/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 10:28:57 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/14 18:03:28 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/server.h"

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

static int				print_addr(struct addrinfo const *node)
{
	char				buff_addr[INET6_ADDRSTRLEN];
	size_t				size_buff;

	if (node == NULL)
		return (-1);
	size_buff = sizeof(buff_addr);
	ft_bzero(buff_addr, size_buff);
	printf("ai_flags     = %d\n", node->ai_flags);
	printf("ai_family    = %s\n", node->ai_family == AF_INET ? "IPV4" : "IPV6");
	printf("ai_socktype  = %d\n", node->ai_socktype);
	printf("ai_addrlen   = %zd\n", node->ai_addrlen);
	if (get_node_ip(node, buff_addr, size_buff) != NULL)
		printf("ai_addr      = %s\n", buff_addr);
	printf("ai_canonname = %s\n\n", node->ai_canonname);
	return (0);
}

int						loop_server(void)
{
	struct addrinfo		hints;
	struct addrinfo		*curs;
	struct addrinfo		*ptr;
	t_gen				*gen;

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

int						init_server(t_gen *gen)
{
	if (gen == NULL || gen->port == NULL)
		return (-1);
	gen->hints.ai_family = AF_INET6;
	gen->hints.ai_socktype = SOCK_STREAM;
	gen->hints.ai_flags = AI_PASSIVE;
	printf("\e[1;1H\e[2JServer opened on the port %s\n", gen->port);
	return (0);
}

int						loop_server(void)
{
	t_gen				*gen;

	if ((gen = get_general(NULL)) == NULL)
		return (-1);
	while (1)
	{
		;
	}
	return (0);
}
