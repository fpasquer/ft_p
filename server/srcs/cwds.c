/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 16:16:38 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/24 08:27:13 by fpasquer         ###   ########.fr       */
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

int							func_put(void)
{
	t_client				*gen;

	if ((gen = get_client(NULL)) == NULL || gen->sock_client <= 0)
		return (-1);
	if (send_tab(gen->sock_client, "PUT success") < 0)
		return (-1);
	printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);
	ft_memdel((void**)&gen->cmd);
	return (0);
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
