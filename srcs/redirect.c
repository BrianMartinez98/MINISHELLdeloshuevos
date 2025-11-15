/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 19:51:04 by jarregui          #+#    #+#             */
/*   Updated: 2025/11/15 21:25:52 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_redirect(char *arg)
{
	if (!arg)
		return (0);
	if (ft_strcmp(arg, "<") == 0
		|| ft_strcmp(arg, ">") == 0
		|| ft_strcmp(arg, ">>") == 0
		|| ft_strcmp(arg, "<<") == 0)
		return (1);
	return (0);
}

int	has_redirections(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (is_redirect(cmd[i]))
			return (1);
		i++;
	}
	return (0);
}

int	handle_redirections(char **cmd, t_shell *shell)
{
	int	i;
	int	value;

	i = 0;
	value = 0;
	while (cmd[i])
	{
		if (cmd[i + 1] && is_redirect(cmd[i]))
		{
			if (ft_strcmp(cmd[i], "<") == 0)
				value = ft_left(shell, cmd, i + 1);
			else if (ft_strcmp(cmd[i], ">") == 0)
				value = ft_redirect(shell, cmd, i + 1);
			else if (ft_strcmp(cmd[i], ">>") == 0)
				value = ft_adding(shell, cmd, i + 1);
		}
		if (value == -1)
		{
			shell->last_status = 1;
			exit(shell->last_status);
		}
		i++;
	}
	return (value);
}

int	check_heredoc(char **cmd, t_shell *shell)
{
	int	i;
	int	fd;

	i = 0;
	fd = -1;
	while (cmd[i])
	{
		if (ft_strcmp(cmd[i], "<<") == 0)
		{
			if (!cmd[i + 1] || cmd[i + 1][0] == '\0'
					|| is_redir_token(cmd[i + 1]))
			{
				ft_putendl_fd(
					"minishell: syntax error near unexpected token `newline'",
					STDERR_FILENO);
				return (-1);
			}
			fd = ft_leftleft(shell, cmd, i);
			if (fd == -1)
				return (-1);
			shell->heredoc_fd = fd;
		}
		i++;
	}
	return (0);
}

void	restore_std(t_shell *shell)
{
	dup2(shell->stdin_save, STDIN_FILENO);
	dup2(shell->stdout_save, STDOUT_FILENO);
}
