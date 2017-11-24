/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rgba.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 11:42:56 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/24 09:06:58 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int				ft_rgba(unsigned char red, unsigned char green,
	unsigned char blue, unsigned char trans)
{
	unsigned int			ret;

	ret = (trans << 24);
	ret += (red << 16);
	ret += (green << 8);
	ret += (blue);
	return (ret);
}
