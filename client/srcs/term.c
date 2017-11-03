/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 12:43:08 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/03 08:41:36 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/client.h"

# define KEY_ENTER_ (char[]){13, 0, 0, 0, 0, 0, 0}
# define KEY_DEL_ (char[]){127, 0, 0, 0, 0, 0, 0}
# define KEY_F5_ (char[]){27, 91, 49, 53, 126, 0, 0}
# define KEY_ESC_ (char[]){27, 0, 0, 0, 0, 0, 0}
# define KEY_F6_ (char[]){27, 91, 49, 55, 126, 0, 0, 0, 0}

t_cmd_manager				g_cmds[] = {
	{KEY_ESC_, func_exit},
	{KEY_F5_, func_refresh_client},
	{KEY_F6_, func_change_win},
	{"LS", func_ls},
	{"CD", func_cd},
	{"GET", func_get},
	{"PUT", func_put},
	{"PWD", func_pwd},
	{"LOGIN", func_login},
	{"LOGOUT", func_logout},
	{"QUIT", func_exit},
	{NULL, NULL}
};

static bool					print_prompt_cmd(char const cmd[SIZE_CMD],
		int *wrong_cmd)
{
	t_gen					*gen;

	if ((gen = get_general(NULL)) == NULL || gen->scr.term == NULL ||
			cmd == NULL || wrong_cmd == NULL)
		return (false);
	if ((*wrong_cmd) == true)
		if (add_infos("ft_p: command not found") != 0)
			return (false);
	(*wrong_cmd) = false;
	if (print_infos() != 0)
		return (false);
	wclear(gen->scr.term) ;
	mvwprintw(gen->scr.term, 1 , 1, "%s%s", PROMPT, cmd);
	wrefresh(gen->scr.term);
	return (true);
}

int							get_cmd(char cmd[SIZE_CMD], size_t *i,
		int wrong_cmd)
{
	ssize_t					len;
	char					key[SIZE_BUFF];
	int						j;

	if (cmd == NULL || i == NULL)
		return (-1);
	ft_bzero(cmd, sizeof(char) * SIZE_CMD);
	(*i) = 0;
	while ((*i) < SIZE_CMD - 1 && print_prompt_cmd(cmd, &wrong_cmd) == true)
	{
		if ((len = get_key_pressed(key)) < 0 ||
				ft_strncmp(key, KEY_ENTER_, SIZE_BUFF) == 0)
			break ;
		j = 0;
		while (g_cmds[j].cmd != NULL)
			if (ft_strncmp(g_cmds[j++].cmd, key, SIZE_BUFF) == 0)
				if (g_cmds[j - 1].f() != 0)
					return (-1);
		if (key[0] >= 32 && key[0] <= 126)
			cmd[(*i)++] = key[0];
		if (ft_strncmp(key, KEY_DEL_, SIZE_BUFF) == 0 && (*i) > 0)
			cmd[--(*i)] = 0;
	}
	return (len < 0 ? -1 : 0);
}

bool						term_size(void)
{
	if (!(LINES < SCR_ROW_MIN || COLS < SCR_COL_MIN))
		return (true);
	show_str_ncurses("Screen too small");
	return (false);
}

int							loop_term(t_gen *gen)
{
	int						wrong_cmd;
	int						i;
	size_t					len_cmd;

	if (gen == NULL || gen->scr.term == NULL)
		return (-1);
	wrong_cmd = false;
	while (wrong_cmd >= 0)
		if (term_size() == true)
		{
			if (get_cmd(gen->cmd, &len_cmd, wrong_cmd) != 0)
				del_general(EXIT_FAILURE);
			i = 0;
			wrong_cmd = true;
			while (g_cmds[i].cmd != NULL)
				if (ft_strcmp(g_cmds[i++].cmd, gen->cmd) == 0)
					wrong_cmd = g_cmds[i - 1].f();
		}
	return (-1);
}
