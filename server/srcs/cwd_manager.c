/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwd_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 16:08:30 by fpasquer          #+#    #+#             */
/*   Updated: 2017/12/02 16:33:41 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/server.h"

t_cmd_manager				g_cmds[] = {
	{"LS", 2, STRCMP, func_ls},
	{"CD ", 3, STRNCMP, func_cd},
	{"GET ", 4, STRNCMP, func_get},
	{"PUT", 3, STRCMP, func_put},
	{"PWD", 3, STRCMP, func_pwd},
	{"LOGOUT", 6, STRCMP, func_logout},
	{"REFRESH", 7, STRCMP, func_refresh_server},
	{NULL, 0, STRCMP, NULL}
};

int							cmds_manager(t_client *gen)
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
		{
			if (ft_strncmp(g_cmds[i].cmd, gen->cmd, g_cmds[i].len_cmp) == 0)
				return (g_cmds[i].f());
		}
		i++;
	}
	if (gen->cmd[0] != '\0')
		printf("\tUser[%3d]: cmd not found '%s'\n", gen->sock_client, gen->cmd);
	ft_memdel((void**)&gen->cmd);
	if (send_tab(gen->sock_client, "ft_p: command not found") < 0)
		return (-1);
	return (0);
}
