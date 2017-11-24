/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 14:55:50 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/24 08:21:09 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/server.h"

static void					error_msg(char const *error)
{
	if (error != NULL)
		ft_putstr_fd(error, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

int							main(int argc, char **argv)
{
	t_gen					*gen;

	if (argc <= 1 || check_port(argv[1]) == false)
		error_msg("Need port or port unvalable(1500 <-> 65535)\n");
	if ((gen = get_general(ft_memalloc(sizeof(*gen)))) == NULL)
		error_msg("Error gen main\n");
	if (init_signaux() != 0)
		error_msg("Signaux error\n");
	if (init_server(argv[1]) != 0)
		error_msg("Init server error\n");
	loop_server(gen);
	return (EXIT_FAILURE);
}
