/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_cmds_server.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 10:37:10 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/16 06:39:53 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/client.h"

int							set_list_cwd_server(void)
{
	t_gen					*gen;

	if ((gen = get_general(NULL)) == NULL || gen->i_client.fd == 0)
		return (-1);
	if ((gen->cwd_server.list = get_tab_2d(gen->i_client.fd)) == NULL)
		return (-1);
	if (recv(gen->i_client.fd, gen->cwd_server.cwd_show, SIZE_CWD, 0) < 0)
		return (-1);
	if (recv(gen->i_client.fd, gen->cwd_server.cwd, SIZE_CWD, 0) < 0)
		return (-1);
	gen->cwd_server.nb_row = (int)len_y(gen->cwd_server.list);
	if (add_infos("Update content server") != 0)
		return (-1);
	return (0);
}