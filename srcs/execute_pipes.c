/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:19:59 by jarregui          #+#    #+#             */
/*   Updated: 2025/11/15 17:50:28 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_execute_pipes(t_shell *shell)
{
	int		in_fd;
	pid_t	pids[256];

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	shell->i = 0;
	while (shell->i < 256)
	{
		pids[shell->i] = 0;
		shell->i++;
	}
	in_fd = -1;
	shell->i = 0;
	shell->n = 0;
	while (shell->cmds[shell->i])
	{
		shell->n = execute_single_pipe(shell, &in_fd, pids);
		shell->i++;
	}
	if (in_fd != -1)
		close(in_fd);
	ft_wait_children(shell, pids);
	signal(SIGINT, ft_sigint_handler);
	signal(SIGQUIT, ft_sigquit_handler);
	restore_stdio(shell);
}
