/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 22:52:05 by jarregui          #+#    #+#             */
/*   Updated: 2025/11/07 17:30:50 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_pipes(t_shell *shell)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (shell->line[i])
	{
		if (shell->line[i] == '"' || shell->line[i] == '\'')
			i = closed_quotes(shell->line, i);
		else if (shell->line[i] == '|')
			count++;
		i++;
	}
	return (count);
}

char	*copy_token(char *line, t_span sp)
{
	size_t	len;
	char	*token;

	len = sp.end - sp.start;
	token = malloc(len + 1);
	if (!token)
		return (NULL);
	ft_strncpy(token, &line[sp.start], len);
	token[len] = '\0';
	return (token);
}

void	add_token(char **cmds, int *token_idx, char *line, t_span sp)
{
	char	*tok;

	tok = copy_token(line, sp);
	if (!tok)
	{
		perror("malloc token");
		return ;
	}
	cmds[(*token_idx)++] = tok;
	cmds[*token_idx] = NULL;
}

size_t	alloc_tokens(char **cmds, char *line)
{
	size_t	i;
	int		token_idx;
	t_span	sp;
	size_t	prev_i;

	i = 0;
	token_idx = 0;
	while (line[i] && line[i] != '|')
	{
		prev_i = i;
		if (!ft_next_span(line, &i, &sp))
			break ;
		if (i == prev_i)
		{
			i++;
			continue ;
		}
		add_token(cmds, &token_idx, line, sp);
	}
	cmds[token_idx] = NULL;
	return (i);
}
