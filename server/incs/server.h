/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 17:27:29 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/15 08:01:44 by fpasquer         ###   ########.fr       */
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
	char					*port;			//port d' ecoute du server
	struct addrinfo			hints;			//pour parametrer le server
	struct addrinfo			*ptr;			//pointeur du debut de la liste
	int						sock_server;	//fd de socket server
	int						sock_client;	//fd de socket client
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

#endif
