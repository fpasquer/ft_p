#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#define SIZE_BUFF 9
#define MAX_J 10

int							main(void)
{
	char					buff[SIZE_BUFF];
	int						i;
	int						j;

	initscr();
	while (j < MAX_J)
	{
		bzero(buff, sizeof(char) * SIZE_BUFF);
		if (read(STDIN_FILENO, buff, SIZE_BUFF) > 0)
		{
			j++;
			printw("(char[]){");
			for(i = 0; i < SIZE_BUFF; i++)
				if (i > 0)
					printw(", %d", buff[i]);
				else
					printw("%d", buff[i]);
			printw("}\n");
			refresh();
		}
	}
	endwin();
	return (1);
}
