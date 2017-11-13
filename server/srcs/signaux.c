/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 10:03:50 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/13 10:33:16 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/server.h"

static void				func_int(int sig)
{
	del_general(EXIT_SUCCESS);
	sig = (int)sig;
}

int							init_signaux(void)
{
	int						i;
	t_sig_func const		list_sin [] =
	{
		{SIGINT, func_int},
		{0, NULL}
	};

	i = -1;
	while (list_sin[++i].f != NULL)
		if (signal(list_sin[i].signal, list_sin[i].f) == SIG_ERR)
			return (-1);
	return (0);
}
