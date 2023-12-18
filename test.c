
#include "./src/pipex.h"

int main(void)
{
	int tube[2];
	char *cmd[] = {"cat", "-e", NULL};
	pipe(tube);

	write(tube[WRITE], "oi", 2);

	dup2(tube[READ], STDIN_FILENO);
	close(tube[READ]);
	execvp(cmd[0], cmd);
}