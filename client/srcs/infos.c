/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infos.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 07:31:40 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/08 07:58:10 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/client.h"

int							add_infos(char const *str)
{
	int						i;
	t_gen					*gen;

	if ((gen = get_general(NULL)) == NULL || str == NULL)
		return (-1);
	i = 0;
	if (gen->i_last_infos >= HIGHT_INFO_WIN - 2 && ft_strlen(gen->last_infos[0])
			> 0)
	{
		while (++i <= gen->i_last_infos)
			ft_strncpy(gen->last_infos[i - 1], gen->last_infos[i],
					SCR_COL_MIN -2);
		gen->i_last_infos--;
	}
	ft_strncpy(gen->last_infos[gen->i_last_infos++], str, SCR_COL_MIN -2);
	return (0);
}

int							print_infos(void)
{
	int						i;
	t_gen					*gen;

	if ((gen = get_general(NULL)) == NULL || gen->scr.infos == NULL)
		return (-1);
	i = 0;
	wclear(gen->scr.infos);
	wattron(gen->scr.infos, COLOR_PAIR(UNSELECTED));
	if (wborder(gen->scr.infos, '|', '|', '-', '-', '+', '+', '+', '+') != OK)
		return (-1);
	while (i < gen->i_last_infos)
	{
		mvwprintw(gen->scr.infos, i + 1, 1, "%s", gen->last_infos[i]);
		i++;
	}
	wattroff(gen->scr.infos, COLOR_PAIR(UNSELECTED));
	wrefresh(gen->scr.infos);
	return (0);
}
