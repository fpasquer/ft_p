/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 17:27:29 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/22 15:23:21 by fpasquer         ###   ########.fr       */
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
	
}							t_gen;

/*
**	general
*/
t_gen 						*get_general(t_gen *gen);
int							del_general(void);

/*
**	signaux
*/
int							init_signaux(void);

#endif
