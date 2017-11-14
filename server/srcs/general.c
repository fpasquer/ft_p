/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 10:19:45 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/14 18:04:57 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/server.h"

t_gen						*get_general(t_gen *ptr)
{
	static t_gen			*gen = NULL;

	if (ptr != NULL)
		gen = ptr;
	return (gen);
}

void						del_general(int const ret)
{
	t_gen					*gen;

#ifdef DEBUG
	fclose(debug);
#endif
	if ((gen = get_general(NULL)) != NULL)
	{
		if (gen->ptr != NULL)
			freeaddrinfo(gen->ptr);
		printf("\nServer closed\n");
	}
	exit(ret);
}
