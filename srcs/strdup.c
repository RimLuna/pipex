/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbougssi <rbougssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:19:29 by rbougssi          #+#    #+#             */
/*   Updated: 2021/10/06 11:20:06 by rbougssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*_strdup(const char *s)
{
	char	*p;
	char	*k;

	p = (char *)malloc((_strlen(s) + 1) * sizeof(char));
	if (!p)
		return (NULL);
	k = p;
	while (s && *s)
		*p++ = *s++;
	*p = '\0';
	return (k);
}
