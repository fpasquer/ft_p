/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybord.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 09:56:13 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/01 18:56:07 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../general_incs/general.h"

ssize_t						get_key_pressed(char buff[SIZE_BUFF])
{
	if (buff == NULL)
		return (-1);
	ft_bzero(buff, sizeof(char) * SIZE_BUFF);
	return (read(STDIN_FILENO, buff, SIZE_BUFF));
}
