/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_get_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 16:51:17 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/18 13:13:53 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../general_incs/general.h"

# define BUFF_SIZE_RECV 5

static size_t				get_size_tab(char **list_cwd)
{
	unsigned int			i;
	size_t					ret;

	if (list_cwd == NULL)
		return (0);
	ret = 0;
	i = 0;
	while (list_cwd[i] != NULL)
		ret += ft_strlen(list_cwd[i++]);
	return (i > 0 ? ret + i - 1 : 0);
}

int							send_tab(int const sock, char *str)
{
	size_t					len;

	if (sock < 0 || str == NULL || (len = ft_strlen(str)) == 0)
		return (-1);
	if (send(sock, &len, sizeof(len), 0) < 0)
		return (-1);
	if (send(sock, str, len, 0) < 0)
		return (-1);
	return (0);
}

char						*get_tab(int const sock)
{
	char					*buff;
	size_t					len;

	if (sock < 0)
		return (NULL);
	if (recv(sock, &len, sizeof(len), 0) < 0)
		return (NULL);
	if ((buff = ft_memalloc(len + 1)) == NULL)
		return (NULL);
	if (recv(sock, buff, len, 0) < 0)
		return (NULL);
	return (buff);
}

int							send_tab_2d(int const sock, char **tab)
{
	char					*buff;
	unsigned int			i;
	size_t					len;

	if (sock < 0 || tab == NULL || *tab == NULL)
		return (-1);
	if ((len = get_size_tab(tab)) == 0)
		return (-1);
	if ((buff = ft_memalloc(len + 1)) == NULL)
		return (-1);
	i = 0;
	while (tab[i] != NULL)
	{
		if (ft_strncat(buff, tab[i++], len) != buff)
			return (-1);
		if (tab[i] != NULL)
			if (ft_strncat(buff, "*", len) != buff)
				return (-1);
	}
	if (send(sock, &len, sizeof(len), 0) < 0)
		return (-1);
	if (send(sock, buff, len, 0) < 0)
		return (-1);
	ft_memdel((void**)&buff);
	return (0);
}

char						**get_tab_2d(int const sock)
{
	char					**list;
	char					*buff;

	if ((buff = get_tab(sock)) == NULL)
		return (NULL);
	list = ft_strsplit(buff, '*');
	ft_memdel((void**)&buff);
	return (list);
}