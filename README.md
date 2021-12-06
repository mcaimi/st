st - simple terminal
--------------------
st is a simple terminal emulator for X which sucks less.

This is a WIP fork of Suckless' awesome [ST](http://st.suckless.org), with some added features built-in:
  - Kept mostly in sync with upstream branch
  - Number of rows and columns are read from Xresources
  - Custom history size via Xresources
  - Added skiptaskbar and skippager XResources options
  - Added support for Xorg fullscreen mode via F11 key
  - For desktops with a dock (e.g. GNOME) an hardcoded RGBA icon is provided
  - Many other fixes here and there

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
  - boxdraw
  - sync patch

Requirements
------------
In order to build st you need the Xlib header files.
For the alpha patch, you also need XRender.

Additional required packages:
  - w3m
  - xurls
  - dmenu

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

