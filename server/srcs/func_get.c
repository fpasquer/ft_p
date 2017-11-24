/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 19:50:07 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/24 07:58:44 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/server.h"

void						print_memory(void *addr, size_t len)
{
	unsigned char			*tmp;
	size_t					i;

	i = 0;
	tmp = (unsigned char *)addr;
	while (i < len)
	{
		printf("%p = %c = %d\n", tmp + i, ft_isprint((int)tmp[i]) == true ? tmp[i] : '.', tmp[i]);
		i++;
	}
}

static int					send_file(t_client *gen , t_data_file *file)
{
	if (gen == NULL || file == NULL)
		return (-1);
	file->size_datas = sizeof(file->len_name) + sizeof(file->size_file) +
			file->len_name + file->size_file;
	if ((file->datas = ft_memalloc(file->size_datas)) == NULL)
		return (-1);
	if (ft_memcpy(file->datas, &file->len_name, sizeof(file->len_name)) !=
			file->datas)
		return(-1);
	if (ft_memcpy(&file->datas[sizeof(file->len_name)], file->name,
			file->len_name) != &file->datas[sizeof(file->len_name)])
		return(-1);
	if (ft_memcpy(&file->datas[sizeof(file->len_name) + file->len_name],
			&file->size_file, sizeof(file->size_file)) !=
			&file->datas[sizeof(file->len_name) + file->len_name])
		return(-1);
	if (ft_memcpy(&file->datas[sizeof(file->len_name) + file->len_name +
			sizeof(file->size_file)], file->file_content, file->size_file) !=
			&file->datas[sizeof(file->len_name) + file->len_name +
			sizeof(file->size_file)])
		return(-1);
	return (0);
}

static int					send_file_to_client(t_client *gen, t_data_file *file)
{
	char					*full_path;

	if (gen == NULL || (file->len_name = ft_strlen(file->name)) == 0)
		return (-1);
	if ((full_path = ft_multijoin(3, gen->racine, gen->current_dir, file->name))
			== NULL)
		return (send_tab(gen->sock_client, "Error malloc"));
	if ((file->fd = ft_fopen(full_path, "r")) <= 0)
		return (send_tab(gen->sock_client, "Error open"));
	if ((file->size_file = lseek(file->fd, 0, SEEK_END)) <= 0)
		return (send_tab(gen->sock_client, "Empty file"));
	if ((file->file_content = mmap(NULL, file->size_file, PROT_READ,
			MAP_PRIVATE, file->fd, 0)) == MAP_FAILED)
		return (send_tab(gen->sock_client, "Error mmap"));
	if (send_file(gen, file) != 0 || send_tab(gen->sock_client, "GET success")
			!= 0)
		return (send_tab(gen->sock_client, "Error send file"));
	if (send(gen->sock_client, &file->size_datas, sizeof(file->size_datas), 0)
			< 0 || send(gen->sock_client, file->datas, file->size_datas, 0) < 0)
		return (-1);
	ft_memdel((void**)&file->datas);
	munmap(file->file_content, file->size_file);
	close(file->fd);
	ft_memdel((void**)&full_path);
	return (0);
}

int							func_get(void)
{
	t_data_file				file;
	int						ret;
	unsigned int			i;
	t_client				*gen;

	if ((gen =  get_client(NULL)) == NULL || gen->sock_client <= 0)
		return (-1);
	i = 4;
	file.name = &gen->cmd[i];
	while (ft_isspace(*file.name) == true)
		file.name++;
	if ((ret = is_in_list(gen->cwd_server, file.name)) <= 0 || ret == TYPE_FOLDER)
		return (send_tab(gen->sock_client, ret <= 0 ? "GET Failure" :
			"GET don't work with folder"));
	ret = send_file_to_client(gen, &file);
	ft_memdel((void**)&gen->cmd);
	if (ret == 0)
		printf("\tUser[%3d] get file : %s%s%s\n", gen->sock_client, gen->racine,
				gen->current_dir, file.name);
	return (ret);
}