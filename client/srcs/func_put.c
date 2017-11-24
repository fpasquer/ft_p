/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_put.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 08:54:48 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/24 11:12:29 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/client.h"

static int					error_put(char const *error)
{
	if (error != NULL)
		if (add_infos(error) != 0 || print_infos() != 0)
			return (-1);
	return (0);
}

// static int					cmd_for_server(int const fd, char *cmd)
// {
// 	int						ret;
// 	char					*info;

// 	if (fd <= 0 || cmd == NULL)
// 		return (-1);
// 	if (send_tab(fd, cmd) < 0 || (info = get_tab(fd)) == NULL)
// 		return (-1);
// 	if (add_infos(info) != 0)
// 		return (-1);
// 	ret = ft_strcmp(info, "PUT success");
// 	ft_memdel((void**)&info);
// 	return (ret == 0 ? 0 : 1);
// }

void						print_memory(void *addr, size_t len)
{
	unsigned char			*tmp;
	size_t					i;

	i = 0;
	tmp = (unsigned char *)addr;
	while (i < len)
	{
		fprintf(debug, "%p = %c = %d\n", tmp + i, ft_isprint((int)tmp[i]) == true ? tmp[i] : '.', tmp[i]);
		i++;
	}
}

static int					send_file_to_server(t_gen *gen, t_data_file *file)
{
	char					*info;

	if (gen == NULL || file == NULL)
		return (-1);
	if (send_tab(gen->i_client.fd, "PUT") < 0 || send(gen->i_client.fd,
			&file->size_datas, sizeof(file->size_datas), 0) < 0 || send(
			gen->i_client.fd, file->datas, file->size_datas, 0) < 0)
		return (-1);
	if ((info = get_tab(gen->i_client.fd)) == NULL || add_infos(info) != 0)
		return (-1);
	ft_memdel((void**)&info);
	return (func_refresh_server());
}

static int					execute_put(t_gen *gen, char const *file_name)
{
	char					*full_path;
	int						ret;
	t_data_file				file;

	if (gen == NULL || file_name == NULL)
		return (-1);
	if ((full_path = ft_multijoin(3, gen->cwd_client.cwd_show, "/", file_name))
			== NULL || (file.len_name = ft_strlen(file_name)) == 0 ||
			(file.name = ft_strdup(file_name)) == NULL)
		return (-1);
	if ((file.fd = ft_fopen(full_path, "r")) <= 0)
		return (error_put("Error open"));
	if ((file.size_file = lseek(file.fd, 0, SEEK_END)) <= 0)
		return (error_put("Empty file"));
	if ((file.file_content = mmap(NULL, file.size_file, PROT_READ,
			MAP_PRIVATE, file.fd, 0)) == MAP_FAILED)
		return (error_put("Error mmap"));
	if ((ret = get_datas_file(&file)) != 0)
		return (error_put("Error get file datas"));
	ret = send_file_to_server(gen, &file);
	close(file.fd);
	munmap(file.file_content, file.size_file);
	ft_memdel((void**)&full_path);
	return (ret);
}

int							func_put(void)
{
	char					**list_files;
	int						type;
	unsigned int			i;
	t_gen					*gen;
	
	if ((gen = get_general(NULL)) == NULL)
		return (-1);
	if ((list_files = ft_strsplit(&gen->cmd[4], ' ')) == NULL)
		return (-1);
	i = 0;
	while (list_files[i] != NULL)
		if ((type = is_in_list(gen->cwd_client, list_files[i++])) <= 0 ||
				type == TYPE_FOLDER)
		{
			if (error_put(type <= 0 ? "PUT need valable file" :
					"PUT don't work with folder") < 0)
				return (-1);
		}
		else
		{
			if (execute_put(gen, list_files[i - 1]) < 0)
				return (-1);
		}
	return (0);
}