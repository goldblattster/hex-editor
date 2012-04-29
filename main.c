#include "main.h"

int main(int argc, char* argv[])
{
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  clear();
  refresh();
  parse_file(argv[1]);
  echo();
  endwin();
  return 0;
}

void parse_file(char* file_name)
{
  FILE *f_ptr;
  int c;
  unsigned int i;
  int x;
  unsigned int row;
  char x_cursor;
  char y_cursor;
  char hex_buff[17];
  f_ptr = fopen(file_name, "r+");
  if(f_ptr == NULL)
  {
    printw("\n The file you were trying to open cannot be opened.");
    return;
  }
  for(;;)
  {
    clear();
    mvprintw(0, 0, "Goddamn Hex Tool 0.1 Developed by Danny Panasyuk and Ariel Goldblatt.\n");
    for(i = 1; i < 24; i++)
    {
      fseek(f_ptr, (row + i) * 16, SEEK_SET);
      for(x = 0; x < 16; x++) //Loads a buffer from the file
      {
	hex_buff[x] = fgetc(f_ptr);
	if(hex_buff[x] == EOF)
	{
	  hex_buff[x] = ' ';
	}
	if(hex_buff[x] < 32)
	{
	  hex_buff[x] = '.';
	}
      }
      hex_buff[16] = '\0'; //Buffer is also a string to make things easier
      if((row + i) * 16 <= 255) //Bit of a hack here, this
	mvprintw(i, 0, "00");	//slows things down and makes
      else			//them unelegant but w/e
	if((row + i) * 16 <= 32768)
	  mvprintw(i, 0, "0");
      printw("%X: ", (short)(row + i) * 16);
      for(x = 0; x < 8; x++)
      {
	printw("%X%X ", hex_buff[x], hex_buff[x + 1]); //Print hex to the screen
      }
      printw("%s\n", hex_buff); //Print ASCII to screen
    }
    refresh();
    c = getch();
    switch(c) //Scroll up / down
    {
      case KEY_UP:
	if(row != 0);
	  row--;
	break;
      case KEY_DOWN:
	  row++;
	break;
      case 27: //27 == ESCAPE key
	fclose(f_ptr);
	return;
    }
  }
}