/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 17:26:06 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/30 07:36:56 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/client.h"

void						need_param(char const *name_bin)
{
	if (name_bin != NULL)
		ft_putstr_fd(name_bin, STDERR_FILENO);
	ft_putstr_fd(" need ip and port\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

int							main(int argc, char **argv)
{
	t_gen					*gen;

	if (argc <= 2)
		need_param(argv[0]);
	if ((gen = get_general(ft_memalloc(sizeof(*gen)))) == NULL)
		return (EXIT_FAILURE);
	gen->scr = init_ncurses();
	loop_client(gen->scr);
	del_general();
	return (EXIT_SUCCESS);
}
