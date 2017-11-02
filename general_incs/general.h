/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 17:22:36 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/02 18:10:19 by fpasquer         ###   ########.fr       */
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

# define SIZE_BUFF 7

# define SIZE_CWD 500
# define SIZE_CMD 1000

# define UNSELECTED 1
# define SELECTED 2

# define PROMPT "?> "
# define LEN_PROMPT ft_strlen(PROMPT)

# ifdef DEBUG
	FILE					*debug;
# endif

typedef struct				s_coord
{
	int						y;
	int						x;
}							t_coord;

typedef struct				s_list_cwd
{
	char					cwd[SIZE_CWD];
	char					**list;
	int						nb_row;
	int						decalage;
}							t_list_cwd;

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
int							print_list_cwd(t_list_cwd const cwd, WINDOW *win,
		bool const selected);
void						del_list_cwd(t_list_cwd cwd);

#endif
