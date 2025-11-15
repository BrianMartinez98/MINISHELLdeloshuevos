/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_span.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 17:28:41 by jarregui          #+#    #+#             */
/*   Updated: 2025/11/15 16:35:04 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	skip_single_quotes(char *s, size_t *i)
{
	(*i)++;
	while (s[*i] && s[*i] != '\'')
		(*i)++;
	if (s[*i] == '\'')
		(*i)++;
}

static void	skip_double_quotes(char *s, size_t *i)
{
	(*i)++;
	while (s[*i] && s[*i] != '\"')
	{
		if (s[*i] == '\\' && s[*i + 1])
			(*i) += 2;
		else
			(*i)++;
	}
	if (s[*i] == '\"')
		(*i)++;
}

static void	read_word(char *s, size_t *i)
{
	while (s[*i] && !ft_isspace((unsigned char)s[*i]) && s[*i] != '|')
	{
		if (s[*i] == '\\' && s[*i + 1])
			(*i) += 2;
		else if (s[*i] == '\'')
			skip_single_quotes(s, i);
		else if (s[*i] == '\"')
			skip_double_quotes(s, i);
		else
		{
			if (s[*i + 1] && (s[*i + 1] == '<' || s[*i + 1] == '>'))
			{
				(*i)++;
				break ;
			}
			(*i)++;
		}
	}
}

static int	handle_redir(char *s, size_t *i, t_span *sp)
{
	char	op;

	op = s[*i];
	(*i)++;
	while (s[*i] == op)
		(*i)++;
	sp->end = *i;
	return (1);
}

int	ft_next_span(char *s, size_t *i, t_span *sp)
{
	size_t	start;

	if (!s || !i || !sp)
		return (0);
	while (s[*i] && ft_isspace((unsigned char)s[*i]))
		(*i)++;
	if (!s[*i] || s[*i] == '|')
		return (0);
	start = *i;
	sp->start = start;
	if (s[*i] == '<' || s[*i] == '>')
		return (handle_redir(s, i, sp));
	read_word(s, i);
	if (*i == start)
		(*i)++;
	sp->end = *i;
	return (1);
}
