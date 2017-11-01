/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ncurses.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 17:24:06 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/01 21:20:16 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/client.h"

# define UNSELECTED 1
# define SELECTED 2

static t_color_ncurses		g_colors[] =
{
	{1, COLOR_GREEN, COLOR_BLACK},
	{2, COLOR_RED, COLOR_BLACK},
	{0, 0, 0}
};

static void					show_str_ncurses(char const *error)
{
	if (error == NULL)
		return ;
	printw("%s\n", error);
	refresh();
	getch();
	exit(EXIT_FAILURE);
}

static WINDOW				*setup_win(int const height, int const width,
		int const begin_y, int const begin_x)
{
	WINDOW					*win;

	if ((win = subwin(stdscr, height, width, begin_y, begin_x)) == NULL)
		return (NULL);
	wattron(win, COLOR_PAIR(UNSELECTED));
	box(win, ACS_VLINE, ACS_HLINE);
	wattroff(win, COLOR_PAIR(UNSELECTED));
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
	if ((scr->term = setup_win(HIGHT_TERM_WIN, COLS, LINES - HIGHT_TERM_WIN, 0)
			)== NULL)
		return (-1);
	return (0);
}

t_ncurses					init_ncurses(void)
{
	int						i;
	t_ncurses				scr;

	initscr();
	i = -1;
	start_color();
	while (g_colors[++i].pair != 0)
		init_pair(g_colors[i].pair, g_colors[i].font, g_colors[i].background);
	ft_bzero(&scr, sizeof(scr));
	if (LINES < SCR_ROW_MIN || COLS < SCR_COL_MIN)
		show_str_ncurses("Screen too small");
	else
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
