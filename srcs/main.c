#include "../include/minishell.h"

void        prompt_mod(char **promptpath, int i, char cwd[])
{
    ft_putstr("\033[1;32m");
    if (i > 2)
    {
        ft_putstr("[");
        ft_putstr(promptpath[i-2]);
        ft_putstr("/");
        ft_putstr(promptpath[i-1]);
        ft_putstr("]");
        ft_putstr(" » ");
    }
    else
    {
        ft_putstr("[");
        ft_putstr(cwd);
        ft_putstr("]");
        ft_putstr(" » ");
    }
    ft_putstr("\033[0m");
}

void        print_prompt()
{
    char    cwd[1024];
    char    **promptpath;
    int     i;

    getcwd(cwd, 1023);
    promptpath = ft_strsplit(cwd, '/');
    i = 0;
    while (promptpath[i])
        i++;
    prompt_mod(promptpath, i, cwd);
    free_arr(promptpath);
}

char        **usr_prompt(char **cmd)
{
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
    
    pid = 0;
    if(check_builtin(cmd) != 0)
        return (1); 
    if(check_current(cmd, pid) > 0)
        return (1);
    if ((binpath = look_in_path(cmd)) == NULL)
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
    
    (void)argc;
    (void)argv;
    cmd = NULL;
    if (env[0] == NULL)
    {
        ft_putstr("I need an env to work.\n");
        return (0);
    }
    welcome();
    init_env(env);
    while (1)
	{
        cmd = usr_prompt(cmd);
        if (cmd)
        {   
            execute(cmd, env);
            free_arr(cmd);
        }
    }
    return (0);
}