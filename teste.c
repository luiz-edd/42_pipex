#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


// int main(int argc, char **argv, char **envp) {
//     for (int i = 0; envp[i] != NULL; i++) {
//         printf("Environment variable %d: %s\n", i, envp[i]);
//     }
//     return 0;
// }

// int	main(void)
// {
	
// 	char *args[] = {"cat", "test2", NULL};
// 	char *bin_file = args[0];

// 	int fd = open("redirect.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	
// 	dup2(fd, STDOUT_FILENO);
// 	close(fd);
// 	// int fd2 = open("test2", O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (execvp(bin_file, args) == -1)
// 	{
// 		fprintf(stderr, "Error.");
// 	}
// }