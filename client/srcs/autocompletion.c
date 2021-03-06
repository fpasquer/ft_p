/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 16:50:27 by fpasquer          #+#    #+#             */
/*   Updated: 2017/12/02 16:50:44 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/client.h"

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
		cmd--;
	if (ft_strncpy(cmd, word, SIZE_CMD - (int)(cmd - gen->cmd)) != cmd)
		return (-1);
	gen->len_cmd = ft_strlen(gen->cmd);
	return (0);
}

static int					autocompletion_exe(t_gen *gen, char **list_rep,
		char const *cmd)
{
	char					**list;
	int						ret;
	int						nb_match;
	unsigned int			i;
	size_t					len_needed;

	if (list_rep == NULL || (*list_rep) == NULL || cmd == NULL || gen == NULL)
		return (-1);
	if ((nb_match = nb_match_in_list((char**)list_rep, cmd)) <= 0)
		return (nb_match);
	list = NULL;
	i = 0;
	len_needed = ft_strlen(cmd);
	while (list_rep[i] != NULL)
		if (cmd == '\0' || ft_strncmp(list_rep[i++], cmd, len_needed) == 0)
		{
			if (nb_match == 1)
				return (autocomplet_word(gen, list_rep[i - 1]));
			if ((list = ft_add_to_array((char *)list_rep[i - 1], list)) ==
					NULL)
				break ;
		}
	ret = save_ret_server(gen->i_client.list_cmd, list);
	ft_free_add_to_array(list);
	return (ret);
}

static int					check_autocompletion_bin(char const *cmd)
{
	unsigned int			i;

	if (cmd == NULL)
		return (-1);
	i = 0;
	while (ft_isspace(cmd[i]))
		i++;
	while (ft_isalnum(cmd[i]))
		i++;
	return (cmd[i] == '\0' ? true : false);
}

int							autocompletion(void)
{
	char const				*list_cmd[] = {"CD", "GET", "LS", "PUT", "PWD",
			"QUIT", NULL};
	char					*cmd;
	int						ret;
	t_gen					*gen;

	if ((gen = get_general(NULL)) == NULL || add_cmd_list(
			&gen->i_client.list_cmd, gen->cmd, NULL) != 0)
		return (-1);
	cmd = gen->cmd + gen->len_cmd - 1;
	while (cmd > gen->cmd && ft_isspace(*(cmd - 1)) == false)
		cmd--;
	if ((ret = check_autocompletion_bin(gen->cmd)) < 0)
		return (-1);
	if (ret == true)
		return (autocompletion_exe(gen, (char **)list_cmd, cmd));
	ret = 0;
	while (ft_isspace(gen->cmd[ret]))
		ret++;
	if (ft_strncmp(&gen->cmd[ret], "PUT ", 4) == 0)
		return (autocompletion_exe(gen, gen->cwd_client.list, cmd));
	else if (ft_strncmp(&gen->cmd[ret], "GET ", 4) == 0)
		return (autocompletion_exe(gen, gen->cwd_server.list, cmd));
	return (autocompletion_exe(gen, gen->win == SERVER ? gen->cwd_server.list :
			gen->cwd_client.list, cmd));
}
