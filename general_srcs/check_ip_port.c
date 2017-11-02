/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ip_port.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 19:11:49 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/02 20:53:44 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../general_incs/general.h"

#define MAX_IP 255
#define MIN_IP 0
#define MAX_NUMBER 3
#define NB_NUMBER 4
#define MAX_PORT 65535
#define MIN_PORT 1

static char					*const_ip(char const *ip, t_type_ip **type_ip)
{
	if (ip == NULL || type_ip == NULL || (*type_ip) == NULL)
		return (NULL);
	if (((*(*type_ip)) = IPV4) == IPV4 && ft_strcmp("localhost", ip) == 0)
		return (ft_strdup("127.0.0.1"));
	else if (ft_strcmp("::1", ip) == 0 && ((*(*type_ip)) = IPV6) == IPV6)
		return (ft_strdup(ip));
	return (NULL);
}

char						*get_ip(char const *ip, t_type_ip *type_ip)
{
	char					*ret;
	int						i;
	int						j;
	int						nb;
	int						count_number;

	ret = NULL;
	if (ip == NULL || type_ip == NULL || (ret = const_ip(ip, &type_ip)) != NULL)
		return (ret);
	i = -1;
	j = 0;
	count_number = 0;
	while (ip[++i] != '\0' && count_number <= MAX_NUMBER)
		if (ft_isdigit(ip[i]) == true)
			j = count_number++ == 0 ? j + 1 : j;
		else if (ip[i] == '.' && i > 0 && ip[i - 1] != '.')
		{
			if ((nb = ft_atoi(&ip[i - count_number])) > MAX_IP || nb < MIN_IP)
				return (NULL);
			count_number = 0;
		}
		else
			return (NULL);
	return (j == 4 ? ft_strdup(ip) : NULL);
}

bool						check_port(char *port)
{
	int						port_int;

	if (port == NULL || ft_is_number(port) == false)
		return (false);
	if ((port_int = ft_atoi(port)) > MAX_PORT || port_int < MIN_PORT)
		return (false);
	return (true);
}
