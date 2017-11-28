/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 08:05:54 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/28 08:49:22 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/client.h"

static int					error_time_out(void)
{
	del_general(-1);
	return (-1);
}

static int					login_server_ipv4(t_gen *gen)
{
	struct sockaddr_in		sin;
	struct protoent			*proto;

	if (gen == NULL || (proto = getprotobyname("tcp")) == NULL)
		return (-1);
	if ((gen->i_client.fd = socket(PF_INET, SOCK_STREAM, proto->p_proto)) < 0)
		return (-1);
	ft_bzero(&sin, sizeof(sin));
	if (inet_pton(AF_INET, gen->i_client.ip, &sin.sin_addr.s_addr) != 1)
		return (-1);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(ft_atoi(gen->i_client.port));
	if (connect(gen->i_client.fd, (struct sockaddr*)&sin, sizeof(sin)) == -1)
		return (error_time_out());
	return (0);
}

static int					login_server_ipv6(t_gen *gen)
{
	struct sockaddr_in6		sin;

	if (gen == NULL)
		return (-1);
	ft_bzero(&sin, sizeof(sin));
	if ((gen->i_client.fd = socket(PF_INET6, SOCK_STREAM, 0)) < 0)
		return (-1);
	if (inet_pton(AF_INET6, gen->i_client.ip, &sin.sin6_addr) != 1)
		return (-1);
	sin.sin6_family = AF_INET6;
	sin.sin6_port = htons((short)ft_atoi(gen->i_client.port));
	if (connect(gen->i_client.fd, (struct sockaddr*)&sin, sizeof(sin)) == -1)
		return (error_time_out());
	return (0);
}

int							login_server(void)
{
	t_gen					*gen;

	if ((gen = get_general(NULL)) == NULL || gen->scr.infos == NULL)
		return (-1);
	if ((gen->i_client.type_ip == IPV4) ? login_server_ipv4(gen) :
			login_server_ipv6(gen) != 0)
		return (-1);
	if (add_infos("Login server") != 0)
		return (-1);
	return (0);
}

void						logout_server(void)
{
	t_gen					*gen;

	if ((gen = get_general(NULL)) == NULL)
		return ;
	if (gen->i_client.fd > 0)
	{
		close(gen->i_client.fd);
		add_infos("Logout server");
	}
}
