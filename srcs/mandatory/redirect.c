#include "minishell.h"

char	*delimiter(char *str)
{
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != '<')
		i++;
	if (str[i])
		i++;
	if (str[i] && str[i] == '<')
		i++;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	j = i;
	while (str[j] && str[j] != ' ' && str[j] != '\t')
		j++;
	return (ft_substr(str, i, j - i));
}

/* changes str to remove redirection and changes fd[0] */
void	redirect_stdin(char *str, int fd[2])
{
	char	*name;
	char	*line;
	char	*tmp;
	char	**history;

	history = NULL;
	fd[0] = 0;
	if (!ft_strchr(str, '<'))
		return ;
	line = ft_strdup(str);
	name = delimiter(line);
	if (ft_strnstr(line, "<<", ft_strlen(line)))
	{
		ft_printf(">");
		tmp = get_input(history);
		while (tmp && (ft_strncmp(tmp, name, ft_strlen(name)) || (ft_strlen(name) != ft_strlen(tmp))))
		{
			ft_printf("\n>");
			tmp = get_input(history);
		}
	}
	*ft_strchr(line, '<') = 0;
	line = gnl_join(line, ft_strchr(name, 32), ft_strlen(ft_strchr(name, 32)));
	if (ft_strchr(name, ' '))
		*ft_strchr(name, ' ') = 0;
	fd[0] = open(name, O_RDONLY);
	ft_strlcpy(str, line, ft_strlen(line) + 1);
	return (free(name), free(line), free_split(history));
}

/* changes str to remove redirection and changes fd[1] */
void	redirect_stdout(char *str, int fd[2])
{
	char	*name;
	int		append;
	char	*line;

	fd[1] = 1;
	if (!ft_strchr(str, '>'))
		return ;
	line = ft_strdup(str);
	name = ft_strchr(line, '>') + 1;
	append = 0;
	if (name[0] == '>')
	{
		append = 1;
		name ++;
	}
	name = ft_strtrim(name, " \t");
	*ft_strchr(line, '>') = 0;
	line = gnl_join(line, ft_strchr(name, 32), ft_strlen(ft_strchr(name, 32)));
	if (ft_strchr(name, ' '))
		*ft_strchr(name, ' ') = 0;
	if (append)
		fd[1] = open(name, O_FLAG2, S_FLAG);
	else
		fd[1] = open(name, O_FLAG, S_FLAG);
	return (ft_strlcpy(str, line, ft_strlen(line) + 1), free(name), free(line));
}