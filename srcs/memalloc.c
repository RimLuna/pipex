/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memalloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbougssi <rbougssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:14:41 by rbougssi          #+#    #+#             */
/*   Updated: 2021/10/06 11:15:06 by rbougssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*_memalloc(size_t size)
{
	unsigned char	*mem;

	mem = (unsigned char *)malloc(sizeof(size_t) * size);
	if (mem == NULL)
		return (NULL);
	_bzero(mem, size);
	return (mem);
}
