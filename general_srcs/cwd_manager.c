/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwd_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 11:44:22 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/30 08:29:12 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../general_incs/general.h"

int							set_list_cwd(t_list_cwd *cwd)
{
	if (cwd == NULL)
		return (-1);
	ft_bzero(cwd, sizeof(*cwd));
	if (getcwd(cwd->cwd, SIZE_CWD) == NULL || (cwd->nb_row =
			ft_scandir(cwd->cwd, &cwd->list)) < 0)
		return (-1);
	return (0);
}

int							print_list_cwd(t_list_cwd cwd, WINDOW *win)
{
	int						i;

	if (cwd.list == NULL || win == NULL || LINES - 2 - HIGHT_INFO_WIN -
			HIGHT_TERM_WIN <= 0)
		return (-1);
	i = 0;
	mvwprintw(win, 1, 1, "%s", cwd.cwd);
	while (cwd.list[i] != NULL && i + cwd.decalage < LINES - HIGHT_INFO_WIN -
			HIGHT_TERM_WIN - 2)
	{
		mvwprintw(win, i + 2, 1, "\t%s", cwd.list[i]);
		i++;
	}
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
