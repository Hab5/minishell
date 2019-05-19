#include "../include/minishell.h"

char			*find_var(char *str)
{
	char buffer[4096];
	char *p = NULL;
	int i;

	i = 0;
	if(!(p = ft_strstr(str, "$")))
		return NULL;
	while(p[i] && (p[i] != ' ' && p[i] != '\t'))
	{
		buffer[i] = p[i];
		i++;
		if(p[i] == '$')
			break;
	}
	buffer[i] = '\0';
	return (ft_strdup(buffer));
}

char			*replace_str(char *str, char *orig, char *rep)
{
	static char	buffer[4096];
	char		temp[4096];
	char		*p;

	if(!(p = ft_strstr(str, orig)))
		return str;
	ft_strcpy(temp, (p));
	ft_strncpy(buffer, str, p-str);
	buffer[p-str] = '\0';
	ft_strcpy(buffer+(p-str), rep);
	free(str);
	return (ft_strjoin(buffer, temp+(ft_strlen(orig))));
}

char			*expand_in(char *cmd)
{
	int			offset;
	char		*temp;
	char		*var_content;
	char		*index;

	offset = 0;
	index = cmd;
	while ((index = ft_strstr(index + offset++, "$")) != 0)
	{
		if((temp = find_var(index)))
		{
			if(!(var_content = search_env(temp+1)))
				var_content = temp;
			cmd = replace_str(cmd, temp, var_content);
			free(temp);
			free(var_content);
		}
		else
			break;
	}
	if(!(var_content = search_env("HOME")))
		var_content = ft_strdup("~");
	while (ft_strstr(cmd, "~") != 0)
		cmd = replace_str(cmd, "~", var_content);
	free(var_content);
	return (cmd);
}

char			**expand(char **cmd)
{
	int			i;
	int			j;

	i = 0;
	j = -1;
	while (cmd[++j])
		cmd[j] = expand_in(cmd[j]);
	return (cmd);
}
