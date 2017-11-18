/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 15:03:55 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/18 15:44:21 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/client.h"

int							add_cmd_list(t_cmd_list **lst, char const *cmd,
		char const *ret)
{
	t_cmd_list				*new;

	if (lst == NULL || cmd == NULL || (new = ft_memalloc(sizeof(*new))) == NULL)
		return (-1);
	if ((new->cmd_size = ft_strlen(cmd)) == 0)
		return (-1);
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