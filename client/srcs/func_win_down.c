/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_win_down.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 09:02:33 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/24 09:03:11 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/client.h"

static int					func_client_down(t_gen *gen)
{
	if (gen == NULL)
		return (-1);
	if (gen->cwd_client.decalage > 0)
	{
		gen->cwd_client.decalage--;
		if (print_list_cwd(gen->cwd_client, gen->scr.client, gen->win == CLIENT
				? true : false) != 0)
			return (-1);
		if (add_infos("Client scroll down") != 0)
			return (-1);
	}
	return (0);
}

static int					func_server_down(t_gen *gen)
{
	if (gen == NULL)
		return (-1);
	if (gen->cwd_server.decalage > 0)
	{
		gen->cwd_server.decalage--;
		if (print_list_cwd(gen->cwd_server, gen->scr.server, gen->win == SERVER
				? true : false) != 0)
			return (-1);
		if (add_infos("Server scroll down") != 0)
			return (-1);
	}
	return (0);
}

int							func_win_down(void)
{
	t_gen					*gen;

	if ((gen = get_general(NULL)) == NULL)
		return (-1);
	if (gen->win == SERVER)
		return (func_server_down(gen));
	return (func_client_down(gen));
}
