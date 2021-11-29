# dwm - dynamic window manager
dwm is an extremely fast, small, and dynamic window manager for X.

## owbosh's build
### Patches
- [ru_gaps](https://dwm.suckless.org/patches/ru_gaps/)

    The most sensible gaps patch in my opinion. Equal gaps on all sides. Removes gaps and borders when only one window is present. Adjustable at runtime.
- [winicon](https://dwm.suckless.org/patches/winicon/)

    Displays the application icon of the focused window, next to the title in the status bar.
- [dynamicswallow](https://dwm.suckless.org/patches/dynamicswallow/)

    Manually make windows "swallow" other windows (not limited to terminals). You can Mod + Shift + Mouse drag a window to another window to swallow it.
- [selfrestart](https://dwm.suckless.org/patches/selfrestart/)

    Restart dwm in-place using a keybind.
- [systray](https://dwm.suckless.org/patches/systray/)

    Adds a system tray to the status bar for programs that support it.

## Requirements
In order to build dwm you need the Xlib header files.

## Installation
Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

    make clean install

## Running dwm
Add the following line to your .xinitrc to start dwm using startx:

    exec dwm

In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

    DISPLAY=foo.bar:1 exec dwm

(This will start dwm on display :1 of the host foo.bar.)

In order to display status info in the bar, you can do something
like this in your .xinitrc:

    while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
    do
    	sleep 1
    done &
    exec dwm

## Configuration
The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.
