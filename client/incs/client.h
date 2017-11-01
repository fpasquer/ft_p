/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 17:27:29 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/01 20:54:42 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# define DEBUG

# include "../../libft/libft.h"
# include "../../general_incs/general.h"

typedef enum				e_win
{
	CLIENT, SERVER							//liste des fenetres possible de changer
}							t_win;

typedef struct				s_color_ncurses
{
	short					pair;
	short					font;
	short					background;
}							t_color_ncurses;

typedef struct				s_ncurses
{
	WINDOW					*infos;			//fenetre info
	WINDOW					*client;		//fenetre client
	WINDOW					*server;		//fenetre server
	WINDOW					*term;			//fenetre term
}							t_ncurses;

typedef struct				s_gen
{
	char					cmd[SIZE_CMD];	//commandes tapee dans le shell
	t_ncurses				scr;			//ensembles des fenetres
	t_list_cwd				cwd_client;		//liste fichiers du client
	t_list_cwd				cwd_server;		//liste fichiers du server
	t_win					win;			//pour savoir dans quelle fenetre j'execute les commandes
}							t_gen;

void						loop_client(t_ncurses scr);

/*
**	cmds
*/
int							func_change_win(void);
int							func_exit(void);
int							func_ls(void);
int							func_cd(void);
int							func_get(void);
int							func_put(void);
int							func_pwd(void);
int							func_login(void);
int							func_logout(void);
int							func_refresh_client(void);

/*
**	term
*/
int							loop_term(t_gen *gen);

/*
**	ncurses
*/
t_ncurses					init_ncurses(void);
void						del_ncurses(t_gen *gen);

/*
**	general manager
*/
t_gen						*get_general(t_gen *ptr);
void						del_general(int const ret);

#endif
