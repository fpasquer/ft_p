/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 07:56:11 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/24 17:31:07 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

/*
**	DESCRIPTION :
**		int ft_is_dir(char *path)
**		indique si le path pointe vers un dossier
**	PARAMETRE :
**		Path vers le dossier
**	RETOUR :
**		Retourne true si c'est un dossier sinon false ou -1
*/

int							ft_is_dir(char const *path)
{
	int						fd;
	struct stat				s;

	if ((fd = ft_fopen(path, "r")) < 0)
		return (-1);
	if (fstat(fd, &s) == -1)
		return (-1);
	close(fd);
	return (((s.st_mode & S_IFMT) == S_IFDIR) ? true : false);
}
