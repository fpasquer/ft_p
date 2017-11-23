/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 19:16:56 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/23 22:07:40 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/client.h"

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

static int					cmd_for_server(int const fd, char *cmd)
{
	int						ret;
	char					*info;

	if (fd <= 0 || cmd == NULL)
		return (-1);
	if (send_tab(fd, cmd) < 0 || (info = get_tab(fd)) == NULL)
		return (-1);
	if (add_infos(info) != 0)
		return (-1);
	ret = ft_strcmp(info, "GET success");
	ft_memdel((void**)&info);
	return (ret == 0 ? 0 : 1);
}

static int					func_get_file(t_gen *gen)
{
	void					*datas;
	size_t					size_data;
 
	if (gen == NULL || recv(gen->i_client.fd, &size_data, sizeof(size_data), 0)
			< 0 || (datas = ft_memalloc(size_data)) == NULL || recv(
			gen->i_client.fd, datas, size_data, 0) < 0)
		return (-1);
	print_memory(datas, size_data);
	ft_memdel((void**)&datas);
	return (0);
}

int							func_get(void)
{
	char					**list_files;
	char					cmd[SIZE_CMD];
	int						ret;
	unsigned int			i;
	t_gen					*gen;

	if ((gen = get_general(NULL)) == NULL)
		return (-1);
	if ((list_files = ft_strsplit(&gen->cmd[4], ' ')) == NULL)
		return (-1);
	i = 0;
	while (list_files[i] != NULL)
	{
		if (ft_strncpy(cmd, "GET ", SIZE_CWD) != cmd ||
				ft_strncat(cmd, list_files[i++], SIZE_CWD) != cmd ||
				(ret = cmd_for_server(gen->i_client.fd, cmd)) < 0)
			return (-1);
		if (ret == 0)
			if (func_get_file(gen) != 0)
				return (-1);
	}
	ft_free_strsplit(list_files);
	return (0);
}