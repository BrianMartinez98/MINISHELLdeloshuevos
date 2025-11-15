/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes_single.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:19:59 by jarregui          #+#    #+#             */
/*   Updated: 2025/11/15 17:50:44 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	cleanup_fds(int has_next, int pipefd[2], int in_fd)
{
	if (in_fd != -1)
		close(in_fd);
	if (has_next)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
}

static void	update_fds(int has_next, int pipefd[2], int *in_fd_ptr)
{
	if (has_next)
	{
		if (pipefd[1] >= 0)
			close(pipefd[1]);
		if (*in_fd_ptr != -1)
			close(*in_fd_ptr);
		*in_fd_ptr = pipefd[0];
	}
	else if (*in_fd_ptr != -1)
	{
		close(*in_fd_ptr);
		*in_fd_ptr = -1;
	}
}

static void	init_fd(t_fd *fd, int *in_fd_ptr, int has_next, int pipefd[2])
{
	if (has_next)
		fd->out = pipefd[1];
	else
		fd->out = -1;
	fd->in = *in_fd_ptr;
}

static void	close_heredoc(t_shell *shell)
{
	if (shell->heredoc_fd != -1)
	{
		close(shell->heredoc_fd);
		shell->heredoc_fd = -1;
	}
}

int	execute_single_pipe(t_shell *shell, int *in_fd_ptr, pid_t *pids)
{
	int		pipefd[2];
	int		has_next;
	char	**tokens;
	t_fd	fd;
	pid_t	pid;

	has_next = (shell->cmds[shell->i + 1] != NULL);
	if (has_next && pipe(pipefd) == -1)
		handle_error(PIPES, shell);
	if (check_heredoc(shell->cmds[shell->i], shell) == -1)
	{
		cleanup_fds(has_next, pipefd, *in_fd_ptr);
		return (shell->n);
	}
	filter_args(shell->cmds[shell->i], &tokens, shell);
	init_fd(&fd, in_fd_ptr, has_next, pipefd);
	pid = execute_command(shell, tokens, has_next, fd);
	close_heredoc(shell);
	if (pid > 0)
		pids[shell->n++] = pid;
	ft_free_array(&tokens);
	update_fds(has_next, pipefd, in_fd_ptr);
	return (shell->n);
}
