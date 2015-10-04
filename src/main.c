/*

  JetDialog - Simple dialogs for desktop
  Copyright (C) 2015 Marius Messerschmidt

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "yesno.h"
#include "inputbox.h"
#include "mixedform.h"
#include "menu.h"

#define VERSION "0.03"

//defines for 'usage'
enum {
  NO_ARGS = 0,    //User has not given any args
  FALSE_ARGS,     //User has given invalid args
  TOO_MUCH_ARGS,  //User has given too much args
  JUST_HELP       //User did all right! just show help
};

typedef short selector;

void usage(selector x)
{
  puts("JetDialog");
  if(x == NO_ARGS)
    {
      puts("You have given no arguments!");
      puts("you must at least give one argument.\n");
    }

  puts("Valid Arguments:");
  puts("  --help   |-h                   :  Displays this help message");
  puts("  --version|-v                   :  Shows current Version");


  if(x != JUST_HELP)
      exit(-1);

}


/*

Main will be called, args will be phrased and then a function
for the specific dialog will be called...

Planned for future:
  - enable module loading (plugins)

*/

int main(int argc, char **argv)
{
  int ret;
  if(argc == 1)
    {
      //we have no args...
      usage(NO_ARGS);
    }
  if(argc >= 2)
    { //Phrase dialogs
      gtk_init(&argc, &argv);
      for(int x = 0; x < argc; x++)
        {
          if(strcmp(argv[x], "--yesno") == 0)
          {
            ret = create_yes_no_dialog(argc, argv, x);
            if(ret == -1)
              usage(FALSE_ARGS);
            continue;
          }
          else if(strcmp(argv[x], "--inputbox") == 0)
          {
            ret = create_input_box_dialog(argc, argv, x);
            if(ret == -1)
              usage(FALSE_ARGS);
            continue;
          }
          else if(strcmp(argv[x], "--menu") == 0)
          {
            ret = create_menu_dialog(argc, argv, x);
            if(ret == -1)
              usage(FALSE_ARGS);
            continue;
          }
          else if(strcmp(argv[x], "--mixedform") == 0)
          {
            ret = create_mixed_form_dialog(argc, argv, x);
            if(ret == -1)
              usage(FALSE_ARGS);
            continue;
          }



          //phrase config params
          if(strcmp(argv[x], "--backtitle") == 0)
            if(argc > x+1)
              {
                set_backtitle(argv[x+1]);
                x++;
              }


        }

    }

    return ret;

}
