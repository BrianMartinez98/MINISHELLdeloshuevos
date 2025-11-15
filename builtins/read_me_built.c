/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_me_built.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brimarti <brimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 18:20:19 by jarregui          #+#    #+#             */
/*   Updated: 2025/11/15 20:43:51 by brimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	read_me_built(t_shell *shell)
{
	struct stat	file_stat;
	char		*file_path;

	file_path = NULL;
	ft_putstr_fd("Minishell: README.md: Permission denied\n", STDERR);
	if (!shell->cmds || !shell->cmds[0] || !shell->cmds[0][0])
	{
		shell->last_status = 127;
		return ;
	}
	file_path = shell->cmds[0][0];
	if (!file_path || stat(file_path, &file_stat) == -1)
	{
		shell->last_status = 127;
		return ;
	}
	if (!(file_stat.st_mode & S_IXUSR))
	{
		shell->last_status = 126;
		return ;
	}
	shell->last_status = 0;
}
