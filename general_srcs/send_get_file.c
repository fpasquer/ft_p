/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_get_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 08:03:11 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/24 08:05:34 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../general_incs/general.h"

int							creat_file(void *datas, int (f)(void))
{
	char					*name;
	char					*file_content;
	int						fd;
	size_t					len_name;
	size_t					size_file;

	if (datas == NULL || (len_name = (*(size_t*)datas)) == 0)
		return (-1);
	datas += sizeof(len_name);
	if ((name = ft_strndup(datas, len_name)) == NULL)
		return (-1);
	datas += len_name;
	size_file = (*(size_t *)datas);
	datas += sizeof(size_file);
	file_content = (char *)datas;
	if ((fd = ft_fopen(name, "w+")) <= 0 || write(fd, file_content, size_file)
			!= (ssize_t)size_file)
	{
		ft_memdel((void**)&name);
		return (-1);
	}
	ft_memdel((void**)&name);
	close(fd);
	return (f());
}