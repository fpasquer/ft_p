/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 17:26:06 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/28 17:32:30 by fpasquer         ###   ########.fr       */
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
	if (argc <= 2)
		need_param(argv[0]);
	printf("ok\n");
	return (EXIT_SUCCESS);
}
