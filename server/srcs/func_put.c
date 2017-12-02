/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_put.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 11:23:59 by fpasquer          #+#    #+#             */
/*   Updated: 2017/12/02 17:22:15 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/server.h"

static int					execute_put(int const sock)
{
	t_data_file				file;

	if (recv(sock, &file.size_datas, sizeof(file.size_datas), 0) < 0)
		return (send_tab(sock, "PUT failure size datas"));
	printf("User[%3d] size %zu\n", sock, file.size_datas);
	if ((file.datas = ft_memalloc(file.size_datas)) == NULL)
		return (send_tab(sock, "PUT malloc failure"));
	if (recv(sock, file.datas, file.size_datas, 0) < 0)
		return (send_tab(sock, "PUT failure datas"));
	if (creat_file(file.datas, NULL) != 0)
		return (send_tab(sock, "PUT failure Creat file"));
	ft_memdel((void**)&file.datas);
	return (send_tab(sock, "PUT success"));
}

int							func_put(void)
{
	int						ret;
	t_client				*gen;

	if ((gen = get_client(NULL)) == NULL || gen->sock_client <= 0)
		return (-1);
	ret = execute_put(gen->sock_client);
	ft_memdel((void**)&gen->cmd);
	return (ret);
}
