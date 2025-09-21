# LVGL-Linux-Framebuffer-Demo

This is just a simple demo how to use LVGL, the [Light and Versatile Graphics Library](https://lvgl.io) together with [EEZ Studio](https://www.envox.eu/studio/studio-introduction/) on an old Laptop running Linux and using the Linux framebuffer.

### Prerequisites
- Debian 12 "bookworm" (other Linux versions presumably work as well)
- LVGL Version 9.4.0
- EEZ Studio Version 0.24.0

### Blinking Cursor
The blinking cursor created by the Linux kernel shoud be disabled if you work with the framebuffer. This can be done by adding **vt.global_cursor_default=0** to the kernel command line in /etc/default/grub 

```
...
GRUB_CMDLINE_LINUX_DEFAULT="quiet vt.global_cursor_default=0"
...
```

### Project Structure
```
LVGL-Linux-Framebuffer-Demo/
├── CMakeLists.txt
├── main.c
├── build/             # Build directory
├── lvgl/              # LVGL 9 Source
└── drivers/           # Framebuffer-Driver
    └── lv_linux_fbdev.c
    └── lv_linux_fbdev.h

```
### Setup

After clone or download of this repo, the following steps are necessary:

1. Clone LVGL by executing the following command from the project root
```
git clone https://github.com/lvgl/lvgl.git --branch master
```

2. Create a build directory and build the project
```
mkdir build
cd build
cmake ..
make
sudo ./lvgl_fb_demo
```

### Hints

- The file **main.c** is the only one I edited myself
- The **mouse_cursor_icon.c** was generated online with the [LVGL image converter](https://lvgl.io/tools/imageconverter). Find the **.png** in the /images folder.
- The other files were generated with  [EEZ Studio](https://www.envox.eu/studio/studio-introduction/). Find the **.eez-project** in the /EEZ_STUDIO folder.

