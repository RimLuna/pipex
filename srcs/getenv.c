/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbougssi <rbougssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 10:54:42 by rbougssi          #+#    #+#             */
/*   Updated: 2021/10/06 10:54:43 by rbougssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*_getenv(char **env, const char *name)
{
	const char	*np;
	char		**p;
	char		*envptr;
	int			len;

	np = name;
	while (*np && *np != '=')
		np++;
	len = np - name;
	p = env;
	envptr = *p;
	while (envptr != NULL)
	{
		envptr = *p;
		if (_strncmp(envptr, name, len) == 0 && envptr[len] == '=')
		{
			return (_strdup(envptr + len + 1));
		}
		p++;
	}
	return (NULL);
}
