/*
    Contains the Menu dialogs
    Copyright (C) 2015 Marius Messerschmidt
*/

#ifndef _HAVE_MENU
#define _HAVE_MENU

#include <stdlib.h>
#include <gtk/gtk.h>
#include "util.h"

struct menu_stuff
{
  GtkWidget *button;
  char *tag;

};

typedef struct menu_stuff MENU;

//creates an yesno dialog  totalargs  values   where is the --yesno
short create_menu_dialog(int argc, char **argv, int start);

#endif
