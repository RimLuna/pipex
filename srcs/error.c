/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbougssi <rbougssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 10:16:03 by rbougssi          #+#    #+#             */
/*   Updated: 2021/10/06 10:52:43 by rbougssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cmd404(char *cmd)
{
	_strerror("Error: \n", 7);
	_strerror(cmd, _strlen(cmd));
	_strerror(": command not found\n", 20);
}

void	bye(t_pipex *pstruct, char *p, int cmderr)
{
	free(p);
	dstruct(pstruct);
	if (!cmderr)
		perror("Error");
	exit(EXIT_FAILURE);
}

void	usage(void)
{
	write(2, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 37);
}

void	usagecode(int code)
{
	write(2, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 37);
	exit(code);
}

void	_strerror(char *msg, int _strlen)
{
	write(2, msg, _strlen);
}
