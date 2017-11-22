/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 09:05:16 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/22 19:21:25 by fpasquer         ###   ########.fr       */
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

/*
int							func_refresh_server(void)
{
	t_gen					*gen;

	if ((gen = get_general(NULL)) == NULL)
		return (-1);
	if (send_tab(gen->i_client.fd, "REFRESH") < 0)
		return (-1);
	del_list_cwd(gen->cwd_server);
	if (set_list_cwd_server() != 0 || print_list_cwd(gen->cwd_server,
			gen->scr.server, gen->win == SERVER ? true : false) != 0)
		return (-1);
	return (0);
}*/

int							func_exit(void)
{
	t_gen					*gen;

	if ((gen = get_general(NULL)) == NULL)
		return (-1);
	if (send_tab(gen->i_client.fd, "LOGOUT") < 0)
		return (-1);
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

static int					func_client_up(t_gen *gen)
{
	int						nb_row_scr;

	if (gen == NULL)
		return (-1);
	nb_row_scr = LINES - 2 - HIGHT_INFO_WIN - HIGHT_TERM_WIN;
	if (gen->cwd_client.nb_row > nb_row_scr + gen->cwd_client.decalage)
	{
		gen->cwd_client.decalage++;
		if (print_list_cwd(gen->cwd_client, gen->scr.client, gen->win == CLIENT
				? true : false) != 0)
			return (-1);
		if (add_infos("Client scroll up") != 0)
			return (-1);
	}
	return (0);
}

static int					func_client_down(t_gen *gen)
{
	if (gen == NULL)
		return (-1);
	if (gen->cwd_client.decalage > 0)
	{
		gen->cwd_client.decalage--;
		if (print_list_cwd(gen->cwd_client, gen->scr.client, gen->win == CLIENT
				? true : false) != 0)
			return (-1);
		if (add_infos("Client scroll down") != 0)
			return (-1);
	}
	return (0);
}

static int					func_server_up(t_gen *gen)
{
	int						nb_row_scr;

	if (gen == NULL)
		return (-1);
	nb_row_scr = LINES - 2 - HIGHT_INFO_WIN - HIGHT_TERM_WIN;
	if (gen->cwd_server.nb_row > nb_row_scr + gen->cwd_server.decalage)
	{
		gen->cwd_server.decalage++;
		if (print_list_cwd(gen->cwd_server, gen->scr.server, gen->win == SERVER
				? true : false) != 0)
			return (-1);
		if (add_infos("Server scroll up") != 0)
			return (-1);
	}
	return (0);
}

static int					func_server_down(t_gen *gen)
{
	if (gen == NULL)
		return (-1);
	if (gen->cwd_server.decalage > 0)
	{
		gen->cwd_server.decalage--;
		if (print_list_cwd(gen->cwd_server, gen->scr.server, gen->win == SERVER
				? true : false) != 0)
			return (-1);
		if (add_infos("Server scroll down") != 0)
			return (-1);
	}
	return (0);
}

int							func_win_up(void)
{
	t_gen					*gen;

	if ((gen = get_general(NULL)) == NULL)
		return (-1);
	if (gen->win == SERVER)
		return (func_server_up(gen));
	return (func_client_up(gen));
}

int							func_win_down(void)
{
	t_gen					*gen;

	if ((gen = get_general(NULL)) == NULL)
		return (-1);
	if (gen->win == SERVER)
		return (func_server_down(gen));
	return (func_client_down(gen));
}

int							func_ls(void)
{
	t_gen					*gen;

	if ((gen = get_general(NULL)) == NULL)
		return (-1);
	if (gen->win == SERVER)
		return (save_ret_server(gen->i_client.list_cmd, gen->cwd_server.list));
	return (save_ret_server(gen->i_client.list_cmd, gen->cwd_client.list));
}

int							func_cd(void)
{
	char					*path_full;
	char					*path;
	int						ret;
	unsigned int			i;
	t_gen					*gen;

	if ((gen = get_general(NULL)) == NULL)
		return (-1);
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
	char					*rep[2];
	int						ret;
	t_gen					*gen;

	if ((gen = get_general(NULL)) == NULL)
		return (-1);
	if ((rep[0] = ft_strdup(gen->win == SERVER ? gen->cwd_server.cwd_show :
			gen->cwd_client.cwd_show)) == NULL)
		return (-1);
	rep[1] = NULL;
	ret = save_ret_server(gen->i_client.list_cmd, rep);
	ft_memdel((void**)&rep[0]);
	return (ret);
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
	if (set_list_cwd(&gen->cwd_client, NULL, gen->cwd_client.cwd_show) != 0 ||
			print_list_cwd(gen->cwd_client, gen->scr.client, gen->win == CLIENT
			? true : false) != 0)
		return (-1);
	if (add_infos("Update content client") != 0 || print_infos() != 0)
		return (-1);
	return (0);
}

int							func_refresh_server(void)
{
	t_gen					*gen;

	if ((gen = get_general(NULL)) == NULL)
		return (-1);
	if (send_tab(gen->i_client.fd, "REFRESH") < 0)
		return (-1);
	del_list_cwd(gen->cwd_server);
	if (set_list_cwd_server() != 0 || print_list_cwd(gen->cwd_server,
			gen->scr.server, gen->win == SERVER ? true : false) != 0)
		return (-1);
	return (0);
}