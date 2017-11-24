/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 17:22:36 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/24 11:01:34 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERAL_H
# define GENERAL_H

# include "../libft/libft.h"
# include <ncurses.h>
# include <time.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netdb.h>
# include <errno.h>
# include <arpa/inet.h>
# include <sys/mman.h>

# define SIZE_CWD 500

# define SIZE_BUFF 7

# define SCR_ROW_MIN 51
# define SCR_COL_MIN 203

# define HIGHT_INFO_WIN 10
# define HIGHT_TERM_WIN 20

# define UNSELECTED 1
# define SELECTED 2

# define DEBUG

# define TYPE_FOLDER 1
# define TYPE_FILE 2

# ifdef DEBUG
	FILE					*debug;
# endif

typedef struct				s_data_file
{
	char					*datas;			//ligne complete envoye au client
	char					*name;			//name du fichier
	char					*file_content;	//contenue du fihier
	int						fd;				//de open
	size_t					len_name;		//longueur de name
	size_t					size_file;		//size_du fichier
	size_t					size_datas;		//size_datas
}							t_data_file;

typedef struct				s_sig_func
{
	int						signal;
	void					(*f)(int);
}							t_sig_func;

typedef enum				e_type_ip
{
	IPV4 = AF_INET, IPV6 = AF_INET6
}							t_type_ip;

typedef enum				e_type_cmp
{
	STRCMP, STRNCMP
}							t_type_cmp;

typedef struct				s_coord
{
	int						y;
	int						x;
}							t_coord;

typedef struct				s_list_cwd
{
	char					cwd[SIZE_CWD];
	char					cwd_show[SIZE_CWD];
	char					**list;
	int						nb_row;
	int						decalage;
}							t_list_cwd;

typedef struct				s_data
{
	size_t					size;
	void					*data;
}							t_data;

typedef struct				s_cmd_manager
{
	char					*cmd;
	size_t					len_cmp;
	t_type_cmp				type;
	int						(*f)(void);
}							t_cmd_manager;

/*
**	keybord.c
*/
ssize_t						get_key_pressed(char buff[SIZE_BUFF]);

/*
**	gestion cwd client server
*/
int							set_list_cwd(t_list_cwd *cwd, char const *cwd_show,
	char dest[SIZE_CWD]);
int							print_list_cwd(t_list_cwd const cwd, WINDOW *win,
		bool const selected);
int							is_in_list(t_list_cwd const cwd,
		char const *target);
void						del_list_cwd(t_list_cwd cwd);

/*
**	check_ip_port
*/
char						*get_ip(char const *ip, t_type_ip *type_ip);
int							check_ip(char const *ip);
bool						check_port(char const *port);
int							ipv4_mapped_ipv6(char const *ipv4, char *dest,
		size_t const size_dest);

/*
**	send_get_data
*/
int							send_tab(int const sock, char *str);
char						*get_tab(int const sock);
int							send_tab_2d(int const sock, char **tab);
char						**get_tab_2d(int const sock);

/*
**	send_get_file
*/
int							creat_file(void *datas, int (f)(void));
int							get_datas_file(t_data_file *file);

#endif
