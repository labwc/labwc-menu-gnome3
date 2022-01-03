// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (C) 2021 Johan Malm
 */
#include <gio/gio.h>
#include <glib.h>
#include <gnome-menus-3.0/gmenu-tree.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void
process_entry(GMenuTreeEntry *entry)
{
	GDesktopAppInfo *info;
	info = gmenu_tree_entry_get_app_info(entry);
	if (!info) {
		fprintf(stderr, "no app info\n");
		return;
	}

	GString *name = g_string_new(g_app_info_get_name(G_APP_INFO(info)));
	g_string_replace(name, "&", "&amp;", 0);

	/*
	 * g_app_info_get_executable() appears not to return any % fields, so
	 * no need to strip those out.
	 */
	const char *exec = g_app_info_get_executable(G_APP_INFO(info));

	printf("  <item label=\"%s\">\n", name->str);
	printf("    <action name=\"Execute\">\n");
	printf("      <command>%s</command>\n", exec);
	printf("    </action>\n");
	printf("  </item>\n");

	g_string_free(name, TRUE);
}

void
process_directory(GMenuTreeDirectory *dir)
{
	static bool is_first_menu_element = true;

	if (is_first_menu_element) {
		printf("<menu id=\"root-menu\" label=\"Openbox 3\">\n");
		is_first_menu_element = false;
	} else {
		printf("<menu id=\"%s\" label=\"%s\">\n",
			gmenu_tree_directory_get_name(dir),
			gmenu_tree_directory_get_name(dir));
	}

	GMenuTreeIter *iter = gmenu_tree_directory_iter(dir);

	for (;;) {
		switch (gmenu_tree_iter_next(iter)) {
		case GMENU_TREE_ITEM_INVALID:
			goto out;
		case GMENU_TREE_ITEM_ENTRY:
			{
				GMenuTreeEntry *entry = gmenu_tree_iter_get_entry(iter);
				process_entry(entry);
			}
			break;
		case GMENU_TREE_ITEM_DIRECTORY:
			{
				GMenuTreeDirectory *dir =
					gmenu_tree_iter_get_directory(iter);
				process_directory(dir);
			}
		default:
			break;
		}
	}
out:
	printf("</menu>\n");
}

int
main(int argc, char **argv)
{
	char *menu = "applications.menu";

	printf("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
	printf("<openbox_menu>\n");

	GMenuTree *tree = gmenu_tree_new(menu, GMENU_TREE_FLAGS_NONE);
	gmenu_tree_load_sync(tree, NULL);
	GMenuTreeDirectory *rootdir = gmenu_tree_get_root_directory(tree);
	process_directory(rootdir);
	gmenu_tree_item_unref(rootdir);

	printf("</openbox_menu>\n");
}
