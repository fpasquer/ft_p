/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_cwd_client.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 13:33:17 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/15 14:03:35 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/server.h"

static size_t				get_size_list_cwd(char **list_cwd)
{
	unsigned int			i;
	size_t					ret;

	if (list_cwd == NULL)
		return (0);
	ret = 0;
	i = 0;
	while (list_cwd[i] != NULL)
		ret += ft_strlen(list_cwd[i++]);
	printf("i = %u\n", i);
	return (i > 0 ? ret + i - 1 : 0);
}

int							send_cwd_server(t_gen const *gen)
{
	unsigned int			i;
	char					*buff;
	size_t					len;

	if (gen == NULL)
		return (-1);
	if ((len = get_size_list_cwd(gen->cwd_server.list)) == 0)
		return (-1);
	if ((buff = ft_memalloc(len + 1)) == NULL)
		return (-1);
	i = 0;
	while (gen->cwd_server.list[i] != NULL)
	{
		if (ft_strncat(buff, gen->cwd_server.list[i++], len) != buff)
			return (-1);
		if (gen->cwd_server.list[i] != NULL)
			if (ft_strncat(buff, " ", len) != buff)
				return (-1);
	}
	printf("buff ='%s' len = %zu\n", buff, len);
	if (send(gen->sock_client, &len, sizeof(len), 0) != 0)
		return (-1);
	ft_memdel((void**)&buff);
	return (0);
}