/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 08:45:03 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/17 14:36:34 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/server.h"

int							func_ls(void)
{
	t_gen					*gen;

	if ((gen =  get_general(NULL)) == NULL || gen->sock_client <= 0)
		return (-1);
	if (send_tab(gen->sock_client, "LS") < 0)
		return (-1);
	printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);
	return (0);
}

int							func_cd(void)
{
	t_gen					*gen;

	if ((gen =  get_general(NULL)) == NULL || gen->sock_client <= 0)
		return (-1);
	if (send_tab(gen->sock_client, "CD") < 0)
		return (-1);
	printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);
	return (0);
}

int							func_get(void)
{
	t_gen					*gen;

	if ((gen =  get_general(NULL)) == NULL || gen->sock_client <= 0)
		return (-1);
	if (send_tab(gen->sock_client, "GET") < 0)
		return (-1);
	printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);
	return (0);
}

int							func_put(void)
{
	t_gen					*gen;

	if ((gen =  get_general(NULL)) == NULL || gen->sock_client <= 0)
		return (-1);
	if (send_tab(gen->sock_client, "PUT") < 0)
		return (-1);
	printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);
	return (0);
}

int							func_pwd(void)
{
	t_gen					*gen;

	if ((gen =  get_general(NULL)) == NULL || gen->sock_client <= 0)
		return (-1);
	if (send_tab(gen->sock_client, "PWD") < 0)
		return (-1);
	printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);
	return (0);
}

int							func_login(void)
{
	t_gen					*gen;

	if ((gen =  get_general(NULL)) == NULL || gen->sock_client <= 0)
		return (-1);
	if (send_tab(gen->sock_client, "LOGIN") < 0)
		return (-1);
	printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);
	return (0);
}

int							func_logout(void)
{
	t_gen					*gen;

	if ((gen =  get_general(NULL)) == NULL || gen->sock_client <= 0)
		return (-1);
	if (send_tab(gen->sock_client, "LOGOUT") < 0)
		return (-1);
	printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);
	return (0);
}

int							func_refresh_server(void)
{
	t_gen					*gen;

	if ((gen =  get_general(NULL)) == NULL || gen->sock_client <= 0)
		return (-1);
	if (send_tab(gen->sock_client, "Refresh server") < 0)
		return (-1);
	printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);
	return (0);
}