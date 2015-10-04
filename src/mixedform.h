/*
    Contains the InputBox dialogs
    Copyright (C) 2015 Marius Messerschmidt
*/

#ifndef _HAVE_MIXED_FORM
#define _HAVE_MIXED_FORM

#include <stdlib.h>
#include <stdbool.h>
#include <gtk/gtk.h>
#include "util.h"

//creates an yesno dialog  totalargs  values   where is the --yesno
short create_mixed_form_dialog(int argc, char **argv, int start);

#endif
