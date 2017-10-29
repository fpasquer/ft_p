/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_client.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 09:32:24 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/29 10:40:30 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/client.h"

void						loop_client(t_ncurses scr)
{
	char					b[SIZE_BUFF];

	if (scr.client == NULL)
		return ;
	while (1)
	{
		if (get_key_pressed(b) != 0)
			break ;
		if (ESC)
			return ;
	}
}
