#include "../include/minishell.h"

char        **usr_prompt(char **cmd, char **env)
{
    int     ret;
    char    *input;
    char    *cleaninput;

    input = NULL;
    cmd = NULL;
    ft_putstr("$>");
    if ((get_next_line(0, &input) != -1) && !ft_strequ(input, ""))
    {
        cleaninput = clean_input(input);
        cmd = split_input(cleaninput, cmd);
        ft_strdel(&cleaninput);
    }
    else
        ft_strdel(&input);
    
    return (cmd);
}

int         main(int argc, char **argv, char **env)
{
    char    **cmd;
    
    while (1)
	{
        cmd = usr_prompt(cmd, env);
        if (cmd)
        {   
            execute(cmd, env);
            free_arr(cmd);
        }
    }
    return (0);
}