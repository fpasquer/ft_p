/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 08:57:04 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/24 08:58:15 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/client.h"

static int					error_cmd(char const *error)
{
	if (error == NULL)
		return (-1);
	if (add_infos(error) != 0 || print_infos() != 0)
		return (-1);
	return (0);
}

static int					cmd_for_server(t_gen *gen)
{
	char					*info;

	if (gen == NULL || gen->i_client.fd <= 0)
		return (-1);
	if (send_tab(gen->i_client.fd, gen->cmd) < 0 || (info = get_tab(
			gen->i_client.fd)) == NULL)
		return (-1);
	if (add_infos(info) != 0)
		return (-1);
	ft_memdel((void**)&info);
	return (0);
}

int							func_cd(void)
{
	char					*path_full;
	char					*path;
	int						ret;
	unsigned int			i;
	t_gen					*gen;

	if ((gen = get_general(NULL)) == NULL)
		return (gen == NULL ? -1 : 0);
	if (gen->win == SERVER)
	{
		if (cmd_for_server(gen) != 0 || func_refresh_server() != 0)
			return (-1);
		return (0);
	}
	i = 0;
	if ((*(path = &gen->cmd[3])) == '\0')
		return (error_cmd("CD need dest path"));
	while (ft_isspace(path[i]) == true)
		i++;
	if ((path_full = path[i] == '/' ? ft_strdup(&path[i]) : ft_multijoin(3,
			gen->cwd_client.cwd, "/", &path[i])) == NULL)
		return (-1);
	ret = chdir(path_full);
	ft_memdel((void**)&path_full);
	return (ret == -1 ? error_cmd("CD path unvalable") : func_refresh_client());
}
