/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 12:43:08 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/29 19:36:15 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../general_incs/general.h"

static t_cmd_manager		g_cmds[] = {
	{(char[]){27, 0, 0, 0, 0, 0}, func_exit},
	{NULL, NULL}
};

int							get_cmd(char cmd[SIZE_CMD])
{
	char					b[SIZE_BUFF];
	int						i;

	if (cmd == NULL)
		return (-1);
	ft_bzero(cmd, sizeof(char) * SIZE_CMD);
	i = 0;
	while (i < SIZE_CMD - 1)
	{
		if (get_key_pressed(b) != 0)
			break ;
		if (ft_strncmp(b, (char[]){27, 0, 0, 0, 0, 0}, SIZE_BUFF) == 0)
			exit(10);
		if (b[0] >= 32 && b[0] <= 127)
			cmd[i++] = b[0];
		if (ENTER)
			break ;
	}
	return (0);
}


