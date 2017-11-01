/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 17:22:36 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/01 18:49:36 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERAL_H
# define GENERAL_H

# include "../libft/libft.h"
# include <ncurses.h>
# include <time.h>

# define SCR_ROW_MIN 51
# define SCR_COL_MIN 203

# define HIGHT_INFO_WIN 8
# define HIGHT_TERM_WIN 10

# define DEBUG

# define SIZE_BUFF 7

# define SIZE_CWD 500
# define SIZE_CMD 1000

# define PROMPT "?> "
# define LEN_PROMPT ft_strlen(PROMPT)

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

typedef struct				s_list_cwd
{
	char					cwd[SIZE_CWD];
	char					**list;
	int						nb_row;
	int						decalage;
}							t_list_cwd;

typedef struct				s_gen
{
	char					cmd[SIZE_CMD];
	t_ncurses				scr;
	t_list_cwd				cwd_client;
	t_list_cwd				cwd_server;
}							t_gen;

typedef struct				s_cmd_manager
{
	char					*cmd;
	int						(*f)(void);
}							t_cmd_manager;

/*
**	keybord.c
*/
ssize_t						get_key_pressed(char buff[SIZE_BUFF]);

/*
**	gestion cwd client server
*/
int							set_list_cwd(t_list_cwd *cwd);
int							print_list_cwd(t_list_cwd cwd, WINDOW *win);
void						del_list_cwd(t_list_cwd cwd);

#endif
