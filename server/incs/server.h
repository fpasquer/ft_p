/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 17:27:29 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/23 22:00:18 by fpasquer         ###   ########.fr       */
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

typedef struct				s_data_file
{
	char					*datas;			//ligne complete envoye au client
	char					*name;			//name du fichier
	char					*file_content;	//contenue du fihier
	int						fd;				//de open
	size_t					len_name;		//longueur de name
	size_t					size_file;		//size_du fichier
	size_t					size_datas;		//size_datas
}							t_data_file;

typedef struct				s_gen
{
	char					port[MAX_LEN_PORT];
											//port d'ecoute du server
	int						sock_server;	//fd de socket server
	struct addrinfo			hints;			//pour parametrer le server
	struct addrinfo			*ptr;			//pointeur du debut de la liste

}							t_gen;

typedef struct				s_client
{
	char					*cmd;			//cmd qui vient du client
	char					racine[SIZE_CWD];
											//path racine server
	char					current_dir[SIZE_CWD];
											//path de la position dans le server
	int						sock_server;	//fd de socket server
	int						sock_client;	//fd de socket client
	t_list_cwd				cwd_server;		//liste fichiers du server
}							t_client;

/*
**	general
*/
t_gen 						*get_general(t_gen *gen);
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
int							func_login(void);
int							func_logout(void);
int							func_refresh_server(void);

#endif
