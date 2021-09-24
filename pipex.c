#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

int				main(int argc, char **argv)
{
	pid_t	pid;
	int		p[2];

	if (argc != 5)
	{
		write(1, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 41);
		return (0);
	}
	if (pipe(p) == -1)
		return (0);
	pid = fork();
	if (pid == -1)
	{
		write(1, "Fork failed\n", 12);
		return (0);
	}
	if (pid == 0)
		write(1, "Son\n", 12);
	else
		write(1, "Dad\n", 12);
	return (0);
}