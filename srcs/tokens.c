/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brimarti <brimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:30:09 by jarregui          #+#    #+#             */
/*   Updated: 2025/11/13 13:27:57 by brimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	init_cmds(t_shell *shell)
{
	size_t	n;

	ft_free_matrix(&shell->cmds);
	n = count_pipes(shell) + 2;
	shell->cmds = ft_calloc(n, sizeof(char **));
	if (!shell->cmds)
		handle_error(MALLOCERROR, shell);
}

static int	syntax_pipe(t_shell *shell, int i)
{
	int	index;

	index = i + 1;
	shell->flag = 0;
	while (shell->line[index] == ' ')
		index++;
	if (shell->line[index] == '|' || shell->line[index] == '\0')
	{
		shell->flag = 1;
		ft_putendl_fd("Minishell: parse error near `|'", 2);
		shell->last_status = 1;
		ft_free_array(shell->cmds);
	}
	return (shell->flag);
}

static void	fill_cmds(t_shell *shell)
{
	size_t	i;

	i = 0;
	shell->n = 0;
	while (shell->line[i])
	{
		while (shell->line[i] == ' ')
			i++;
		if (shell->line[i] == '|')
		{
			if (syntax_pipe(shell, i))
				return ;
			i++;
			shell->n++;
			continue ;
		}
		if (!shell->cmds[shell->n])
		{
			shell->cmds[shell->n] = malloc(sizeof(char *) * (MAX_TOKENS + 1));
			if (!shell->cmds[shell->n])
				handle_error(MALLOCERROR, shell);
		}
		i += alloc_tokens(shell->cmds[shell->n], &shell->line[i]);
	}
	shell->cmds[shell->n + 1] = NULL;
}

void	split_line(t_shell *shell)
{
	init_cmds(shell);
	fill_cmds(shell);
	if (DEBUG)
	{
		printf(COL_MAGENTA "Tokens que nos llegan:\n" COL_RESET);
		print_tokens_array(shell);
	}
	parse_cmds(shell);
	remove_initial_empty_cmds(shell);
	if (DEBUG)
	{
		printf(COL_MAGENTA "Tras Elimin Quotes & Expan Variables:\n" COL_RESET);
		print_tokens_array(shell);
	}
}
