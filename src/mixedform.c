/*
    Contains the InputBox dialogs
    Copyright (C) 2015 Marius Messerschmidt
*/
#include "mixedform.h"

GtkWidget *box;

void ok_mixedform(GtkWidget *w, GdkEvent *e, GtkWidget *toDestroy)
{
    GList *ch, *iter;
    ch = gtk_container_get_children(GTK_CONTAINER(box));
    bool first = true;
    for(iter = ch; iter != NULL; iter = g_list_next(iter))
    {
        if(GTK_IS_BOX(iter->data))
        {

            GList *sub, *subiter;
            sub = gtk_container_get_children(GTK_CONTAINER(iter->data));
            for(subiter = sub; subiter != NULL; subiter = g_list_next(subiter))
            {



                if(GTK_IS_ENTRY(subiter->data))
                {
                    if(!first)
                        fprintf(stderr, " ");

                    first = false;
                    fprintf(stderr, "%s",gtk_entry_get_text(GTK_ENTRY(subiter->data)));
                }


            }
        }
    }
    g_list_free(ch);


    gtk_widget_destroy(toDestroy);

}

short create_mixed_form_dialog(int argc, char **argv, int start)
{
  if(argc - (start+3) < 1)
    return -1;

  char *msg = argv[start+1];
  int width  = atoi(argv[start+2]);
  int height = atoi(argv[start+3]);



  //Create stuff
  GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  if(width > 0 && height > 0)
    gtk_window_resize(GTK_WINDOW(win), width, height);
  gtk_window_set_title(GTK_WINDOW(win), "MIXED FORM box");
  gtk_container_set_border_width(GTK_CONTAINER(win), 18);
  g_signal_connect(G_OBJECT(win), "destroy", G_CALLBACK(destroy), NULL);

  apply_dialog_config(GTK_WINDOW(win));

  //Create BOX + Message label
  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 9);
  GtkWidget *label = gtk_label_new(msg);
  gtk_container_add(GTK_CONTAINER(box), label);

  for(int x = start + 5; x <= argc - 9; x++)
    {
      if(argv[x][0] == '-' && argv[x][1] == '-')
        break; //reached next configuration

    GtkWidget *box_buff = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

    GtkWidget *label = gtk_label_new(argv[x]);
    gtk_box_pack_start(GTK_BOX(box_buff), label, FALSE, FALSE, 0);

    x++; //X
    x++; //Y

    x++;
    GtkWidget *inp = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(inp), argv[x]);
    gtk_box_pack_end(GTK_BOX(box_buff), inp, FALSE, FALSE, 0);

    gtk_container_add(GTK_CONTAINER(box), box_buff);

    x++;
    x++;
    x++;
    x++;
    x++;
    //check for password
    if(atoi(argv[x]) == 1)
        gtk_entry_set_visibility(GTK_ENTRY(inp), FALSE);

    }



  //Create OK/CANCEL Buttons
  GtkWidget *buttonbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 12);
  GtkWidget *button_ok = gtk_button_new_with_label("OK");
  g_signal_connect(G_OBJECT(button_ok), "clicked", G_CALLBACK(ok_mixedform), win);
  GtkWidget *button_cancel  = gtk_button_new_with_label("Cancel");
  g_signal_connect(G_OBJECT(button_cancel) , "clicked", G_CALLBACK(cancel) , win);

  gtk_box_pack_end(GTK_BOX(buttonbox), button_cancel, FALSE, FALSE, 0);
  gtk_box_pack_end(GTK_BOX(buttonbox), button_ok , FALSE, FALSE, 0);

  gtk_box_pack_end(GTK_BOX(box), buttonbox, FALSE, TRUE, 0);
  gtk_container_add(GTK_CONTAINER(win), box);

  gtk_widget_show_all(win);

  gtk_main();
  reset_config();
  return 0;
}
