/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 17:26:06 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/02 18:12:32 by fpasquer         ###   ########.fr       */
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
	init_signaux();
	gen->scr = init_ncurses();
	gen->win = SERVER;
	if (set_list_cwd(&gen->cwd_client) != 0 ||
			print_list_cwd(gen->cwd_client, gen->scr.client, gen->win == CLIENT
			? true : false) != 0)
		return (EXIT_FAILURE);
	loop_term(gen);
	del_general(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
