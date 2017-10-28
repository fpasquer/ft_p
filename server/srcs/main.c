/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 17:49:55 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/28 17:51:38 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/server.h"

int							main(int argc, char **argv)
{
	if (argc <= 1)
		return (EXIT_FAILURE);
	printf("%s\n", argv[1]);
	return (EXIT_SUCCESS);
}
