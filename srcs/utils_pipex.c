/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:52:10 by jarregui          #+#    #+#             */
/*   Updated: 2025/11/07 17:34:55 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_path_like(const char *cmd)
{
	size_t	i;

	if (!cmd || !*cmd)
		return (0);
	if (cmd[0] == '/')
		return (1);
	if (cmd[0] == '.')
	{
		i = 1;
		while (cmd[i] == '.')
			i++;
		if (cmd[i] == '/')
			return (1);
		return (0);
	}
	return (0);
}

void	free_paths(char **paths)
{
	int	i;

	if (!paths)
		return ;
	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

char	**paths_finder(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			if (DEBUG)
				printf(COL_MAGENTA "%s\n" COL_RESET, env[i]);
			return (ft_split(env[i] + 5, ':'));
		}
		i++;
	}
	return (NULL);
}

static char	*get_pathname(char *path, char *command)
{
	char	*trimmed;
	char	*temp;
	char	*pathname;

	trimmed = ft_strtrim(path, "\n");
	if (!trimmed)
		return (NULL);
	temp = ft_strjoin(trimmed, "/");
	free(trimmed);
	if (!temp)
		return (NULL);
	pathname = ft_strjoin(temp, command);
	free(temp);
	return (pathname);
}

char	*command_finder(char **command, char **paths)
{
	int		i;
	char	*pathname;

	if (!command || !command[0] || !*command[0])
		return (NULL);
	if (is_path_like(command[0]))
		return (ft_strdup(command[0]));
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i] != NULL)
	{
		pathname = get_pathname(paths[i], command[0]);
		if (access(pathname, X_OK) == 0)
			return (pathname);
		if (!pathname)
			return (NULL);
		free(pathname);
		i++;
	}
	return (NULL);
}
