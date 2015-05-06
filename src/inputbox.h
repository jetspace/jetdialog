/*
    Contains the InputBox dialogs
    Copyright (C) 2015 Marius Messerschmidt
*/

#ifndef _HAVE_INPUT_BOX
#define _HAVE_INPUT_BOX

#include <stdlib.h>
#include <gtk/gtk.h>
#include "util.h"

//creates an yesno dialog  totalargs  values   where is the --yesno
short create_input_box_dialog(int argc, char **argv, int start);

#endif
