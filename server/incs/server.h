/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 17:27:29 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/22 11:18:52 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include "../../libft/libft.h"
# include "../../general_incs/general.h"
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct				s_gen
{
	char					*port;			//port d'ecoute du server
	char					racine[SIZE_CWD];
											//path racine server
	char					current_dir[SIZE_CWD];
											//path de la position dans le server
	char					*cmd;			//cmd qui vient du client
	int						sock_server;	//fd de socket server
	int						sock_client;	//fd de socket client
	struct addrinfo			hints;			//pour parametrer le server
	struct addrinfo			*ptr;			//pointeur du debut de la liste
	t_list_cwd				cwd_server;		//liste fichiers du server
}							t_gen;

/*
**	server.c
*/
int							init_server(t_gen *gen);
int							loop_server(void);

/*
**	general.c
*/
t_gen						*get_general(t_gen *ptr);
void						del_general(int const ret);

/*
**	signaux.c
*/
int							init_signaux(void);

/*
**	send_cwd_client
*/
int							send_cwd_server(t_gen const *gen);

/*
**	cmds
*/
int							func_ls(void);
int							func_cd(void);
int							func_get(void);
int							func_put(void);
int							func_pwd(void);
int							func_login(void);
int							func_logout(void);
int							func_refresh_server(void);

/*
**	cmds_manager
*/
int							cmds_manager(t_gen *gen);

#endif
