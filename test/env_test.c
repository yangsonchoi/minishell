#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int	main(void)
{
	char *env;

	env = getenv("PWD");
	printf("%s\n", env);

	env = getcwd(NULL, 0);
	printf("%s\n", env);
	free(env);

	chdir("..");
	env = getcwd(NULL, 0);
	printf("%s\n", env);
	free(env);

	chdir("shell.c");
	env = getcwd(NULL, 0);
	printf("%s\n", env);
	free(env);

	errno = 1;
	env = strerror(errno);
	printf("%s\n", env);

	errno = 2;
	env = strerror(errno);
	printf("%s\n", env);

    errno = 0;
	env = getenv("");
	printf("%s, %p\n", env, env);

	env = strerror(errno);
	printf("%s\n", env);
	return (0);
}