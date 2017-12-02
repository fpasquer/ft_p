/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_get_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 08:03:11 by fpasquer          #+#    #+#             */
/*   Updated: 2017/12/02 17:37:20 by fpasquer         ###   ########.fr       */
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
	if (ft_is_dir(name) == true || (fd = ft_fopen(name, "w+")) <= 0 ||
			write(fd, file_content, size_file) != (ssize_t)size_file)
	{
		ft_memdel((void**)&name);
		return (-1);
	}
	ft_memdel((void**)&name);
	close(fd);
	return (f == NULL ? 0 : f());
}

int							get_datas_file(t_data_file *file)
{
	if (file == NULL)
		return (-1);
	file->size_datas = sizeof(file->len_name) + sizeof(file->size_file) +
			file->len_name + file->size_file;
	if ((file->datas = ft_memalloc(file->size_datas)) == NULL)
		return (-1);
	if (ft_memcpy(file->datas, &file->len_name, sizeof(file->len_name)) !=
			file->datas)
		return (-1);
	if (ft_memcpy(&file->datas[sizeof(file->len_name)], file->name,
			file->len_name) != &file->datas[sizeof(file->len_name)])
		return (-1);
	if (ft_memcpy(&file->datas[sizeof(file->len_name) + file->len_name],
			&file->size_file, sizeof(file->size_file)) !=
			&file->datas[sizeof(file->len_name) + file->len_name])
		return (-1);
	if (ft_memcpy(&file->datas[sizeof(file->len_name) + file->len_name +
			sizeof(file->size_file)], file->file_content, file->size_file) !=
			&file->datas[sizeof(file->len_name) + file->len_name +
			sizeof(file->size_file)])
		return (-1);
	return (0);
}
