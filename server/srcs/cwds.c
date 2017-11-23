/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 16:16:38 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/23 14:54:43 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/server.h"

int							func_ls(void)
{
	t_client				*gen;

	if ((gen =  get_client(NULL)) == NULL || gen->sock_client <= 0)
		return (-1);
	if (send_tab(gen->sock_client, "LS success") < 0)
		return (-1);
	printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);
	ft_memdel((void**)&gen->cmd);
	return (0);
}

static int					check_cd(char const *racine, char *current_dir,
		size_t const size_current_dir)
{
	char					buff[SIZE_CWD];

	if (racine == NULL || getcwd(buff, SIZE_CWD) != buff)
		return (-1);
	if (strstr(buff, racine) == buff)
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

	if ((gen =  get_client(NULL)) == NULL || gen->sock_client <= 0)
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

int							func_get(void)
{
	t_client				*gen;

	if ((gen =  get_client(NULL)) == NULL || gen->sock_client <= 0)
		return (-1);
	if (send_tab(gen->sock_client, "GET success") < 0)
		return (-1);
	printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);
	ft_memdel((void**)&gen->cmd);
	return (0);
}

int							func_put(void)
{
	t_client				*gen;

	if ((gen =  get_client(NULL)) == NULL || gen->sock_client <= 0)
		return (-1);
	if (send_tab(gen->sock_client, "PUT success") < 0)
		return (-1);
	printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);
	ft_memdel((void**)&gen->cmd);
	return (0);
}

int							func_pwd(void)
{
	t_client				*gen;

	if ((gen =  get_client(NULL)) == NULL || gen->sock_client <= 0)
		return (-1);
	if (send_tab(gen->sock_client, "PWD success") < 0)
		return (-1);
	printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);
	ft_memdel((void**)&gen->cmd);
	return (0);
}

int							func_login(void)
{
	t_client				*gen;

	if ((gen =  get_client(NULL)) == NULL || gen->sock_client <= 0)
		return (-1);
	if (send_tab(gen->sock_client, "LOGIN success") < 0)
		return (-1);
	printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);
	ft_memdel((void**)&gen->cmd);
	return (0);
}

int							func_logout(void)
{
	del_client(EXIT_SUCCESS);
	return (0);
}

int							func_refresh_server(void)
{
	t_client				*gen;

	if ((gen =  get_client(NULL)) == NULL || gen->sock_client <= 0)
		return (-1);
	del_list_cwd(gen->cwd_server);
	if (set_list_cwd(&gen->cwd_server, gen->cwd_server.cwd_show,
			gen->cwd_server.cwd_show) != 0)
		return (-1);
	if (send_cwd_server(gen) != 0)
		return (-1);
	printf("\tUser [%3d] is on %s%s\n", gen->sock_client, gen->racine,
			gen->current_dir);
	ft_memdel((void**)&gen->cmd);
	return (0);
}