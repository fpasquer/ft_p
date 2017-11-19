/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 20:59:26 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/19 08:56:22 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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
