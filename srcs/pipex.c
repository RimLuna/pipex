/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbougssi <rbougssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:28:28 by rbougssi          #+#    #+#             */
/*   Updated: 2021/10/06 11:30:44 by rbougssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(t_pipex pstruct, int *p, char **envp)
{
	char	**cmd;

	cmd = _split(pstruct.cmd1, ' ');
	if (pstruct.fd1 == -1)
	{
		dcmd(cmd);
		bye(&pstruct, NULL, 0);
	}
	dup2(pstruct.fd1, STDIN_FILENO);
	dup2(p[1], STDOUT_FILENO);
	close(p[0]);
	close(pstruct.fd1);
	if (execve(pstruct.cmd1path, cmd, envp) < 0)
	{
		dcmd(cmd);
		bye(&pstruct, NULL, 0);
	}
	dcmd(cmd);
	exit(EXIT_SUCCESS);
}

void	child1(t_pipex pstruct, int *p, char **envp)
{
	char	**cmd;

	cmd = _split(pstruct.cmd2, ' ');
	if (pstruct.fd2 == -1)
	{
		dcmd(cmd);
		bye(&pstruct, NULL, 0);
	}
	dup2(pstruct.fd2, STDOUT_FILENO);
	dup2(p[0], STDIN_FILENO);
	close(p[1]);
	close(pstruct.fd2);
	if (execve(pstruct.cmd2path, cmd, envp) < 0)
	{
		dcmd(cmd);
		bye(&pstruct, NULL, 0);
	}
	dcmd(cmd);
	exit(EXIT_SUCCESS);
}

void	pipex(t_pipex pstruct, char **envp)
{
	int		p[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	if (pipe(p) == -1)
		bye(NULL, NULL, 0);
	pid1 = fork();
	if (pid1 == -1)
		bye(NULL, NULL, 0);
	if (pid1 == 0)
		child(pstruct, p, envp);
	pid2 = fork();
	if (pid2 == -1)
	{
		_strerror("Error: \n", 7);
		perror("fork");
	}
	if (pid2 == 0)
		child1(pstruct, p, envp);
	waitpid(pid1, &status, 0);
}
