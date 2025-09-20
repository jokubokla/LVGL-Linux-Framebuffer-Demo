//============================================================================
//
// mkdir build
// cd build
// cmake ..
// make
// sudo ./lvgl_fb_demo
//
//============================================================================

// my screen: 1280 x 800

#include "lvgl.h"
#include "lv_linux_fbdev.h"
#include <unistd.h>
#include "ui.h"
#include <stdio.h>
//#include <string.h>
#include <pthread.h>
#include <fcntl.h>
//#include <stdint.h>
#include <stdbool.h>

#include "mouse_cursor_icon.c" // https://lvgl.io/tools/imageconverter

volatile int mouse_x = 640;
volatile int mouse_y = 400;
volatile bool mouse_pressed = false;

static lv_indev_t *mouse_indev;

//============================================================================
//
//============================================================================
static void button_event_blue(lv_event_t *e) 
{
  lv_event_code_t code = lv_event_get_code(e);

  if(code == LV_EVENT_CLICKED)
  {
    static uint8_t counter = 0;
    counter ++;
    lv_label_set_text_fmt(objects.lbl_sample, "You clicked %d times", counter);
  }
}

//============================================================================
//
//============================================================================
static void button_event_red(lv_event_t *e) 
{
  lv_event_code_t code = lv_event_get_code(e);

  if(code == LV_EVENT_CLICKED)
  {

   if(lv_obj_has_state(objects.chk_test, LV_STATE_CHECKED))
   {
     // Checkbox is checked
    lv_label_set_text_fmt(objects.lbl_sample, "Checkbox is checked");
   }
   else
   {
     // Checkbox is not checked
    lv_label_set_text_fmt(objects.lbl_sample, "Checkbox is not checked");
   }

  }

}

//============================================================================
//
//============================================================================
static void mouse_read_cb(lv_indev_t *indev, lv_indev_data_t *data)
{
    data->point.x = mouse_x;
    data->point.y = mouse_y;
    data->state = mouse_pressed ? LV_INDEV_STATE_PRESSED : LV_INDEV_STATE_RELEASED;

    lv_obj_set_pos(lv_indev_get_cursor(indev), mouse_x, mouse_y);
}


//============================================================================
// https://lvgl.io/tools/imageconverter
// 32x32 PNG mit ARGB8888
// Cursor-Image
//============================================================================
void init_lvgl_mouse_cursor_icon(void)
{
    lv_indev_t *indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev, mouse_read_cb);
    mouse_indev = indev;

    LV_IMAGE_DECLARE(mouse_cursor_icon);  // z. B. ein PNG als C-Array

    lv_obj_t *cursor_obj = lv_image_create(lv_screen_active());
    lv_image_set_src(cursor_obj, &mouse_cursor_icon);
    lv_obj_clear_flag(cursor_obj, LV_OBJ_FLAG_CLICKABLE);  // Cursor soll nicht klickbar sein

    lv_indev_set_cursor(mouse_indev, cursor_obj);

}

//============================================================================
// UNUSED
//============================================================================
void init_lvgl_mouse_cursor_char(void)
{
    lv_indev_t *indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev, mouse_read_cb);

    lv_label_set_text(objects.lbl_mouse, "+");
    lv_obj_clear_flag(objects.lbl_mouse, LV_OBJ_FLAG_CLICKABLE);
    lv_indev_set_cursor(indev, objects.lbl_mouse);
    lv_obj_move_foreground(objects.lbl_mouse);

    lv_obj_set_style_text_color(objects.lbl_mouse, lv_color_hex(0xFF0000), 0);
    lv_obj_set_style_bg_color(objects.lbl_mouse, lv_color_hex(0x000000), 0);
    lv_obj_set_style_bg_opa(objects.lbl_mouse, LV_OPA_COVER, 0);

}

//============================================================================
//
//============================================================================
void *mouse_thread(void *arg)
{
    int fd = open("/dev/input/mice", O_RDONLY);
    if (fd < 0) 
    {
        perror("Fehler beim Öffnen von /dev/input/mice");
        return NULL;
    }

    uint8_t data[3];
    while (1) 
    {
        if (read(fd, data, sizeof(data)) > 0) {
            int dx = (int8_t)data[1];
            int dy = (int8_t)data[2];

            mouse_x += dx;
            mouse_y -= dy;

            // Begrenzung auf Bildschirmgröße (z. B. 1280 x 800)
            if (mouse_x < 0) mouse_x = 0;
            if (mouse_y < 0) mouse_y = 0;
            if (mouse_x > 1279) mouse_x = 1279;
            if (mouse_y > 799) mouse_y = 799;

            mouse_pressed = data[0] & 0x1;
        }
        usleep(5000);
    }
    close(fd);
    return NULL;
}


//============================================================================
//
//============================================================================
int main(void)
{
    char pos[80];
    
    lv_init();

    lv_display_t *disp = lv_linux_fbdev_create();
    lv_linux_fbdev_set_file(disp, "/dev/fb0");
    //lv_linux_fbdev_set_force_refresh(disp, true);

    pthread_t mouse_tid;
    pthread_create(&mouse_tid, NULL, mouse_thread, NULL);
       
    ui_init();

    init_lvgl_mouse_cursor_icon();

    lv_obj_add_event_cb(objects.btn_blue, button_event_blue, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(objects.btn_red, button_event_red, LV_EVENT_ALL, NULL);

    while (1) 
    {
        lv_timer_handler();
        ui_tick();
        usleep(5000);
        snprintf(pos, sizeof(pos), "X:%d Y:%d %s", mouse_x, mouse_y, mouse_pressed ? "PRESSED" : "RELEASED");
        lv_label_set_text_fmt(objects.lbl_debug, pos );

        if(mouse_pressed) 
        {
            //printf("X:%d Y:%d PRESSED\n", mouse_x, mouse_y);
        }

    }

    return 0;
}
