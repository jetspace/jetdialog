/*
  Contains some basic things
  Copyright (C) 2015 Marius Messerschmidt

*/

#include "util.h"

void destroy(GtkWidget *w, GdkEvent *e, gpointer p)
{
  gtk_main_quit();
}
