/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 17:56:08 by jarregui          #+#    #+#             */
/*   Updated: 2025/11/15 18:26:52 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_fds_except(int keep1, int keep2, int keep3)
{
	long	max_fd;
	int		fd;

	fd = 3;
	max_fd = 1024;
	while (fd < (int)max_fd)
	{
		if (fd != keep1 && fd != keep2 && fd != keep3)
			close(fd);
		fd++;
	}
}

void	redirection_fail(t_fd fd)
{
	if (fd.in != -1 && fd.in != STDIN_FILENO)
	{
		if (dup2(fd.in, STDIN_FILENO) == -1)
		{
			close(fd.in);
			perror("dup2 in_fd");
			exit(1);
		}
	}
	if (fd.out != -1 && fd.out != STDOUT_FILENO)
	{
		if (dup2(fd.out, STDOUT_FILENO) == -1)
		{
			close(fd.out);
			perror("dup2 out_fd");
			exit(1);
		}
	}
}

void	pid_child(char **tokens, char **cmd, t_shell *shell, t_fd fd)
{
	char	*pathname;

	ft_setup_signals_child();
	redirection_fail(fd);
	if (shell->heredoc_fd != -1)
	{
		dup2(shell->heredoc_fd, STDIN_FILENO);
		close(shell->heredoc_fd);
		shell->heredoc_fd = -1;
	}
	handle_redirections(cmd, shell);
	close_fds_except(STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO);
	if (is_builtin(tokens))
	{
		ft_execute_builtin(tokens, shell);
		exit(shell->last_status % 256);
	}
	pathname = ft_execve_prep(&tokens, shell);
	execve(pathname, tokens, shell->env);
	perror(tokens[0]);
	ft_free_array(&tokens);
	if (errno == EACCES)
		exit(126);
	exit(127);
}
