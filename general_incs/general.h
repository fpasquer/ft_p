/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 17:22:36 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/03 08:09:42 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERAL_H
# define GENERAL_H

# include "../libft/libft.h"
# include <ncurses.h>
# include <time.h>

# define SIZE_CWD 500

# define SIZE_BUFF 7

# define SCR_ROW_MIN 51
# define SCR_COL_MIN 203

# define HIGHT_INFO_WIN 8
# define HIGHT_TERM_WIN 10

# define UNSELECTED 1
# define SELECTED 2

# ifdef DEBUG
	FILE					*debug;
# endif

typedef enum				e_type_ip
{
	IPV4, IPV6
}							t_type_ip;

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

/*
**	check_ip_port
*/
char						*get_ip(char const *ip, t_type_ip *type_ip);
bool						check_port(char *port);

#endif
