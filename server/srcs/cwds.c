/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 16:16:38 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/24 11:10:53 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/server.h"

int							func_ls(void)
{
	t_client				*gen;

	if ((gen = get_client(NULL)) == NULL || gen->sock_client <= 0)
		return (-1);
	if (send_tab(gen->sock_client, "LS success") < 0)
		return (-1);
	printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);
	ft_memdel((void**)&gen->cmd);
	return (0);
}

void						print_memory(void *addr, size_t len)
{
	unsigned char			*tmp;
	size_t					i;

	i = 0;
	tmp = (unsigned char *)addr;
	while (i < len)
	{
		printf("%p = %c = %d\n", tmp + i, ft_isprint((int)tmp[i]) == true ? tmp[i] : '.', tmp[i]);
		i++;
	}
} 

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

int							func_pwd(void)
{
	t_client				*gen;

	if ((gen = get_client(NULL)) == NULL || gen->sock_client <= 0)
		return (-1);
	if (send_tab(gen->sock_client, "PWD success") < 0)
		return (-1);
	printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);
	ft_memdel((void**)&gen->cmd);
	return (0);
}

int							func_logout(void)
{
	del_client(EXIT_SUCCESS);
	return (0);
}

int							func_refresh_server(void)
{
	t_client				*gen;

	if ((gen = get_client(NULL)) == NULL || gen->sock_client <= 0)
		return (-1);
	del_list_cwd(gen->cwd_server);
	if (set_list_cwd(&gen->cwd_server, gen->cwd_server.cwd_show,
			gen->cwd_server.cwd_show) != 0)
		return (-1);
	if (send_cwd_server(gen) != 0)
		return (-1);
	printf("\tUser [%3d] is on %s%s\n", gen->sock_client, gen->racine,
			gen->current_dir);
	ft_memdel((void**)&gen->cmd);
	return (0);
}
