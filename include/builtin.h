#ifndef BUILTIN_H
# define BULITIN_H

enum e_builtin_type
{
    ECHO,
    CD,
    PWD,
    EXPORT,
    UNSET,
    ENV,
    EXIT,
};


/*
** builtin.c
*/
void    execute_builtin(char **cmd, t_data *data, enum e_builtin_type type);

/*
** builtin_echo.c
*/
void    builtin_echo(char **cmd, t_data *data);

/*
** builtin_cd.c
*/
void    builtin_cd(char **cmd, t_data *data);

/*
** builtin_pwd.c
*/
void    builtin_pwd(char **cmd, t_data *data);

/*
** builtin_pwd.c
*/
void    builtin_pwd(char **cmd, t_data *data);

/*
** builtin_pwd.c
*/


#endif