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

1. Clone this repository
```
git clone https://github.com/jokubokla/LVGL-Linux-Framebuffer-Demo
```

2. Clone LVGL by executing the following command from the project root
```
cd LVGL-Linux-Framebuffer-Demo
git clone https://github.com/lvgl/lvgl.git --branch master
```

3. Create the build directory and build the project
```
mkdir build
cd build
cmake ..
make
```

4. Execute as sudo because of framebuffer and mouse access
```
sudo ./lvgl_fb_demo
```
5. For future builds just execute make in the /build directory
```
make
```



### Hints

- The file **main.c** is the only one I edited myself (together with friendly support from Microsoft Copilot).

- The file **main_dead_simple.c** only shows the UI without mouse or button events. Exchange this file with **main.c** for a first test in case you have trouble.

- The **mouse_cursor_icon.c** was generated online with the [LVGL image converter](https://lvgl.io/tools/imageconverter). Find the **.png** in the /images folder.

- The other files were generated with  [EEZ Studio](https://www.envox.eu/studio/studio-introduction/). Find the **.eez-project** in the /EEZ_STUDIO folder.

