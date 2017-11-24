/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 15:15:49 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/24 08:16:57 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/server.h"

t_gen						*get_general(t_gen *gen)
{
	static t_gen			*tmp = NULL;

	if (gen != NULL)
		tmp = gen;
	return (tmp);
}

int							del_general(int const ret)
{
	t_gen					*gen;

	if ((gen = get_general(NULL)) == NULL)
		return (-1);
	ft_memdel((void**)&gen);
	printf("\nServer closed\n");
	exit(ret);
	return (0);
}
