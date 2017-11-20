/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 08:52:07 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/20 10:12:13 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/client.h"

static char const 			*g_list_cmd[] = {"CD", "GET", "LOGIN", "LOGOUT",
 		"LS", "PUT", "PWD", "QUIT", NULL};

static int					nb_match_in_list(char **list, char const *needed)
{
	int						nb_match;
	unsigned int			i;
	size_t					len_needed;

	if (list == NULL || needed == NULL)
		return (-1);
	nb_match = 0;
	i = 0;
	len_needed = ft_strlen(needed);
	while (list[i] != NULL)
		if (ft_strncmp(list[i++], needed, len_needed) == 0)
			nb_match++;
	return (nb_match);
}

static int					autocomplet_word(t_gen *gen, char const *word)
{
	char					*cmd;

	if (gen == NULL || word == NULL || gen->len_cmd == 0)
		return (-1);
	cmd = gen->cmd + gen->len_cmd - 1;
	while (cmd > gen->cmd && ft_isspace(*(cmd - 1)) == false)
	{
		gen->len_cmd--;
		cmd--;
	}
	if (ft_strncpy(cmd, word, SIZE_CMD - (int)(cmd - gen->cmd)) != cmd)
		return (-1);
	gen->len_cmd = ft_strlen(gen->cmd);
	return (0);
}

static int					autocompletion_bin(t_gen *gen, char const *cmd)
{
	char					**list;
	int						ret;
	int						nb_match;
	unsigned int			i;
	size_t					len_needed;

	if (gen == NULL)
		return (-1);
	if ((nb_match = nb_match_in_list((char**)g_list_cmd, cmd)) <= 0)
		return (nb_match);
	list = NULL;
	i = 0;
	len_needed = ft_strlen(cmd);
	while (g_list_cmd[i] != NULL)
		if (ft_strncmp(g_list_cmd[i++], cmd, len_needed) == 0)
		{
			if (nb_match == 1)
				return (autocomplet_word(gen, g_list_cmd[i - 1]));
			if ((list = ft_add_to_array((char *)g_list_cmd[i - 1], list)) ==
					NULL)
				break ;
		}
	ret = save_ret_server(gen->i_client.list_cmd, list);
	ft_free_add_to_array(list);
	return (ret);
}

int							autocompletion(void)
{
	char					*cmd;
	t_gen					*gen;

	if ((gen = get_general(NULL)) == NULL || add_cmd_list(
			&gen->i_client.list_cmd, gen->cmd, NULL) != 0)
		return (-1);
	if (gen->len_cmd == 0)
		return (save_ret_server(gen->i_client.list_cmd, (char**)g_list_cmd));
	cmd = gen->cmd + gen->len_cmd - 1;
	while (cmd > gen->cmd && ft_isspace(*(cmd - 1)) == false)
		cmd--;
	return (autocompletion_bin(gen, cmd));
}