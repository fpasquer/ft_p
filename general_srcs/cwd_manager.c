/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwd_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 11:44:22 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/23 19:31:47 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../general_incs/general.h"

int							set_list_cwd(t_list_cwd *cwd, char const *cwd_show,
		char dest[SIZE_CWD])
{
	if (cwd == NULL || dest == NULL)
		return (-1);
	ft_bzero(cwd, sizeof(*cwd));
	if (getcwd(cwd->cwd, SIZE_CWD) == NULL || (cwd->nb_row =
			ft_scandir(cwd->cwd, &cwd->list, true)) < 0)
		return (-1);
	if (ft_strncpy(dest, cwd_show == NULL ? cwd->cwd : cwd_show, SIZE_CWD) ==
			NULL)
		return (-1);
	return (0);
}

int							is_in_list(t_list_cwd const cwd, char const *target)
{
	char					tmp[SIZE_CWD];
	int						ret;
	unsigned int			i;

	if (cwd.list == NULL || target == NULL)
		return (-1);
	ret = target[ft_strlen(target) - 1] == '/' ? TYPE_FOLDER : TYPE_FILE;
	i = 0;
	while (cwd.list[i] != NULL)
	{
		if (ret == TYPE_FILE)
		{
			if (ft_strncpy(tmp, target, SIZE_CWD) != tmp || ft_strncat(tmp, "/",
					SIZE_CWD) != tmp)
				return (-1);
			if (ft_strcmp(cwd.list[i], tmp) == 0)
				return (TYPE_FOLDER);
		}
		if (ft_strcmp(cwd.list[i], target) == 0)
			return (ret);
		i++;
	}
	return (0);
}

int							print_list_cwd(t_list_cwd const cwd, WINDOW *win,
		bool const selected)
{
	int						i;
	int						j;

	if (win == NULL || LINES - 2 - HIGHT_INFO_WIN -
			HIGHT_TERM_WIN <= 0)
		return (-1);
	i = 0;
	j = selected == true ? SELECTED : UNSELECTED;
	wclear(win);
	wattron(win, COLOR_PAIR(j));
	if (wborder(win, '|', '|', '-', '-', '+', '+', '+', '+') != OK)
		return (-1);
	if (cwd.list != NULL)
	{
		mvwprintw(win, 1, 1, "%s", cwd.cwd_show);
		while (cwd.list[i + cwd.decalage] != NULL && i < LINES -
				HIGHT_INFO_WIN - HIGHT_TERM_WIN - 3)
		{
			mvwprintw(win, i + 2, 1, "\t%s", cwd.list[i + cwd.decalage]);
			i++;
		}
	}
	wattroff(win, COLOR_PAIR(j));
	wrefresh(win);
	return (0);
}

void						del_list_cwd(t_list_cwd cwd)
{
	int						i;

	if (cwd.list == NULL)
		return ;
	i = 0;
	while (cwd.list[i] != NULL)
		ft_memdel((void**)&cwd.list[i++]);
	ft_memdel((void**)&cwd.list);
}
