#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int picoshell(char **cmds[])
{
	int i = 0;
	int	in = 0;
	int fd[2];
	pid_t pid;
	int status;

	while (cmds[i])
	{
		if (cmds[i + 1] && pipe(fd) == -1)
			return 1;
		if ((pid = fork()) == -1)
			return 1;
		if (pid == 0)
		{
			if (in != 0)
			{
				dup2(in, 0);
				close(in);
			}
			if (cmds[i + 1])
			{
				dup2(fd[1], 1);
				close(fd[0]);
				close(fd[1]);
			}
			execvp(cmds[i][0], cmds[i]);
			exit(1);
		}
		if (in != 0)
			close(in);
		if (cmds[i + 1])
		{
			close(fd[1]);
			in = fd[0];
		}
		i++;
	}
	while (wait(&status) > 0)
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			return 1;
	return 0;
}

#include <stdio.h>

int picoshell(char **cmds[]);

int main(void)
{
	char *cmd1[] = {"ls", "-l", NULL};
	char *cmd2[] = {"cat", "-e", NULL};
	char **cmds[] = {cmd1, cmd2, NULL};
	printf("exit code: %d\n", picoshell(cmds));
}
