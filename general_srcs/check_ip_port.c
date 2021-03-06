/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ip_port.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 19:11:49 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/28 09:00:25 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../general_incs/general.h"

#define MAX_PORT 65535
#define MIN_PORT 1500

char						*get_ip(char const *ip, t_type_ip *type_ip)
{
	if (ip == NULL || type_ip == NULL)
		return (NULL);
	if (ft_strcmp("localhost", ip) == 0)
	{
		(*type_ip) = IPV6;
		return (ft_strdup("::1"));
	}
	if (((*type_ip) = check_ip(ip)) == false)
		return (NULL);
	return (ft_strdup(ip));
}

int							check_ip(char const *ip)
{
	char					dest[INET6_ADDRSTRLEN];

	if (ip == NULL)
		return (false);
	ft_bzero(&dest, sizeof(dest));
	if (inet_pton(AF_INET, ip, &dest) == 1)
		return (AF_INET);
	else if (inet_pton(AF_INET6, ip, &dest) == 1)
		return (AF_INET6);
	return (false);
}

bool						check_port(char const *port)
{
	int						port_int;

	if (port == NULL || ft_is_number((char *)port) == false)
		return (false);
	if ((port_int = ft_atoi(port)) > MAX_PORT || port_int < MIN_PORT)
		return (false);
	return (true);
}
