/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:26:27 by jarregui          #+#    #+#             */
/*   Updated: 2025/11/13 10:51:20 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	check_path_errors(t_shell *shell, char *pathname)
{
	struct stat	st;

	if (stat(pathname, &st) == -1)
	{
		if (errno == ENOENT)
			error_custom(shell, 127, "no such file or directory:", pathname);
	}
	else if (S_ISDIR(st.st_mode))
		error_custom(shell, 126, "is a directory:", pathname);
	else if (access(pathname, X_OK) != 0)
		error_custom(shell, 126, "permission denied:", pathname);
}

static void	check_split_spaces(char ***tkns_ptr)
{
	char	**split_tokens;
	char	**tokens;
	int		space_count;
	size_t	i;

	tokens = *tkns_ptr;
	if (!tokens || !tokens[0] || tokens[1])
		return ;
	space_count = 0;
	i = 0;
	while (tokens[0][i])
	{
		if (tokens[0][i] == ' ')
			space_count++;
		i++;
	}
	if (space_count == 1)
	{
		split_tokens = ft_split(tokens[0], ' ');
		if (split_tokens && split_tokens[0])
		{
			ft_free_array(tkns_ptr);
			*tkns_ptr = split_tokens;
		}
	}
}

char	*ft_execve_prep(char ***tkns_ptr, t_shell *shell)
{
	char	**paths;
	char	*pathname;

	check_split_spaces(tkns_ptr);
	paths = paths_finder(shell->env);
	pathname = command_finder(*tkns_ptr, paths);
	free_paths(paths);
	if (!pathname && !is_builtin(*tkns_ptr))
		error_custom(shell, 127, "minishell: command not found:", *tkns_ptr[0]);
	if (!(*tkns_ptr)[0] || !*(*tkns_ptr)[0])
		exit(0);
	if (is_path_like(pathname))
		check_path_errors(shell, pathname);
	if (DEBUG)
		printf(COL_MAGENTA "pathname: %s\n" COL_RESET, pathname);
	return (pathname);
}
