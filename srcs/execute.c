/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brimarti <brimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 19:47:59 by jarregui          #+#    #+#             */
/*   Updated: 2025/11/13 21:57:40 by brimarti         ###   ########.fr       */
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

static void	pid_child(char **tokens, char **cmd, t_shell *shell, t_fd fd)
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
	if (errno == EACCES)
		exit(126);
	exit(127);
}

static pid_t	fork_and_exec(char **tokens, char **cmd, t_shell *shell,
	t_fd fd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		error_custom(shell, 1, "fork error", NULL);
		return (-1);
	}
	if (pid == 0)
	{
		shell->is_child = 1;
		pid_child(tokens, cmd, shell, fd);
	}
	else
		shell->is_child = 0;
	return (pid);
}

pid_t	execute_command(t_shell *shell, char **tokens, int has_next, t_fd fd)
{
	pid_t	pid;

	if (!tokens || !tokens[0])
		return (-2);
	if (has_next)
	{
		if (is_builtin(tokens))
			pid = fork_and_exec_builtin(tokens, shell, fd);
		else
			pid = fork_and_exec(tokens, shell->cmds[shell->i], shell, fd);
	}
	else
	{
		if (is_builtin(tokens) && !has_next && fd.in == -1)
		{
			shell->builtin = 1;
			dup2(STDIN_FILENO, shell->stdin_save);
			dup2(STDOUT_FILENO, shell->stdout_save);
			handle_redirections(shell->cmds[shell->i], shell);
			ft_execute_builtin(tokens, shell);
			return (-2);
		}
		else
			pid = fork_and_exec(tokens, shell->cmds[shell->i], shell, fd);
	}
	return (pid);
}
