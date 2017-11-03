/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 17:55:43 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/03 08:34:39 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../incs/client.h"

static void				func_int(int sig)
{
	del_general(EXIT_SUCCESS);
	sig = (int)sig;
}

static void				func_sig_winch(int sig)
{
	t_gen				*gen;

	if ((gen = get_general(NULL)) == NULL)
		return ;
	del_ncurses(gen);
	gen->scr = init_ncurses();
	if (LINES < SCR_ROW_MIN || COLS < SCR_COL_MIN)
		show_str_ncurses("Screen too small");
	else
		if (print_list_cwd(gen->cwd_client, gen->scr.client, gen->win ==
				CLIENT ? true : false) != 0 || print_list_cwd(gen->cwd_server,
				gen->scr.server, gen->win == SERVER ? true : false) != 0 ||
				print_infos() != 0)
			return ;
	sig = (int)sig;
}

int						init_signaux(void)
{
	int					i;
	t_sig_func const	list_sin[] =
	{
		{SIGINT, func_int},
		{SIGWINCH, func_sig_winch},
		{0, NULL}
	};

	i = -1;
	while (list_sin[++i].f != NULL)
		if (signal(list_sin[i].signal, list_sin[i].f) == SIG_ERR)
			return (-1);
	return (0);
}
