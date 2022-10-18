#include <stdio.h>
#include <stdlib.h>

int	ft_isdigit(int c)
{
	return (('0' <= c) && ('9' >= c));
}

int	main(void)
{
	int i, j;
	char a, b;

	a = '5';
	b = 'f';
	i = ft_isdigit(a);
	j = ft_isdigit(b);

	printf("i: %d, j: %d", i, j);

}
