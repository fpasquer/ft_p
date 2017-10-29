/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 20:56:46 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/29 21:32:15 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../general_incs/general.h"

t_gen						*get_general(void)
{
	static t_gen			*gen;

	if (gen == NULL)
		gen = ft_memalloc(sizeof(gen));
	return (gen);
}

void						del_general(void)
{
	void					*ptr;
	t_gen					*gen;

	if ((gen = get_general()) == NULL)
		return ;
	ptr = &gen->scr;
	del_ncurses(gen->scr);
	ft_memdel((void**)&gen);
}
