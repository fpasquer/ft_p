/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_cmds_server.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 10:37:10 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/15 11:03:05 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/client.h"

int							set_list_cwd_server(void)
{
	size_t					size;
	t_gen					*gen;

	if ((gen = get_general(NULL)) == NULL || gen->i_client.fd == 0)
		return (-1);
	if (recv(gen->i_client.fd, &size, sizeof(size), 0) == -1)
		return (-1);
	if (size > 0)
	{
		if ((gen->cwd_server = ft_memalloc(size)) == NULL)
			return (-1);
		if (recv(gen->i_client.fd, &gen->cwd_server, size, 0) == -1)
			return (-1);
	}
	return (0);
}