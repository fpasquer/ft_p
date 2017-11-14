/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 17:27:29 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/13 11:39:55 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include "../../libft/libft.h"
# include "../../general_incs/general.h"
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

# define MAX_CLIENT 255

typedef struct				s_gen
{
	char					*port;			//port d' ecoute du server
	int						sock_server;	//fd de socket server
	int						sock_clients[MAX_CLIENT];
											//tableau des fd des clients
}							t_gen;

/*
**	server.c
*/
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
