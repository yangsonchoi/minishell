#include <stdio.h>

int	main(int argc, char **argv, char **envp)
{
	char	**mini_envp;

	mini_envp = copy_envp(envp);
	set_signal();
}

char	**copy_envp(char **old_envp)
{
	char	**new_envp;
	int		i;

	i = 0;
	while (old_envp[i] != NULL)
		i++;
	new_envp = malloc(sizeof(char *) * (i + 1));
	if (new_envp == NULL)
		return (NULL);
	i = 0;
	while (old_envp[i] != NULL)
	{
		new_envp[i] = ft_strdup(old_envp[i]);
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}
