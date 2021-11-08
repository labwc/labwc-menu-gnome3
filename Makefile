CFLAGS = -g -Wall -DGMENU_I_KNOW_THIS_IS_UNSTABLE
CFLAGS += `pkg-config --cflags glib-2.0 libgnome-menu-3.0 gio-unix-2.0`
LDFLAGS +=`pkg-config --libs glib-2.0 libgnome-menu-3.0 gio-unix-2.0`

labwc-menu-gnome3: labwc-menu-gnome3.o

clean:
	rm -f *.o labwc-menu-gnome3
