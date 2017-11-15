/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 09:05:16 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/15 08:48:52 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/client.h"

int							func_exit(void)
{
	del_general(EXIT_SUCCESS);
	return (0);
}

int							func_change_win(void)
{
	t_gen					*gen;

	if ((gen = get_general(NULL)) == NULL)
		return (-1);
	gen->win = gen->win == CLIENT ? SERVER : CLIENT;
	if (add_infos(gen->win == CLIENT ? "Execute commandes on client" :
			"Execute commandes on server") != 0 || print_infos() != 0)
		return (-1);
	if (print_list_cwd(gen->cwd_client, gen->scr.client, gen->win == CLIENT ?
			true : false) != 0)
		return (-1);
	if (print_list_cwd(gen->cwd_server, gen->scr.server, gen->win == SERVER ?
			true : false) != 0)
		return (-1);
	return (0);
}

int							func_ls(void)
{
	return (0);
}

int							func_cd(void)
{
	return (0);
}

int							func_get(void)
{
	return (0);
}

int							func_put(void)
{
	return (0);
}

int							func_pwd(void)
{
	return (0);
}

int							func_login(void)
{
	return (0);
}

int							func_logout(void)
{
	return (0);
}

int							func_refresh_client(void)
{
	t_gen					*gen;

	if ((gen = get_general(NULL)) == NULL)
		return (-1);
	del_list_cwd(gen->cwd_client);
	if (set_list_cwd(&gen->cwd_client) != 0 ||
			print_list_cwd(gen->cwd_client, gen->scr.client, gen->win == CLIENT
			? true : false) != 0)
		return (-1);
	if (add_infos("Client have been refresh") != 0 || print_infos() != 0)
		return (-1);
	return (0);
}
