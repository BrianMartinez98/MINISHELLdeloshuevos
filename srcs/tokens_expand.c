/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brimarti <brimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 22:30:31 by jarregui          #+#    #+#             */
/*   Updated: 2025/11/13 23:30:24 by brimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_value(t_shell *shell, const char *key)
{
	char	*value;

	if (key[0] == '?')
		value = ft_itoa(shell->last_status);
	else
		value = ft_getenv(shell, key);
	if (!value)
		value = ft_strdup("");
	return (value);
}

static size_t	expand(t_shell *shell, char **cmd, const char *key, t_span span)
{
	char	*value;
	char	*prefix;
	char	*suffix;
	char	*tmp;
	char	*new_cmd;

	value = get_env_value(shell, key);
	if (span.end > ft_strlen(*cmd))
		span.end = ft_strlen(*cmd);
	prefix = ft_substr(*cmd, 0, span.start);
	suffix = ft_substr(*cmd, span.end, ft_strlen(*cmd) - span.end);
	tmp = ft_strjoin(prefix, value);
	span.end = ft_strlen(tmp);
	new_cmd = ft_strjoin(tmp, suffix);
	if (ft_strcmp(key, "?") == 0 || ft_strcmp(value, "") == 0)
		free(value);
	free(*cmd);
	free(prefix);
	free(suffix);
	free(tmp);
	*cmd = new_cmd;
	return (span.end);
}

static size_t	set_key_span_end(char *cmd, size_t i, t_span *span)
{
	i++;
	if (cmd[i] == '?')
	{
		(*span).end = i + 1;
		return (i);
	}
	else
	{
		while (cmd[i] && (ft_isalnum(cmd[i]) || cmd[i] == '_'))
			i++;
		(*span).end = i;
	}
	return (i);
}

size_t	expand_var(t_shell *shell, char **cmd, t_span span)
{
	size_t		i;
	const char	*key;
	t_span		key_span;

	i = span.start;
	while ((*cmd)[i] && i < span.end)
	{
		if ((*cmd)[i] == '$')
		{
			key_span.start = i;
			i = set_key_span_end(*cmd, i, &key_span);
			if (key_span.end > key_span.start + 1)
			{
				key = ft_substr((*cmd), key_span.start + 1,
						key_span.end - (key_span.start + 1));
				i = expand(shell, cmd, key, key_span);
				span.end = i;
				free((void *)key);
			}
		}
		else
			i++;
	}
	return (i);
}
