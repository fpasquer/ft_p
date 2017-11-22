/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signaux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 15:05:09 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/22 16:26:56 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/server.h"

static void					func_ctrl_c(int sig)
{
	t_gen					*gen;

	if ((gen = get_general(NULL)) != NULL)
		del_general(EXIT_SUCCESS);
	exit(sig);
}

int							init_signaux(void)
{
	unsigned int			i;
	static t_sig_func const	signaux[] = {{SIGINT, func_ctrl_c}, {0, NULL}};

	i = 0;
	while (signaux[i].f != NULL)
	{
		if (signal(signaux[i].signal, signaux[i].f) == SIG_ERR)
			return (-1);
		i++;
	}
	return (0);
}