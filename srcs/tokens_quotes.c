/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 23:08:35 by jarregui          #+#    #+#             */
/*   Updated: 2025/11/07 17:34:16 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	closed_quotes(char *line, int i)
{
	int		e;
	char	quote_char;
	int		in_quotes;

	quote_char = line[i];
	e = i + 1;
	in_quotes = 0;
	while (line[e])
	{
		if (line[e] == quote_char)
		{
			in_quotes = 1;
			break ;
		}
		else
			e++;
	}
	if (in_quotes)
		return (e);
	return (i);
}

size_t	remove_quotes(char **cmd, t_span span)
{
	char	*value;
	char	*prefix;
	char	*suffix;
	char	*tmp;
	char	*new_cmd;

	value = ft_substr(*cmd, span.start + 1, span.end - span.start - 1);
	prefix = ft_substr(*cmd, 0, span.start);
	suffix = ft_substr(*cmd, span.end + 1, ft_strlen(*cmd) - span.end);
	tmp = ft_strjoin(prefix, value);
	span.end = ft_strlen(tmp);
	new_cmd = ft_strjoin(tmp, suffix);
	free(value);
	free(*cmd);
	free(prefix);
	free(suffix);
	free(tmp);
	*cmd = new_cmd;
	return (span.end - 1);
}
