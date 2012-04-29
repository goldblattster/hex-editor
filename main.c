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
  unsigned int row = 0;
  char x_cursor = 0;
  char y_cursor = 0;
  char at_cursor;
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
    dump_hex(f_ptr, row, 24, 1); 
    c = getch();
    switch(c) //Scroll up / down
    {
      case KEY_PPAGE:
	if(row != 0)
	  row--;
	break;
      case KEY_NPAGE:
	if(row != 0xFFFFFFFF)
	  row++;
	break;
      case 27: //27 == ESCAPE key
	fclose(f_ptr);
	return;
      case KEY_UP:
	if(y_cursor != 0)
	  y_cursor--;
	break;
      case KEY_DOWN:
	if(y_cursor != 24) 
	  y_cursor++;
	break;
      case KEY_LEFT:
	if(x_cursor != 0)
	  x_cursor--;
	break;
      case KEY_RIGHT:
	if(x_cursor != 79)
	  x_cursor++;
	break;
    }
  }
}

void dump_hex(FILE* f_ptr,unsigned int row, unsigned int line_dump, int y)
{
  char hex_buff[17];
  int i;
  int x;
  if(f_ptr == NULL)
  {
    printw("\n The file you were trying to open cannot be opened.");
    return;
  }
  for(i = y; i < line_dump; i++)
  {
    fseek(f_ptr, (row + i) * 16, SEEK_SET);
    for(x = 0; x < 16; x++)
    {
      hex_buff[x] = fgetc(f_ptr);
      if(hex_buff[x] == EOF)
	hex_buff[x] = ' ';
      if(hex_buff[x] < 32)
	hex_buff[x] = '.';
    }
    hex_buff[16] = '\0';
    mvprintw(i, 0, "%X: ", (row + i) * 16);
    move(i, 11);
    for(x = 0; x < 8; x++)
    {
      printw("%X%X ", hex_buff[x], hex_buff[x + 1]);
    }
    printw(" %s\n", hex_buff);
  }
  refresh();
}

