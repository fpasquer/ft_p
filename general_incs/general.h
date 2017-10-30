/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 17:22:36 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/30 07:33:05 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERAL_H
# define GENERAL_H

# include "../libft/libft.h"
# include "key.h"
# include <ncurses.h>

# define SCR_ROW_MIN 51
# define SCR_COL_MIN 203

# define HIGHT_INFO_WIN 8
# define HIGHT_TERM_WIN 10

# define ESCAPE 27

# define DEBUG

# ifdef DEBUG
	FILE					*debug;
# endif

typedef struct				s_ncurses
{
	WINDOW					*infos;
	WINDOW					*client;
	WINDOW					*server;
	WINDOW					*term;
}							t_ncurses;

typedef struct				s_gen
{
	t_ncurses				scr;
}							t_gen;


t_ncurses					init_ncurses(void);
void						del_ncurses(t_ncurses scr);
int							get_key_pressed(char buff[SIZE_BUFF]);
t_gen						*get_general(t_gen *ptr);
void						del_general(void);

#endif
