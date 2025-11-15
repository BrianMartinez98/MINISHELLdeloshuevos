/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:11:34 by jarregui          #+#    #+#             */
/*   Updated: 2025/11/12 15:18:02 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	append_var_value(char **res, t_shell *sh, const char *line,
	size_t *i)
{
	size_t	start;
	char	*name;
	char	*value;

	start = *i;
	while (ft_isalnum(line[*i]) || line[*i] == '_')
		(*i)++;
	name = ft_substr(line, start, *i - start);
	value = get_env_value(sh, name);
	if (value)
		*res = ft_strjoin_free(*res, value, 1);
	free(name);
}

static void	handle_dollar(char **res, t_shell *sh, const char *line, size_t *i)
{
	(*i)++;
	if (line[*i] == '?')
	{
		*res = ft_strjoin_free(*res, ft_itoa(sh->last_status), 3);
		(*i)++;
	}
	else if (ft_isalpha(line[*i]) || line[*i] == '_')
		append_var_value(res, sh, line, i);
	else
		*res = ft_strjoin_char(*res, '$');
}

char	*expand_heredoc_line(const char *line, t_shell *sh)
{
	char	*res;
	size_t	i;

	if (!line)
		return (NULL);
	res = ft_strdup("");
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
			handle_dollar(&res, sh, line, &i);
		else
			res = ft_strjoin_char(res, line[i++]);
	}
	return (res);
}

int	remove_quotes_and_check_expand(char **delimiter)
{
	int		expand;
	char	*new_delim;

	expand = 0;
	if (!delimiter || !*delimiter)
		return (expand);
	new_delim = *delimiter;
	if (new_delim[0] == '"'
			&& new_delim[ft_strlen(new_delim) - 1] == '"')
	{
		new_delim = ft_substr(new_delim, 1, ft_strlen(new_delim) - 2);
		free(*delimiter);
		*delimiter = new_delim;
	}
	else if (new_delim[0] == '\''
			&& new_delim[ft_strlen(new_delim) - 1] == '\'')
	{
		new_delim = ft_substr(new_delim, 1, ft_strlen(new_delim) - 2);
		free(*delimiter);
		*delimiter = new_delim;
	}
	return (expand);
}
