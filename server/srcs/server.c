/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 15:27:03 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/28 08:50:50 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/server.h"

static int					config_server(t_gen *gen,
		struct addrinfo const node)
{
	if (gen == NULL)
		return (-1);
	if ((gen->sock_server = socket(node.ai_family, node.ai_socktype,
			node.ai_protocol)) < 0)
		return (-1);
	if (bind(gen->sock_server, node.ai_addr, node.ai_addrlen) == -1)
		return (-1);
	return (true);
}

static int					creat_server(t_gen *gen)
{
	if (gen == NULL)
		return (-1);
	if (listen(gen->sock_server, 0) == -1)
		return (-1);
	printf("\e[1;1H\e[2JServer opened on the port %s\n", gen->port);
	return (0);
}

int							init_server(char const *port)
{
	int						ret;
	struct addrinfo			*curs;
	t_gen					*gen;

	if ((gen = get_general(NULL)) == NULL)
		return (-1);
	if (ft_strncpy(gen->port, port, MAX_LEN_PORT) != gen->port)
		return (-1);
	gen->hints.ai_family = AF_UNSPEC;
	gen->hints.ai_socktype = SOCK_STREAM;
	gen->hints.ai_flags = AI_PASSIVE;
	if ((ret = getaddrinfo(NULL, gen->port, &gen->hints, &gen->ptr)) != 0)
		return (-1);
	if ((curs = gen->ptr) == NULL)
		return (-1);
	while (curs != NULL)
	{
		if (config_server(gen, *curs) == true)
			return (creat_server(gen));
		curs = curs->ai_next;
	}
	return (-1);
}

void						loop_server(t_gen *gen)
{
	int						sock_client;
	socklen_t				client_address_length;
	struct sockaddr_storage	client_address;
	pid_t					pid;

	if (gen == NULL)
		return ;
	printf("waiting for client(s) on port %s\n", gen->port);
	while (1)
	{
		if ((sock_client = accept(gen->sock_server, (struct sockaddr *)
				&client_address, &client_address_length)) == -1)
			return ;
		if ((pid = fork()) == -1)
			return ;
		else if (pid == 0)
			new_client(sock_client, gen->sock_server);
	}
}
