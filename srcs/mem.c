/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbougssi <rbougssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:13:56 by rbougssi          #+#    #+#             */
/*   Updated: 2021/10/06 11:35:11 by rbougssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	dcmds(char **cmd1, char **cmd2)
{
	if (*cmd1)
		free(*cmd1);
	if (*cmd2)
		free(*cmd2);
}

void	dcmd(char **cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
		free(cmd[i]);
	free(cmd);
}

void	dstruct(t_pipex *pstruct)
{
	if (pstruct->cmd1)
		free(pstruct->cmd1);
	if (pstruct->cmd2)
		free(pstruct->cmd2);
	if (pstruct->cmd1path)
		free(pstruct->cmd1path);
	if (pstruct->cmd2path)
		free(pstruct->cmd2path);
}
