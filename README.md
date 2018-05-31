st - simple terminal
--------------------
st is a simple terminal emulator for X which sucks less.

This is a WIP fork of Suckless' awesome [ST](http://st.suckless.org), with some added features built-in:
  - Official patches that needed an update were updated to run in ST 0.8.1
  - Number of rows and columns are read from Xresources
  - Custom history size via Xresources
  - Added skiptaskbar and skippager XResources options
  - Added support for Xorg fullscreen mode via F11 key
  - Added X11 Dock Icon for desktops that support this feature

This forks builds upon the offical ST release already patched with these [st-patches](https://st.suckless.org/patches/):
  - st background alpha
  - clipboard support (xclip)
  - externalpipe
  - spoiler
  - allows to disable bold and italic fonts
  - scrollback and mouse scrollback
  - vertcenter
  - relativeborder
  - support loading options from xresources

Requirements
------------
In order to build st you need the Xlib header files.
For the alpha patch, you also need XRender.

dmenu was replaced with Rofi, so you also need to install that or change the source code.

Additional required packages:
  - w3m
  - xurls
  - rofi

Installation
------------
Edit config.mk to match your local setup (st is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install st (if
necessary as root):

    make clean install


Running st
----------
If you did not install st with make clean install, you must compile
the st terminfo entry with the following command:

    tic -sx st.info

See the man page for additional details.

Credits
-------
Based on Aurélien APTEL <aurelien dot aptel at gmail dot com> bt source code.

