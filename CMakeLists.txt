cmake_minimum_required(VERSION 3.10)
project(lvgl_fb_demo C)

set(CMAKE_C_STANDARD 99)

# LVGL
add_subdirectory(lvgl)

# Framebuffer-Treiber
add_library(lv_linux_fbdev drivers/lv_linux_fbdev.c)
target_include_directories(lv_linux_fbdev PUBLIC drivers)

# Hauptprogramm
add_executable(lvgl_fb_demo main.c ui.c screens.c)
target_include_directories(lvgl_fb_demo PRIVATE lvgl drivers)
target_link_libraries(lvgl_fb_demo PRIVATE lvgl lv_linux_fbdev m)
