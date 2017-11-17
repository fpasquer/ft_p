/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_cwd_client.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 13:33:17 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/17 07:51:14 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/server.h"

int							send_cwd_server(t_gen const *gen)
{
	char					buff[SIZE_CWD];

	if (gen == NULL)
		return (-1);
	if (send_tab_2d(gen->sock_client, gen->cwd_server.list) != 0)
		return (-1);
	if (ft_strncpy(buff, gen->current_dir, SIZE_CWD) != buff)
		return (-1);
	if (send(gen->sock_client, buff, SIZE_CWD, 0) < 0)
		return (-1);
	if (ft_strncpy(buff, gen->racine, SIZE_CWD) != buff)
		return (-1);
	if (send(gen->sock_client, buff, SIZE_CWD, 0) < 0)
		return (-1);
	printf("\tServer send to client[%3d] cwd_content\n", gen->sock_client);
	return (0);
}