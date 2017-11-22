/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 15:54:46 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/22 19:24:24 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/server.h"

static t_client				*init_client(int const sock_client,
		int const sock_server, t_client *client)
{
	if (client == NULL)
		return (NULL);
	ft_bzero(client, sizeof(*client));
	client->sock_client = sock_client;
	client->sock_server = sock_server;
	if (set_list_cwd(&client->cwd_server, "/", client->cwd_server.cwd_show) != 0)
		return (NULL);
	if (getcwd(client->racine, SIZE_CWD) == NULL)
		return (NULL);
	if (ft_strncpy(client->current_dir, "/", SIZE_CWD) != client->current_dir)
		return (NULL);
	return (get_client(client));
}

t_client					*get_client(t_client *client)
{
	static t_client			*ptr;

	if (client != NULL)
		ptr = client;
	return (ptr);
}

void						del_client(int const ret)
{
	t_client				*client;

	if ((client = get_client(NULL)) != NULL)
	{
		if (client->cmd != NULL)
			ft_memdel((void**)&client->cmd);
		printf("End client %d\n", client->sock_client);
		if (client->sock_client > 0)
			close(client->sock_client);
	}
	exit(ret);
}

void						new_client(int sock_client, int sock_server)
{
	t_client				client;

	if (sock_client < 0 || sock_server < 0 ||
			init_client(sock_client, sock_server, &client) != &client)
		del_client(EXIT_FAILURE);
	printf("New client %d\n", sock_client);
	if (send_cwd_server(&client) != 0)
		del_client(EXIT_FAILURE);
	while (1)
		if ((client.cmd = get_tab(client.sock_client)) != NULL)
			if (cmds_manager(&client) != 0)
				break ;
	del_client(EXIT_FAILURE);
}