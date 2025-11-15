/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 18:41:31 by jarregui          #+#    #+#             */
/*   Updated: 2025/11/15 21:39:58 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_sig(t_shell *shell, char *msg, int status)
{
	write(1, msg, ft_strlen(msg));
	shell->last_status = status;
}

void	ft_wait_children(t_shell *shell, pid_t *pids)
{
	int	j;
	int	sig;

	j = 0;
	shell->status = 0;
	while (j < shell->n)
	{
		if (waitpid(pids[j], &shell->status, 0) == -1)
		{
			if (errno != ECHILD)
				perror("waitpid");
		}
		else if (WIFSIGNALED(shell->status))
		{
			sig = WTERMSIG(shell->status);
			if (sig == SIGINT)
				handle_sig(shell, "\n", 130);
			else if (sig == SIGQUIT)
				handle_sig(shell, "Quit (core dumped)\n", 131);
		}
		else if (WIFEXITED(shell->status))
			shell->last_status = WEXITSTATUS(shell->status);
		j++;
	}
}

void	restore_stdio(t_shell *shell)
{
	if (shell->stdin_save != STDIN_FILENO)
	{
		dup2(shell->stdin_save, STDIN_FILENO);
		close(shell->stdin_save);
		shell->stdin_save = STDIN_FILENO;
	}
	if (shell->stdout_save != STDOUT_FILENO)
	{
		dup2(shell->stdout_save, STDOUT_FILENO);
		close(shell->stdout_save);
		shell->stdout_save = STDOUT_FILENO;
	}
	if (!shell->builtin)
	{
		if (WIFEXITED(shell->status))
			shell->last_status = WEXITSTATUS(shell->status);
		else if (WIFSIGNALED(shell->status))
			shell->last_status = 128 + WTERMSIG(shell->status);
	}
	shell->builtin = 0;
}

int	error_check(int saved_stdin, int saved_stdout)
{
	perror("dup");
	if (saved_stdin != -1)
		close(saved_stdin);
	if (saved_stdout != -1)
		close(saved_stdout);
	return (-1);
}

pid_t	fork_and_exec_builtin(char **tokens, t_shell *shell, t_fd fd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (error_custom(shell, 1, "fork error", NULL));
	if (pid == 0)
	{
		shell->is_child = 1;
		ft_setup_signals_child();
		redirection_fail(fd);
		if (shell->heredoc_fd != -1)
		{
			dup2(shell->heredoc_fd, STDIN_FILENO);
			close(shell->heredoc_fd);
			shell->heredoc_fd = -1;
		}
		handle_redirections(shell->cmds[shell->i], shell);
		close_fds_except(STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO);
		ft_execute_builtin(tokens, shell);
		exit(shell->last_status % 256);
	}
	else
		shell->is_child = 0;
	return (pid);
}
