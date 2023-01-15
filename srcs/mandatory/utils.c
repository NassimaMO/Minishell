#include "minishell.h"

char	**add_split(char **split, char *str)
{
	int		i;
	char	**new_split;

	i = 0;
	while (split && split[i])
		i++;
	new_split = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (split && split[i])
	{
		new_split[i] = split[i];
		i++;
	}
	new_split[i] = str;
	new_split[i + 1] = NULL;
	free(split);
	return (new_split);
}

/* NEED NORM */
char	**get_cmd_args(const char *cmd)
{
	char	**split;
	char	*str;
	int		i;
	char	c;
	int		j;

	i = 0;
	split = NULL;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			c = cmd[i];
			str = ft_strdup(cmd + ++i);
			*ft_strchr(str, c) = 0;
			split = add_split(split, str);
			while (cmd[i] && cmd[i] != c)
				i++;
			i++;
		}
		else if (cmd[i] && cmd[i] != ' ')
		{
			str = ft_strdup(cmd + i);
			j = i;
			while (cmd[i] && cmd[i] != ' ' && cmd[i] != '\'' && cmd[i] != '"')
				i++;
			str[i - j] = 0;
			split = add_split(split, ft_substr(cmd + i, 0, i - j + 1));
		}
		while (cmd[i] == ' ')
			i++;
	}
	return (split);
}

char	**get_path(char *envp[])
{
	int		i;
	char	**split;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i])) == envp[i])
		{
			split = ft_split(envp[i], ':');
			if (!split)
				return (NULL);
			ft_strlcpy(split[0], split[0] + 5, ft_strlen(split[0] + 5) + 1);
			return (split);
		}
		i++;
	}
	split = malloc(sizeof(char *) * 2);
	if (!split)
		return (NULL);
	split[0] = ft_strdup("/bin/");
	split[1] = NULL;
	return (split);
}

char	*get_pathname(char *cmd, char *envp[])
{
	char	*s1;
	char	*s2;
	char	**split;
	int		i;

	split = get_path(envp);
	i = 0;
	cmd = ft_strtrim(cmd, " ");
	if (!cmd || !split)
		return (cmd);
	while (split[i])
	{
		s1 = ft_strjoin(split[i], "/");
		if (!s1)
			return (free(cmd), NULL);
		s2 = ft_strjoin(s1, cmd);
		free(s1);
		if (s2 && access(s2, X_OK) == 0)
			return (free_split(split), free(cmd), s2);
		i++;
		if (s2)
			free(s2);
	}
	return (free_split(split), free(cmd), s2);
}
