/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 12:43:08 by fpasquer          #+#    #+#             */
/*   Updated: 2017/12/02 16:49:56 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/client.h"

#define KEY_ENTER_ (char[]){13, 0, 0, 0, 0, 0, 0}
#define KEY_DEL_ (char[]){127, 0, 0, 0, 0, 0, 0}
#define KEY_F5_ (char[]){27, 91, 49, 53, 126, 0, 0}
#define KEY_ESC_ (char[]){27, 0, 0, 0, 0, 0, 0}
#define KEY_F6_ (char[]){27, 91, 49, 55, 126, 0, 0, 0, 0}
#define KEY_F7_ (char[]){27, 91, 49, 56, 126, 0, 0, 0, 0}
#define SHIFT_UP (char[]){27, 91, 49, 59, 50, 65, 0, 0, 0}
#define SHIFT_DOWN (char[]){27, 91, 49, 59, 50, 66, 0, 0, 0}
#define OPTION_UP (char[]){27, 27, 91, 65, 0, 0, 0, 0, 0}
#define OPTION_DOWN (char[]){27, 27, 91, 66, 0, 0, 0, 0, 0}
#define TAB (char[]){9, 0, 0, 0, 0, 0, 0, 0, 0}

t_cmd_manager const			g_cmds[] = {
	{KEY_ESC_, 2, STRCMP, func_exit},
	{KEY_F5_, 6, STRCMP, func_refresh_client},
	{KEY_F6_, 6, STRCMP, func_refresh_server},
	{KEY_F7_, 6, STRCMP, func_change_win},
	{SHIFT_UP, 6, STRCMP, func_win_up},
	{SHIFT_DOWN, 6, STRCMP, func_win_down},
	{TAB, 2, STRCMP, autocompletion},
	{"CD ", 3, STRNCMP, func_cd},
	{"GET ", 4, STRNCMP, func_get},
	{"LS", 2, STRCMP, func_ls},
	{"PUT ", 4, STRNCMP, func_put},
	{"PWD", 3, STRCMP, func_pwd},
	{"REFRESH", 7, STRCMP, func_refresh_server},
	{"QUIT", 4, STRCMP, func_exit},
	{NULL, 0, STRCMP, NULL}
};

static bool					print_prompt_cmd(char const cmd[SIZE_CMD],
		int *wrong_cmd, size_t const len_cmd)
{
	int						y;
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
	wclear(gen->scr.term);
	if ((y = print_list_cmd(gen->i_client.list_cmd, HIGHT_TERM_WIN - (LEN_PROMPT
			+ len_cmd) / COLS + 1, 0, gen->scr.term)) < 0)
		return (false);
	if (mvwprintw(gen->scr.term, y, 0, "%s%s", PROMPT, cmd) != OK)
		return (false);
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
	while ((*i) < SIZE_CMD - 1 && print_prompt_cmd(cmd, &wrong_cmd, *i) == true)
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

int							send_exec_cmd(t_gen *gen)
{
	unsigned int			i;

	if (gen == NULL || gen->cmd[0] == '\0')
		return (gen == NULL ? -1 : 0);
	i = 0;
	while (g_cmds[i].cmd != NULL)
	{
		if (g_cmds[i].type == STRCMP && ft_strcmp(g_cmds[i].cmd, gen->cmd) == 0)
			return (g_cmds[i].f());
		else if (g_cmds[i].type == STRNCMP && ft_strncmp(g_cmds[i].cmd,
				gen->cmd, g_cmds[i].len_cmp) == 0)
			return (g_cmds[i].f());
		i++;
	}
	if (add_infos("ft_p command NOT found") != 0)
		del_general(EXIT_FAILURE);
	return (0);
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

	if (gen == NULL || gen->scr.term == NULL)
		return (-1);
	wrong_cmd = false;
	while (wrong_cmd >= 0)
		if (term_size() == true)
		{
			if (get_cmd(gen->cmd, &gen->len_cmd, wrong_cmd) != 0 ||
					add_cmd_list(&gen->i_client.list_cmd, gen->cmd, NULL) != 0)
				del_general(EXIT_FAILURE);
			if (send_exec_cmd(gen) != 0)
				break ;
		}
	return (-1);
}
