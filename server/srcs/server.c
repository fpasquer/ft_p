/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 10:28:57 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/15 11:40:21 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/server.h"
#ifdef DEBUG
	#include <ncurses.h>
#endif

/*static char				*get_node_ip(struct addrinfo const *node, char *buff,
		size_t const buff_size)
{
	void				*sin_addr;

	if (node == NULL || buff == NULL )
		return (NULL);
	if (node->ai_family == AF_INET)
		sin_addr = &((struct sockaddr_in*)node->ai_addr)->sin_addr;
	else if (node->ai_family == AF_INET6)
		sin_addr = &((struct sockaddr_in6*)node->ai_addr)->sin6_addr;
	else
		return (NULL);
	if (sin_addr == NULL || inet_ntop(node->ai_family, sin_addr, buff,
			buff_size) == NULL)
		return (NULL);
	return (buff);
}

#ifdef DEBUG
static int					print_addr(struct addrinfo const *node)
{

	char					buff_addr[INET6_ADDRSTRLEN];
	size_t					size_buff;

	if (node == NULL)
		return (-1);
	size_buff = sizeof(buff_addr);
	ft_bzero(buff_addr, size_buff);
	fprintf(debug, "ai_flags     = %d\n", node->ai_flags);
	fprintf(debug, "ai_family    = %s\n", node->ai_family == AF_INET ? "IPV4" : "IPV6");
	fprintf(debug, "ai_socktype  = %d\n", node->ai_socktype);
	fprintf(debug, "ai_addrlen   = %zd\n", node->ai_addrlen);
	if (get_node_ip(node, buff_addr, size_buff) != NULL)
		fprintf(debug, "ai_addr      = %s\n", buff_addr);
	fprintf(debug, "ai_canonname = %s\n\n", node->ai_canonname);
	return (0);
}
#endif

int							loop_server(void)
{
	struct addrinfo			hints;
	struct addrinfo			*curs;
	struct addrinfo			*ptr;
	t_gen					*gen;

	if ((gen = get_general(NULL)) == NULL)
		return (-1);
	ft_bzero(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	if (getaddrinfo("www.google.com", NULL, &hints, &ptr) != 0)
		return (-1);
	curs = ptr;
	while (curs != NULL)
	{
		if (print_addr(curs) != 0)
			break ;
		curs = curs->ai_next;
	}
	freeaddrinfo(ptr);
	return (0);
}*/

static int					config_server(t_gen *gen,
		struct addrinfo const node)
{
	int						optval;

	if (gen == NULL)
		return (-1);
	if ((gen->sock_server = socket(node.ai_family, node.ai_socktype,
			node.ai_protocol)) < 0)
		return (-1);
	if (node.ai_family == AF_INET6)
		if (setsockopt(gen->sock_server, IPPROTO_IPV6, IPV6_V6ONLY, &optval,
				sizeof(optval)) == -1)
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
	if (set_list_cwd(&gen->cwd_server, "/", gen->cwd_server.cwd_show) != 0)
		return (-1);
	printf("\e[1;1H\e[2JServer opened on the port %s\n", gen->port);
	return (0);
}

int							init_server(t_gen *gen)
{
	int						ret;
	struct addrinfo			*curs;

	if (gen == NULL || gen->port == NULL)
		return (-1);
	gen->hints.ai_family = AF_INET6;
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

int							loop_server(void)
{
	t_gen					*gen;
	socklen_t				clientAddressLength;
	struct sockaddr_storage	clientAddress;

	if ((gen = get_general(NULL)) == NULL)
		return (-1);
// #ifdef DEBUG
// 	int i = 0;
// 	while (cwd.list[i] != NULL)
// 	{
// 		printf("\t%s\n", cwd.list[i]);
// 		i++;
// 	}
// 	del_list_cwd(cwd);
// #endif
	while (1)
	{
		printf("Attente de connexion sur le port %s\n", gen->port);
		if ((gen->sock_client = accept(gen->sock_server, (struct sockaddr *)
				&clientAddress, &clientAddressLength)) == -1)
			return (-1);
		printf("Success\n");
	}
	return (0);
}