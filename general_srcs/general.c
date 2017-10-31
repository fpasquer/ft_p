/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 20:56:46 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/31 08:12:40 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../general_incs/general.h"

t_gen						*get_general(t_gen *ptr)
{
	static t_gen			*gen = NULL;

#ifdef DEBUG
	debug = fopen("debug.txt", "w+");
#endif
	if (ptr != NULL)
		gen = ptr;
	return (gen);
}

void						del_general(int const ret)
{
	t_gen					*gen;

	if ((gen = get_general(NULL)) == NULL)
		return ;
	del_list_cwd(gen->cwd_client);
	del_list_cwd(gen->cwd_server);
	del_ncurses(gen); // ne fonctionne pas
	ft_memdel((void**)&gen);
#ifdef DEBUG
	fclose(debug);
#endif
	exit(ret);
}
