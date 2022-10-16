#include <stdio.h>
#include <stdlib.h>


int	main(void)
{
	char *env;

	env = getenv("YAHO");
	printf("%s, %p, %p\n", env, env, NULL);
}
