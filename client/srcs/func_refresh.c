/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_refresh.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 08:59:39 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/24 09:00:02 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/client.h"

int							func_refresh_client(void)
{
	t_gen					*gen;

	if ((gen = get_general(NULL)) == NULL)
		return (-1);
	del_list_cwd(gen->cwd_client);
	if (set_list_cwd(&gen->cwd_client, NULL, gen->cwd_client.cwd_show) != 0 ||
			print_list_cwd(gen->cwd_client, gen->scr.client, gen->win == CLIENT
			? true : false) != 0)
		return (-1);
	if (add_infos("Update content client") != 0 || print_infos() != 0)
		return (-1);
	return (0);
}

int							func_refresh_server(void)
{
	t_gen					*gen;

	if ((gen = get_general(NULL)) == NULL)
		return (-1);
	if (send_tab(gen->i_client.fd, "REFRESH") < 0)
		return (-1);
	del_list_cwd(gen->cwd_server);
	if (set_list_cwd_server() != 0 || print_list_cwd(gen->cwd_server,
			gen->scr.server, gen->win == SERVER ? true : false) != 0)
		return (-1);
	return (0);
}
