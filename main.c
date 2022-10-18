#include <stdio.h>
#include <stdlib.h>


int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;	

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] != '\0' && s1[i] == s2[i] && i < n)
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}


int	main(void)
{
	printf("%d\n", ft_strncmp("YAHO", "HOME=Users/123", 4));
}
