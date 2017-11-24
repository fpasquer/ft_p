/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 09:05:16 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/24 09:03:13 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/client.h"

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

int							func_ls(void)
{
	t_gen					*gen;

	if ((gen = get_general(NULL)) == NULL)
		return (-1);
	if (gen->win == SERVER)
		return (save_ret_server(gen->i_client.list_cmd, gen->cwd_server.list));
	return (save_ret_server(gen->i_client.list_cmd, gen->cwd_client.list));
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
