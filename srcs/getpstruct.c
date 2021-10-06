/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpstruct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbougssi <rbougssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:13:03 by rbougssi          #+#    #+#             */
/*   Updated: 2021/10/06 11:13:04 by rbougssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	getornotpath(char **envp, t_pipex *pstruct)
{
	struct stat	statbuf;

	if (stat(pstruct->cmd1, &statbuf) != -1)
		pstruct->cmd1path = pstruct->cmd1;
	else
		getpaths(envp, pstruct);
}

void	getpstruct(char **av, char **envp, t_pipex *pstruct)
{
	struct stat	statbuf;

	pstruct->fd1 = open(av[1], O_RDONLY);
	if (pstruct->fd1 < 0)
	{
		_strerror("Error: \n", 7);
		perror(av[1]);
	}
	pstruct->fd2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pstruct->fd2 < 0)
	{
		_strerror("Error: \n", 7);
		perror(av[4]);
		bye(pstruct, NULL, 0);
	}
	pstruct->cmd1 = _strdup(av[2]);
	if (!pstruct->cmd1)
		bye(pstruct, NULL, 0);
	pstruct->cmd2 = _strdup(av[3]);
	if (!pstruct->cmd2)
		bye(pstruct, pstruct->cmd1, 0);
	getornotpath(envp, pstruct);
}
