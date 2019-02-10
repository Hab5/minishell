#include "../include/minishell.h"

char	*clean_input(char *input)
{
	char	*cleanstr;
	char 	*temp;
	int		i;
	int		j;

	j = 0;
	i = 0;
	temp = ft_strtrim(input);
	cleanstr = ft_strnew(ft_strlen(temp) + 1);
	while (temp[i] != '\0')
	{
		if (temp[i] == ' ' || temp[i] == '\t')
		{
			cleanstr[j] = ' ';
			j++;
			while (temp[i] == ' ' || temp[i] == '\t')
				i++;
		}
		cleanstr[j] = temp[i];
		j++;
		i++;
	}
	ft_strdel(&temp);
	ft_strdel(&input);
	cleanstr[j] = '\0';
	return (cleanstr);
}

char        **split_input(char *input, char **cmd)
{
    int     i;

    i = 0;
    while(input[i])
        i++;
    cmd = ft_strsplit(input, ' ');
    cmd[i] = NULL;
    return (cmd);
}