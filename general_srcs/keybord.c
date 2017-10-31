/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybord.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 09:56:13 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/31 07:21:10 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../general_incs/general.h"

ssize_t						get_key_pressed(char buff[SIZE_BUFF])
{
	ssize_t					ret;

	if (buff == NULL)
		return (-1);
	ft_bzero(buff, sizeof(char) * SIZE_BUFF);
	ret = read(STDIN_FILENO, buff, SIZE_BUFF);
#ifdef DEBUG
	fprintf(debug ,"key[0] = %d key[1] = %d key[2] = %d key[3] = %d key[4] = %d key[5] = %d => len = %zi\t", buff[0], buff[1], buff[2], buff[3], buff[4], buff[5], ret);
#endif
	return (ret);
}
