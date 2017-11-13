/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ncurses.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 17:24:06 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/13 09:43:28 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/client.h"


static WINDOW				*setup_win(int const height, int const width,
		int const begin_y, int const begin_x)
{
	WINDOW					*win;

	if ((win = subwin(stdscr, height, width, begin_y, begin_x)) == NULL)
		return (NULL);
	wrefresh(win);
	return (win);
}

static int					init_windows(t_ncurses *scr)
{
	if (scr == NULL)
		return (-1);
	clear();
	if ((scr->infos = setup_win(HIGHT_INFO_WIN, COLS, 0, 0)) == NULL)
		return (-1);
	if ((scr->client = setup_win(LINES - HIGHT_INFO_WIN - HIGHT_TERM_WIN,
			COLS / 2, HIGHT_INFO_WIN, 0)) == NULL)
		return (-1);
	if ((scr->server = setup_win(LINES - HIGHT_INFO_WIN - HIGHT_TERM_WIN,
			COLS / 2, HIGHT_INFO_WIN, COLS / 2)) == NULL)
		return (-1);
	if ((scr->term = setup_win(HIGHT_TERM_WIN, COLS, LINES - HIGHT_TERM_WIN, 0)
			) == NULL)
		return (-1);
	return (0);
}

void						show_str_ncurses(char const *error)
{
	if (error == NULL)
		return ;
	clear();
	printw("%s\n", error);
	refresh();
	getch();
}

t_ncurses					init_ncurses(void)
{
	int						i;
	t_ncurses				scr;
	t_color_ncurses const	colors[] = {{1, COLOR_GREEN, COLOR_BLACK},
		{2, COLOR_RED, COLOR_BLACK},{0, 0, 0}};

	initscr();
	i = -1;
	start_color();
	while (colors[++i].pair != 0)
		init_pair(colors[i].pair, colors[i].font, colors[i].background);
	ft_bzero(&scr, sizeof(scr));
	if (init_windows(&scr) != 0)
		show_str_ncurses("Error init_windows");
	curs_set(false);
	return (scr);
}

void						del_ncurses(t_gen *gen)
{
	endwin();
	if (gen != NULL)
	{
		if (gen->scr.infos != NULL)
			delwin(gen->scr.infos);
		if (gen->scr.client != NULL)
			delwin(gen->scr.client);
		if (gen->scr.server != NULL)
			delwin(gen->scr.server);
		if (gen->scr.term != NULL)
			delwin(gen->scr.term);
	}
	curs_set(true);
}
