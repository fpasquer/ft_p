/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 17:27:29 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/14 09:40:57 by fpasquer         ###   ########.fr       */
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
	int						sock_server;	//fd de socket server
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
