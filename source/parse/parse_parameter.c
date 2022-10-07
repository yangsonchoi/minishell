#include "parse.h"
#include "minishell.h"
#include <stdlib.h>
#include "libft.h"

static int expand_sign(t_token *token, int i);
static char *convert_variable(char *parameter);

void	expand_parameter(t_token *token)
{
	int		i;
	bool	d_quote;

	i = 0;
	d_quote = false;
	while ((token->word)[i] != 0)
	{
		if ((token->word)[i] == '\"')
		{
			d_quote = !d_quote;
			i++;
		}
		else if ((token->word)[i] == '\'' && d_quote == false)
			i += ft_strchr(&(token->word)[i + 1], '\'') - &(token->word)[i];
		else if ((token->word)[i] == '$')
			i += expand_sign(token, i);
		else
			i++;
	}
}

static int expand_sign(t_token *token, int i)
{
	char	*input;
	char	*front_str;
	char	*parameter;
	char	*back_str;
	int		len;

	input = token->word;
	len = 0;
	front_str = ft_substr(input, 0, i);
	while (input[i + 1 + len] != 0)
	{
		if (is_whitespace(input[i + 1 + len]) == true || input[i + 1 + len] == '\'' \
			|| input[i + 1 + len] == '\"' || input[i + 1 + len] == '$')
			break;
		len++;
	}
	parameter = convert_variable(ft_substr(input, i + 1, len));
	back_str = ft_substr(input, i + 1 + len, ft_strlen(&input[i + 1 + len]));
	len = ft_strlen(parameter);
	join_string(token, front_str, parameter, back_str);
	return (len);
}

static char *convert_variable(char *parameter)
{
    int     i;
    char    *value;
	int		len;

	i = 0;
	len = ft_strlen(parameter);
	value = ft_strdup("");
    while(environ[i] != NULL)
	{
		if (ft_strncmp(environ[i], parameter, len) == 0)
		{
			if (environ[i][len] == '=')
			{
				free(value);
				value = ft_substr(environ[i], len + 1, ft_strlen(&environ[i][len + 1]));
				break;
			}	
		}
		i++;
	}
	free(parameter);
	return(value);
}

void join_string(t_token *token, char *front, char *mid, char *back)
{
	char *temp;
	char *result;

	temp = ft_strjoin(front, mid);
	free(front);
	front = NULL;
	free(mid);
	mid = NULL;
	result = ft_strjoin(temp, back);
	free(temp);
	temp = NULL;
	free(back);
	back = NULL;
	free(token->word);
	token->word = NULL;
	token->word = result;
}