/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 09:05:16 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/01 18:43:26 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/client.h"

int							func_exit(void)
{
	del_general(EXIT_SUCCESS);
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
	wclear(gen->scr.client);
	box(gen->scr.client, ACS_VLINE, ACS_HLINE);
	del_list_cwd(gen->cwd_client);
	if (set_list_cwd(&gen->cwd_client) != 0 ||
			print_list_cwd(gen->cwd_client, gen->scr.client) != 0)
		return (-1);
	return (0);
}
