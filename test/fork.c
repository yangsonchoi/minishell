#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int	main(void)
{
	int i = 0;
	pid_t pid;
	int j = 5;
	int k = 2;

	i = 1;
	pid = fork();
	if (pid == 0)
	{
		printf("child i : %d\n", i); 
		exit(300);
	}
	else
	{
		wait(&j);
		printf("j : %d\n", j);
		if (WIFEXITED(j))
		{
			printf("hello mo\n");
			k = WEXITSTATUS(j);
		}
		printf("parent i : %d, exit status : %d\n", i, k);
	}
	return (0);
}
