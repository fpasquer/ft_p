/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_ret_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 15:34:21 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/23 15:04:53 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/client.h"

static int					add_ret(char *ret, unsigned int const
		curs_nb_word_line, unsigned int const nb_word_line,
		unsigned int const rest)
{
	unsigned int			j;

	if (ret == NULL)
		return (-1);
	if (curs_nb_word_line < nb_word_line - 1)
	{
		if (ft_strcat(ret, " ") != ret)
			return (-1);
	}
	else
	{
		j = 0;
		while (j++ < rest)
			if (ft_strcat(ret, " ") != ret)
				return (-1);
	}
	return (0);
}

static int					cpy_in_ret(t_cmd_list **node, char **list,
		size_t const size_ret, size_t const len_bigger)
{
	char					*ret;
	size_t					current_len;
	unsigned int			i;
	unsigned int			nb_word_line;
	unsigned int			curs_nb_word_line;

	if (list == NULL || (ret = ft_memalloc(size_ret * sizeof(*ret))) == NULL)
		return (-1);
	nb_word_line = COLS / (len_bigger + 1);
	curs_nb_word_line = 0;
	i = 0;
	while (list[i] != NULL)
	{
		current_len = ft_strlen(list[i]);
		if (ft_strncat(ret, list[i++], size_ret) != ret)
			return (-1);
		while (current_len++ < len_bigger)
			if (ft_strncat(ret, " ", size_ret) != ret)
				return (-1);
		if (add_ret(ret, curs_nb_word_line, nb_word_line, COLS % (len_bigger +
				1)) != 0)
			break ;
		curs_nb_word_line = curs_nb_word_line + 1 >= nb_word_line ? 0 :
				curs_nb_word_line + 1;
	}
	return (add_cmd_ret(node, &ret));
}

int							save_ret_server(t_cmd_list *node, char  **list)
{
	size_t					current_len;
	size_t					len_bigger;
	size_t					size_ret;
	unsigned int			nb_word_line;
	unsigned int			i;

	if (list == NULL || node == NULL)
		return (-1);
	i = 0;
	len_bigger = 0;
	while (list[i] != NULL)
	{
		current_len = ft_strlen(list[i++]);
		len_bigger = current_len > len_bigger ? current_len : len_bigger;
	}
	nb_word_line = COLS / (len_bigger + 1);
	size_ret = COLS * (i / nb_word_line);
	size_ret += (i % nb_word_line) * (len_bigger + 1) + 1;
	return (cpy_in_ret(&node, list, size_ret, len_bigger));
}