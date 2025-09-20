//============================================================================
//
// mkdir build
// cd build
// cmake ..
// make
// sudo ./lvgl_fb_demo
//
//============================================================================

#include "lvgl.h"
#include "lv_linux_fbdev.h"
#include <unistd.h>
#include "ui.h"

int main(void)
{
    lv_init();

    lv_display_t *disp = lv_linux_fbdev_create();
    lv_linux_fbdev_set_file(disp, "/dev/fb0");

    ui_init();

    while (1) {
        lv_timer_handler();
        ui_tick();
        usleep(5000);
    }

    return 0;
}
