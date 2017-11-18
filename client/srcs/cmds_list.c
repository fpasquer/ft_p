/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 15:03:55 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/18 21:19:56 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/client.h"

int							add_cmd_list(t_cmd_list **lst, char const *cmd,
		char const *ret)
{
	t_cmd_list				*new;
	size_t					len;

	if (lst == NULL || cmd == NULL)
		return (-1);
	if ((len = ft_strlen(cmd)) == 0)
		return (0);
	if ((new = ft_memalloc(sizeof(*new))) == NULL)
		return (-1);
	new->cmd_size = len;
	new->ret_size = (ret == NULL) ? 0 : ft_strlen(ret);
	if ((new->cmd = ft_strdup(cmd)) == NULL)
		return (-1);
	if (ret != NULL)
		if ((new->ret_server = ft_strdup(ret)) == NULL)
			return (-1);
	new->next = *lst;
	*lst = new;
	return (0);
}

static int					print_list_line(char *line, size_t len_line,
		WINDOW *term, int y)
{
	char					mem;
	char					*curs_line;
	char					*addr_position_mem;

	if (line == NULL || term == NULL || y < 0 || y >= HIGHT_TERM_WIN)
		return (-1);
	curs_line = line;
	while (len_line >= (size_t)COLS)
	{
		mem = curs_line[(COLS - 1)];
		addr_position_mem = &curs_line[(COLS - 1)];
		*addr_position_mem = '\0';
		mvwprintw(term, y++, 0, "%s", curs_line);
		*addr_position_mem = mem;
		len_line -= COLS - 1;
		curs_line += COLS - 1;
	}
	mvwprintw(term, y++, 0, "%s", curs_line);
	return (0);
}

int							print_list_cmd(t_cmd_list *list, int const max,
		int y, WINDOW *term)
{
	int						decalage;
	int						ret;
	static int				pos;

	if (term == NULL || y < 0 || max <= 0 || y >= max - 1 || list == NULL)
	{
		pos = 0;
		return (term == NULL || y < 0 || max <= 0 ? -1 : y);
	}
	decalage = list->cmd_size / COLS + 1;
	decalage += (list->ret_server != NULL) ? list->ret_size / COLS : 0;
	if (y + decalage >= max - 1)
	{
		pos = 0;
		return (y);
	}
	ret = print_list_cmd(list->next, max, y + decalage, term);
	if (list->ret_server != NULL && print_list_line(list->ret_server,
			list->ret_size, term, pos) != 0)
		return (-1);
	pos = list->ret_server != NULL ? pos - list->ret_size / COLS + 1 : pos;
	if (print_list_line(list->cmd, list->cmd_size, term, pos) != 0)
		return (-1);
	pos += list->cmd_size / COLS + 1;
	return (ret);
}

int							del_cmd_list(t_cmd_list **lst)
{
	t_cmd_list				*next;

	if (lst == NULL)
		return (-1);
	while (*lst != NULL)
	{
		next = (*lst)->next;
		if ((*lst)->cmd != NULL)
			ft_memdel((void**)&(*lst)->cmd);
		if ((*lst)->ret_server != NULL)
			ft_memdel((void**)&(*lst)->ret_server);
		ft_memdel((void**)lst);
		(*lst) = next;
	}
	return (0);
}