/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbougssi <rbougssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 10:09:31 by rbougssi          #+#    #+#             */
/*   Updated: 2021/10/06 10:48:49 by rbougssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	argcheck(int ac, char **av)
{
	int	i;
	int	j;

	if (ac != 5)
		usagecode(INVALID_ARGS);
	i = -1;
	while (av[++i])
	{
		j = 0;
		while (av[i][j] == ' ')
			j++;
		if (av[i][j] == '\0')
		{
			_strerror("Error: empty argument/s\n", 24);
			usagecode(EMPTY_ARGS);
		}
	}
}
