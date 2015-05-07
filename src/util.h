#ifndef _HAVE_UTIL
#define _HAVE_UTIL

#include <gtk/gtk.h>
#include "config_vars.h"


void destroy(GtkWidget *w, GdkEvent *e, gpointer p);
void cancel(GtkWidget *w, GdkEvent *e, GtkWidget *toDestroy);
void set_backtitle(char *back);
void apply_dialog_config(GtkWindow *w);
void reset_config(void);

#endif
