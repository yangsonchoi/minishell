#include "parse.h"
#include "libft.h"

static void erase_quote(t_token *token, int i, int len);

void	expand_quote(t_token *token)
{
	int		i;
	int		len;
	char	*input;

	i = 0;
	input = token->word;
	while (input[i] != 0)
	{
		if (input[i] == '\'')
		{
			len = ft_strchr(&input[i + 1], '\'') - &input[i + 1];
			erase_quote(token, i, len);
			input = token->word;
			i += len;
		}
		else if (input[i] == '\"')
		{
			len = ft_strchr(&input[i + 1], '\"') - &input[i + 1];
			erase_quote(token, i, len);
			input = token->word;
			i += len;
		}
		else if (input[i] != 0)
			i++;
	}
}

static void erase_quote(t_token *token, int i, int len)
{
	char	*input;
	char	*front_str;
	char	*quote;
	char	*back_str;

	input = token->word;
	front_str = ft_substr(input, 0, i);
	quote = ft_substr(input, i + 1, len);
	back_str = ft_substr(input, i + len + 2, ft_strlen(&input[i + len + 2]));
	join_string(token, front_str, quote, back_str);
}
