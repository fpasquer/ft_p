/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 08:45:03 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/17 15:52:06 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/server.h"

int							func_ls(void)
{
	t_gen					*gen;

	if ((gen =  get_general(NULL)) == NULL || gen->sock_client <= 0)
		return (-1);
	if (send_tab(gen->sock_client, "LS success") < 0)
		return (-1);
	printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);
	return (0);
}

int							func_cd(void)
{
	t_gen					*gen;

	if ((gen =  get_general(NULL)) == NULL || gen->sock_client <= 0)
		return (-1);
	if (send_tab(gen->sock_client, "CD success") < 0)
		return (-1);
	printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);
	return (0);
}

int							func_get(void)
{
	t_gen					*gen;

	if ((gen =  get_general(NULL)) == NULL || gen->sock_client <= 0)
		return (-1);
	if (send_tab(gen->sock_client, "GET success") < 0)
		return (-1);
	printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);
	return (0);
}

int							func_put(void)
{
	t_gen					*gen;

	if ((gen =  get_general(NULL)) == NULL || gen->sock_client <= 0)
		return (-1);
	if (send_tab(gen->sock_client, "PUT success") < 0)
		return (-1);
	printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);
	return (0);
}

int							func_pwd(void)
{
	t_gen					*gen;

	if ((gen =  get_general(NULL)) == NULL || gen->sock_client <= 0)
		return (-1);
	if (send_tab(gen->sock_client, "PWD success") < 0)
		return (-1);
	printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);
	return (0);
}

int							func_login(void)
{
	t_gen					*gen;

	if ((gen =  get_general(NULL)) == NULL || gen->sock_client <= 0)
		return (-1);
	if (send_tab(gen->sock_client, "LOGIN success") < 0)
		return (-1);
	printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);
	return (0);
}

int							func_logout(void)
{
	t_gen					*gen;

	if ((gen =  get_general(NULL)) == NULL || gen->sock_client <= 0)
		return (-1);
	if (send_tab(gen->sock_client, "LOGOUT success") < 0)
		return (-1);
	printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);
	return (0);
}

int							func_refresh_server(void)
{
	t_gen					*gen;

	if ((gen =  get_general(NULL)) == NULL || gen->sock_client <= 0)
		return (-1);
	if (set_list_cwd(&gen->cwd_server, "/", gen->cwd_server.cwd_show) != 0)
		return (-1);
	if (send_cwd_server(gen) != 0)
		return (-1);
	printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);
	return (0);
}