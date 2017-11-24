/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_win_up.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 09:01:05 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/24 09:04:04 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/client.h"

static int					func_server_up(t_gen *gen)
{
	int						nb_row_scr;

	if (gen == NULL)
		return (-1);
	nb_row_scr = LINES - 2 - HIGHT_INFO_WIN - HIGHT_TERM_WIN;
	if (gen->cwd_server.nb_row > nb_row_scr + gen->cwd_server.decalage)
	{
		gen->cwd_server.decalage++;
		if (print_list_cwd(gen->cwd_server, gen->scr.server, gen->win == SERVER
				? true : false) != 0)
			return (-1);
		if (add_infos("Server scroll up") != 0)
			return (-1);
	}
	return (0);
}

static int					func_client_up(t_gen *gen)
{
	int						nb_row_scr;

	if (gen == NULL)
		return (-1);
	nb_row_scr = LINES - 2 - HIGHT_INFO_WIN - HIGHT_TERM_WIN;
	if (gen->cwd_client.nb_row > nb_row_scr + gen->cwd_client.decalage)
	{
		gen->cwd_client.decalage++;
		if (print_list_cwd(gen->cwd_client, gen->scr.client, gen->win == CLIENT
				? true : false) != 0)
			return (-1);
		if (add_infos("Client scroll up") != 0)
			return (-1);
	}
	return (0);
}

int							func_win_up(void)
{
	t_gen					*gen;

	if ((gen = get_general(NULL)) == NULL)
		return (-1);
	if (gen->win == SERVER)
		return (func_server_up(gen));
	return (func_client_up(gen));
}
