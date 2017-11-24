/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 07:56:11 by fpasquer          #+#    #+#             */
/*   Updated: 2017/11/24 09:07:24 by fpasquer         ###   ########.fr       */
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
	struct stat				s;

	if (stat(path, &s) == -1)
		return (-1);
	return (((s.st_mode & S_IFMT) == S_IFDIR) ? true : false);
}
