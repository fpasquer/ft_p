/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 10:19:45 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/15 11:43:10 by fpasquer         ###   ########.fr       */
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
		if (gen->sock_client >= 0)
			close(gen->sock_client);
		if (gen->sock_server >= 0)
			close(gen->sock_server);
		del_list_cwd(gen->cwd_server);
		printf("\nServer closed\n");
	}
	exit(ret);
}
