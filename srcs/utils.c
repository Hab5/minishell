#include "../include/minishell.h"

void free_arr(char **cmd)
{
    int i;
    
    i = -1;
    while (cmd[++i])
        ft_strdel(&cmd[i]);
    free(cmd);
    cmd = NULL;
}