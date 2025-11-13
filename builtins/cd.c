/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brimarti <brimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 19:46:54 by jarregui          #+#    #+#             */
/*   Updated: 2025/11/13 15:12:22 by brimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	change_path(char **tokens, t_shell *shell)
{
	const char	*path;

	if (!tokens[1])
	{
		path = getenv("HOME");
		if (!path)
			return (error_custom(shell, 1, "cd: HOME not set", NULL));
	}
	else if (tokens[2])
		return (error_custom(shell, 1, "cd: too many arguments", NULL));
	else
		path = tokens[1];
	if (chdir(path) != 0)
		return (error_custom(shell, 1, "cd: no such file or directory:",
				tokens[1]));
	free(shell->cwd);
	shell->cwd = getcwd(NULL, 0);
	if (!shell->cwd)
		return (error_custom(shell, 1, "cd: getcwd failed", NULL));
	ft_build_prompt(shell);
	return (0);
}
