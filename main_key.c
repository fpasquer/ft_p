/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 20:59:26 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/18 16:09:47 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>

int							main(void)
{
	initscr();
	printw("nb row = %d nb col = %d\n", LINES, COLS);
	refresh();
	getchar();
	endwin();
	return (0);
}
