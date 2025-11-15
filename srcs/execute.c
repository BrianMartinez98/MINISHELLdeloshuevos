/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brimarti <brimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 19:47:59 by jarregui          #+#    #+#             */
/*   Updated: 2025/11/15 20:41:57 by brimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static pid_t	get_pid_has_next(t_shell *shell, char **tokens, t_fd fd)
{
	pid_t	pid;

	if (is_builtin(tokens))
		pid = fork_and_exec_builtin(tokens, shell, fd);
	else
	{
		if (is_builtin(tokens))
			pid = fork_and_exec_builtin(tokens, shell, fd);
		else
			pid = fork_and_exec(tokens, shell->cmds[shell->i], shell, fd);
	}
	return (pid);
}

pid_t	execute_command(t_shell *shell, char **tokens, int has_next, t_fd fd)
{
	pid_t	pid;

	if (!tokens || !tokens[0])
		return (-2);
	if (has_next)
		get_pid_has_next(shell, tokens, fd);
	else
	{
		if (is_builtin(tokens) && !has_next && !has_redirections(shell->cmds[shell->i]))
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
