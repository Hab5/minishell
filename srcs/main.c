#include "../include/minishell.h"

char        **usr_prompt(char **cmd, char **env)
{
    int     ret;
    char    *input;
    char    *cleaninput;

    input = NULL;
    cmd = NULL;
    print_prompt();
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

int             execute(char **cmd, char **env)
{
    pid_t       pid;
    char        *binpath;
    
    if(check_builtin(cmd, env) != 0)
        return (1); 
    if(check_current(cmd, pid) > 0)
        return (1);
    if ((binpath = look_in_path(cmd, env)) == NULL)
    {
        if(cmd[0])
        {
            ft_putstr("minishell: command not found: ");
            ft_putendl(cmd[0]);
        }
        return (-1);
    }
    run(binpath, cmd, env, pid);
    free(binpath);
    wait(&pid);
    return (1);
}

int         main(int argc, char **argv, char **env)
{
    char    **cmd;
    
    welcome();
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