/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 08:48:14 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/17 09:05:32 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/server.h"

t_cmd_manager				g_cmds[] = {
	{"LS", 2, func_ls},
	{"CD ", 3, func_cd},
	{"GET ", 4, func_get},
	{"PUT ", 4, func_put},
	{"PWD", 3, func_pwd},
	{"LOGIN ", 6, func_login},
	{"LOGOUT", 6, func_logout},
	{NULL, 0, NULL}
};

int							cmds_manager(t_gen *gen)
{
	unsigned int			i;

	if (gen == NULL || gen->cmd == NULL)
		return (-1);
	i = 0;
	while (g_cmds[i].cmd != NULL)
	{
		if (ft_strncmp(g_cmds[i].cmd, gen->cmd, g_cmds[i].len_cmp) == 0)
			return (g_cmds[i].f());
		i++;
	}
	printf("\tUser [%3d] : command not found\n", gen->sock_client);
	return (0);
}