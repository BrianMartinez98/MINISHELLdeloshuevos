/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 08:50:15 by jarregui          #+#    #+#             */
/*   Updated: 2025/10/31 11:47:22 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	handle_quoted_segment(t_shell *shell, char **cmd, size_t i)
{
	t_span	span;
	char	quote;

	quote = (*cmd)[i];
	span.start = i;
	span.end = closed_quotes(*cmd, i);
	if (span.end == span.start)
		return (i + 1);
	i = remove_quotes(cmd, span);
	span.end = i;
	if (quote == '"')
		i = expand_var(shell, cmd, span);
	return (i);
}

static size_t	handle_unquoted_segment(t_shell *shell, char **cmd, size_t i)
{
	t_span	span;

	span.start = i;
	while ((*cmd)[i] && (*cmd)[i] != '\'' && (*cmd)[i] != '"')
		i++;
	span.end = i - 1;
	if (span.end > span.start)
		i = expand_var(shell, cmd, span);
	return (i);
}

static void	parse_cmd(char **cmd_ptr, t_shell *shell, size_t i)
{
	char	*cmd;

	cmd = *cmd_ptr;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '"')
			i = handle_quoted_segment(shell, &cmd, i);
		else
			i = handle_unquoted_segment(shell, &cmd, i);
	}
	*cmd_ptr = cmd;
}

void	parse_cmds(t_shell *shell)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (shell->cmds[i])
	{
		j = 0;
		while (shell->cmds[i][j])
		{
			parse_cmd(&shell->cmds[i][j], shell, 0);
			j++;
		}
		i++;
	}
}
