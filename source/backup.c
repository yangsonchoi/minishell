


char *convert_variable(char *parameter, t_data *data)
{
    int     i;
    char    *value;
	int		len;

	i = 0;
	len = ft_strlen(parameter);
	value = ft_strdup("");
    while(data->envp[i] != NULL)
	{
		if (ft_strncmp(data->envp[i], parameter, len) == 0)
		{
			if (data->envp[i][len] == '=')
			{
				free(value);
				value = ft_substr(data->envp[i], len + 1, ft_strlen(&data->envp[i][len + 1]));
				break;
			}	
		}
		i++;
	}
	free(parameter);
	return(value);
}