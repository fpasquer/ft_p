/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 08:26:34 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/24 17:15:57 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/server.h"

static int					check_cd(char const *racine, char *current_dir,
	size_t const size_current_dir)
{
	char					buff[SIZE_CWD];

	if (racine == NULL || getcwd(buff, SIZE_CWD) != buff)
		return (-1);
	if (ft_strstr(buff, racine) == buff)
		return (true);
	if (chdir(racine) != 0 || ft_strncpy(current_dir, "/", size_current_dir)
			!= current_dir)
		return (-1);
	return (false);
}

int							func_cd(void)
{
	char					*path;
	int						i;
	t_client				*gen;

	if ((gen = get_client(NULL)) == NULL || gen->sock_client <= 0)
		return (-1);
	path = &gen->cmd[3];
	i = 0;
	while (ft_isspace(path[i]) == true)
		i++;
	if ((path = path[i] == '/' ? ft_strjoin(gen->racine, &path[i]) :
			ft_multijoin(3, gen->racine, gen->current_dir, &path[i])) == NULL)
		return (-1);
	i = chdir(path);
	ft_memdel((void**)&path);
	ft_memdel((void**)&gen->cmd);
	if (i != 0 || check_cd(gen->racine, gen->current_dir, SIZE_CWD) != true)
		return (send_tab(gen->sock_client, "CD FAILURE"));
	if (getcwd(gen->current_dir, SIZE_CWD) != gen->current_dir || ft_memmove(
			gen->current_dir, &gen->current_dir[ft_strlen(gen->racine)],
			SIZE_CWD) != gen->current_dir || ft_strncat(gen->current_dir, "/",
			SIZE_CWD) != gen->current_dir || send_tab(gen->sock_client,
			"CD success") < 0)
		return (-1);
	return (0);
}
