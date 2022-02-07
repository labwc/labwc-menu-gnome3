CFLAGS = -g -Wall
CFLAGS += `pkg-config --cflags glib-2.0  gio-unix-2.0`
LDFLAGS +=`pkg-config --libs glib-2.0 gio-unix-2.0`

labwc-menu-gnome3: labwc-menu-gnome3.o
labwc-menu-gnome3: CFLAGS += -DGMENU_I_KNOW_THIS_IS_UNSTABLE
labwc-menu-gnome3: CFLAGS += `pkg-config --cflags libgnome-menu-3.0`
labwc-menu-gnome3: LDFLAGS += `pkg-config --libs libgnome-menu-3.0`
labwc-menu-gnome3.c:
	cp labwc-menu.c labwc-menu-gnome3.c

labwc-menu-cinnamon: labwc-menu-cinnamon.o
labwc-menu-cinnamon: CFLAGS += -DGMENU_I_KNOW_THIS_IS_UNSTABLE
labwc-menu-cinnamon: CFLAGS += `pkg-config --cflags libcinnamon-menu-3.0`
labwc-menu-cinnamon: LDFLAGS += `pkg-config --libs libcinnamon-menu-3.0`
labwc-menu-cinnamon.c:
	cp labwc-menu.c labwc-menu-cinnamon.c

labwc-menu-mate: labwc-menu-mate.o
labwc-menu-mate: CFLAGS += -DMATEMENU_I_KNOW_THIS_IS_UNSTABLE
labwc-menu-mate: CFLAGS += `pkg-config --cflags libmate-menu`
labwc-menu-mate: LDFLAGS += `pkg-config --libs libmate-menu`
labwc-menu-mate.c:
	sed 's/gnome-menus-3.0/mate-menus/; s/applications.menu/mate-&/' labwc-menu.c > labwc-menu-mate.c
	sed -i 's/gmenu/matemenu/g; s/GMenu/MateMenu/g; s/GMENU/MATEMENU/g'  labwc-menu-mate.c

clean:
	rm -f *.o \
		labwc-menu-mate \
		labwc-menu-gnome3 \
		labwc-menu-cinnamon \
		labwc-menu-mate.c \
		labwc-menu-gnome3.c \
		labwc-menu-cinnamon.c
