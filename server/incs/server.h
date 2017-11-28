/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 17:27:29 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/24 11:28:17 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include "../../libft/libft.h"
# include "../../general_incs/general.h"
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

# define MAX_LEN_PORT 6

typedef struct				s_gen
{
	char					port[MAX_LEN_PORT];
	int						sock_server;
	struct addrinfo			hints;
	struct addrinfo			*ptr;

}							t_gen;

typedef struct				s_client
{
	char					*cmd;
	char					racine[SIZE_CWD];
	char					current_dir[SIZE_CWD];
	int						sock_server;
	int						sock_client;
	t_list_cwd				cwd_server;
}							t_client;

/*
**	general
*/
t_gen						*get_general(t_gen *gen);
int							del_general(int const ret);

/*
**	client_manager
*/
void						new_client(int sock_client, int sock_server);
t_client					*get_client(t_client *client);
void						del_client(int const ret);

/*
**	server.c
*/
int							init_server(char const *port);
void						loop_server(t_gen *gen);

/*
**	signaux
*/
int							init_signaux(void);

/*
**	send_cwd_client
*/
int							send_cwd_server(t_client const *gen);

/*
** cwd_manager
*/
int							cmds_manager(t_client *gen);

/*
**	cmds
*/
int							func_ls(void);
int							func_cd(void);
int							func_get(void);
int							func_put(void);
int							func_pwd(void);
int							func_logout(void);
int							func_refresh_server(void);

#endif
