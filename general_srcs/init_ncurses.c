/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ncurses.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 17:24:06 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/29 10:42:06 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../general_incs/general.h"

static void					show_str_ncurses(char const *error)
{
	if (error == NULL)
		return ;
	printw("%s\n", error);
	refresh();
	getch();
}

static WINDOW				*setup_win(int const height, int const width,
		int const begin_y, int const begin_x)
{
	WINDOW					*win;

	if ((win = subwin(stdscr, height, width, begin_y, begin_x)) == NULL)
		return (NULL);
	box(win, ACS_VLINE, ACS_HLINE);
	wrefresh(win);
	return (win);
}

 static int					init_windows(t_ncurses *scr)
{
	if (scr == NULL)
		return (-1);
	if ((scr->infos = setup_win(HIGHT_INFO_WIN, COLS, 0, 0)) == NULL)
		return (-1);
	if ((scr->client = setup_win(LINES - HIGHT_INFO_WIN - HIGHT_TERM_WIN,
				COLS / 2, HIGHT_INFO_WIN, 0)) == NULL)
		return (-1);
	if ((scr->server = setup_win(LINES - HIGHT_INFO_WIN - HIGHT_TERM_WIN,
				COLS / 2, HIGHT_INFO_WIN, COLS / 2)) == NULL)
		return (-1);
	if ((scr->term = setup_win(HIGHT_TERM_WIN, COLS, LINES - HIGHT_TERM_WIN, 0))
				== NULL)
		return (-1);
	return (0);
}

t_ncurses					init_ncurses(void)
{
	t_ncurses				scr;

	initscr();
	ft_bzero(&scr, sizeof(scr));
	if (LINES < SCR_ROW_MIN || COLS < SCR_COL_MIN)
		show_str_ncurses("Screen too small");
	else
		if (init_windows(&scr) != 0)
			show_str_ncurses("Error init_windows");
	curs_set(0);
	return (scr);
}

void						del_ncurses(t_ncurses scr)
{
 	endwin();
	if (scr.infos != NULL)
		ft_memdel((void**)&scr.infos);
	if (scr.client != NULL)
		ft_memdel((void**)&scr.client);
	if (scr.server != NULL)
		ft_memdel((void**)&scr.server);
	if (scr.term != NULL)
		ft_memdel((void**)&scr.term);
}
