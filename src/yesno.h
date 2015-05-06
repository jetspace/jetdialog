/*
    Contains the YesNo dialogs
    Copyright (C) 2015 Marius Messerschmidt
*/

#ifndef _HAVE_YES_NO
#define _HAVE_YES_NO

#include <stdlib.h>
#include <gtk/gtk.h>
#include "util.h"

#define YES 0
#define NO  1

//creates an yesno dialog  totalargs  values   where is the --yesno
short create_yes_no_dialog(int argc, char **argv, int start);



#endif
