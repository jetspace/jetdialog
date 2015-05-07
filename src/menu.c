/*
    Contains the Menu dialogs
    Copyright (C) 2015 Marius Messerschmidt
*/
#include "menu.h"

MENU *menulist;
int menusize;

void menu_button_cb(GtkWidget *code, GdkEvent *e, gpointer p)
{
  for( int x = 0; x < menusize; x++)
    if(menulist[x].button == code)
      {
        fprintf(stderr, "%s", menulist[x].tag);
        free(menulist);
        gtk_main_quit();
        return;
      }

    g_warning("Can't find clicked button! (your memory is might damaged)");

}

short create_menu_dialog(int argc, char **argv, int start)
{
  if(argc - (start+6) < 1)
    return -1;

  char *msg = argv[start+1];
  int width  = atoi(argv[start+2]);
  int height = atoi(argv[start+3]);
  int menu_height = atoi(argv[start+4]);

  //Create stuff
  GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  if(width > 0 && height > 0)
    gtk_window_resize(GTK_WINDOW(win), width, height);
  gtk_window_set_title(GTK_WINDOW(win), "MENU box");
  gtk_container_set_border_width(GTK_CONTAINER(win), 18);
  g_signal_connect(G_OBJECT(win), "destroy", G_CALLBACK(destroy), NULL);

  apply_dialog_config(GTK_WINDOW(win));

  //Create BOX + Message label
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 18);
  GtkWidget *label = gtk_label_new(msg);

  GtkWidget *scroll = gtk_scrolled_window_new(NULL, NULL);
  gtk_scrolled_window_set_min_content_width(GTK_SCROLLED_WINDOW(scroll), 250);
  if(menu_height > 0)
    gtk_scrolled_window_set_min_content_height(GTK_SCROLLED_WINDOW(scroll), 40 * menu_height);


  GtkWidget *menu_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 12);
  gtk_container_add(GTK_CONTAINER(scroll), menu_box);
  int c = 0;
  for(int x = start + 5; x <= argc - 2; x++)
    {
      if(argv[x][0] == '-' && argv[x][1] == '-')
        break; //reached next configuration

      c++;
      menulist = realloc(menulist, sizeof(MENU) * c);
      if(menulist == NULL)
        g_error("Memory was corupted");
      menulist[c-1].tag = argv[x];
      x++;
      menulist[c-1].button = gtk_button_new_with_label(argv[x]);
      gtk_container_add(GTK_CONTAINER(menu_box), menulist[c-1].button);
      g_signal_connect(G_OBJECT(menulist[c-1].button), "clicked", G_CALLBACK(menu_button_cb), NULL);
    }
    menusize = c;

  if(menu_height <= 0)
    gtk_scrolled_window_set_min_content_height(GTK_SCROLLED_WINDOW(scroll), 40 * menusize <= 200 ? 40 * menusize : 200);


  //Create OK/CANCEL Buttons
  GtkWidget *buttonbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 12);
  GtkWidget *button_cancel  = gtk_button_new_with_label("Cancel");
  g_signal_connect(G_OBJECT(button_cancel) , "clicked", G_CALLBACK(cancel) , win);
  gtk_box_pack_end(GTK_BOX(buttonbox), button_cancel, FALSE, FALSE, 0);

  gtk_container_add(GTK_CONTAINER(box), label);
  gtk_container_add(GTK_CONTAINER(box), scroll);
  gtk_box_pack_end(GTK_BOX(box), buttonbox, FALSE, TRUE, 0);
  gtk_container_add(GTK_CONTAINER(win), box);
  gtk_widget_show_all(win);

  gtk_main();
  reset_config();
  menusize = 0;
  return 0;
}
