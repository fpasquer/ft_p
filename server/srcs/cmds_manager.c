/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 08:48:14 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/17 14:10:09 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/server.h"

t_cmd_manager				g_cmds[] = {
	{"LS", 2, STRCMP, func_ls},
	{"CD ", 3, STRNCMP, func_cd},
	{"GET ", 4, STRNCMP, func_get},
	{"PUT ", 4, STRNCMP, func_put},
	{"PWD", 3, STRCMP, func_pwd},
	{"LOGIN ", 6, STRNCMP, func_login},
	{"LOGOUT", 6, STRCMP, func_logout},
	{NULL, 0, STRCMP, NULL}
};

int							cmds_manager(t_gen *gen)
{
	unsigned int			i;

	if (gen == NULL || gen->cmd == NULL)
		return (-1);
	i = 0;
	while (g_cmds[i].cmd != NULL)
	{
		if (g_cmds[i].type == STRCMP)
		{
			if (ft_strcmp(g_cmds[i].cmd, gen->cmd) == 0)
				return (g_cmds[i].f());
		}
		else
			if (ft_strncmp(g_cmds[i].cmd, gen->cmd, g_cmds[i].len_cmp) == 0)
				return (g_cmds[i].f());
		i++;
	}
	if (gen->cmd[0] != '\0')
		printf("\tUser[%3d]: cmd not found '%s'\n", gen->sock_client, gen->cmd);
	ft_memdel((void**)&gen->cmd);
	return (0);
}