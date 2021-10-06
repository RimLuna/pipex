/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpaths.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbougssi <rbougssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 10:22:35 by rbougssi          #+#    #+#             */
/*   Updated: 2021/10/06 11:36:28 by rbougssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pathmdlwr(char **c1p, char **c2p, t_pipex *ps, char **pi)
{
	char	*path;
	char	**cmd;
	char	*slashpath;
	char	*base_cmd1;
	char	*base_cmd2;

	path = _strdup(*pi);
	free(*pi);
	if (path[_strlen(path)] != '/')
		slashpath = _strjoin(path, "/");
	cmd = _split(ps->cmd1, ' ');
	base_cmd1 = _strdup(cmd[0]);
	dcmd(cmd);
	cmd = _split(ps->cmd2, ' ');
	base_cmd2 = _strdup(cmd[0]);
	dcmd(cmd);
	*c1p = _strjoin(slashpath, base_cmd1);
	*c2p = _strjoin(slashpath, base_cmd2);
	free(base_cmd1);
	free(base_cmd2);
	free(path);
	free(slashpath);
}

char	**pathnorminette(char **envp)
{
	char		*pathenv;
	char		**paths;

	pathenv = _getenv(envp, "PATH");
	paths = _split(pathenv, ':');
	free(pathenv);
	return (paths);
}

char	*statpaths(char **cmdpath, struct stat *statbuf)
{
	char	*pscmdpath;

	if (stat(*cmdpath, statbuf) != -1)
		pscmdpath = _strdup(*cmdpath);
	else
		pscmdpath = NULL;
	free(*cmdpath);
	return (pscmdpath);
}

void	getpaths(char **envp, t_pipex *pstruct)
{
	int			i;
	struct stat	statbuf;
	char		**paths;
	char		*cmd1path;
	char		*cmd2path;

	paths = pathnorminette(envp);
	i = -1;
	while (paths && paths[++i])
	{
		pathmdlwr(&cmd1path, &cmd2path, pstruct, &paths[i]);
		if (stat(cmd1path, &statbuf) != -1)
			pstruct->cmd1path = _strdup(cmd1path);
		if (stat(cmd2path, &statbuf) != -1)
			pstruct->cmd2path = _strdup(cmd2path);
		dcmds(&cmd1path, &cmd2path);
	}
	free(paths);
	if (pstruct->cmd1path == NULL)
		cmd404(pstruct->cmd1);
	if (pstruct->cmd2path == NULL)
	{
		cmd404(pstruct->cmd2);
		bye(pstruct, NULL, 1);
	}
}
