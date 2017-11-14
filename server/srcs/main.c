/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 17:49:55 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/14 17:18:16 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/server.h"

void						need_param(char const *name_bin)
{
	if (name_bin != NULL)
		ft_putstr_fd(name_bin, STDERR_FILENO);
	ft_putstr_fd(" need port \n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

int							main(int argc, char **argv)
{
	t_gen					*gen;


#ifdef DEBUG
	debug = fopen("debug.txt", "w+");
#endif
	if (argc <= 1)
		need_param(argv[0]);
	if ((gen = get_general(ft_memalloc(sizeof(*gen)))) == NULL || check_port(
			(gen->port = argv[1])) == false)
		del_general(EXIT_FAILURE);
	if (init_signaux() != 0)
		del_general(EXIT_FAILURE);
	loop_server();
	return (EXIT_SUCCESS);
}
