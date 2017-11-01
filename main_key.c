#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#define SIZE_BUFF 9
#define MAX_J 10

typedef struct				s_coord
{
	int						y;
	int						x;
}							t_coord;

int							get_mouse_coord(t_coord *c_mouse, int *button)
{
	MEVENT					event;

	if (c_mouse == NULL || button == NULL)
		return (-1);
	if (getmouse(&event) != OK)
		return (-1);
	c_mouse->y = event.y;
	c_mouse->x = event.x;
	(*button) = event.bstate;
	return (0);
}

int							main(void)
{
	char					buff[SIZE_BUFF];
	int						i;
	int						j;
	t_coord					c_mouse;
	int						button;

	initscr();
	while (j < MAX_J)
	{
		bzero(buff, sizeof(char) * SIZE_BUFF);
		if (read(STDIN_FILENO, buff, SIZE_BUFF) > 0)
		{
			printw("%d\n", button);
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
