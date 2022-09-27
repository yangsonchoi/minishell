#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern char **environ;

void add_envp(char *new_envp, char ***envp);
int check_hello(void);

int	main(int argc, char **argv, char **envp)
{

	int i = 0;
	pid_t pid;

	if (check_hello())
	{
		printf("lv 2, envirion : %p, envp : %p\n", environ, envp);
		pid = getpid();
		printf("pid = %d\n", pid);
		while (environ[i])
		{
			printf("%s\n", environ[i++]);
		}
		exit(1);
	}
	printf("lv 1, envirion : %p, envp : %p\n", environ, envp);

	add_envp("hello", &envp);

	printf("lv 1, envirion : %p, envp : %p\n", environ, envp);
	// while (environ[i])
	// {
	// 	printf("%s\n", environ[i++]);
	// }
	pid = getpid();
	printf("pid = %d\n", pid);
	execve(argv[0], argv, envp);
	printf("11");
	
	return(0);
}

int check_hello(void)
{
	int i = 0;

	while (environ[i])
	{
		if (!strcmp(environ[i], "hello"))
		{
			return (1);
		}
		i++;
	}
	return (0);
}

void add_envp(char *new_envp, char ***envp)
{
	char **new_list;
	int i = 0;
	int j = 0;

	while (envp[0][i])
	{
		i++;
	}
	new_list = malloc(sizeof (char**) * (i + 2));
	j = 0;

	while (j < i)
	{
		new_list[j] = strdup(envp[0][j]);
		j++;
	}
	new_list[j++] = strdup(new_envp);
	new_list[j] = NULL;

	// free(environ);
	envp[0] = new_list;
}