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