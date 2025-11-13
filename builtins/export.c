/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 13:54:59 by jarregui          #+#    #+#             */
/*   Updated: 2025/11/13 12:16:52 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	find_env_index(char **envp, const char *key)
{
	int		i;
	size_t	key_len;

	if (!envp)
		return (-1);
	i = 0;
	key_len = ft_strlen(key);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static char	*get_key(const char *entry)
{
	char	*eq;

	eq = ft_strchr(entry, '=');
	if (!eq)
		return (NULL);
	return (ft_substr(entry, 0, eq - entry));
}

void	ft_env_set(t_shell *shell, const char *entry, char *equal)
{
	int		index;
	char	*key;
	char	*value;

	if (!shell || !entry)
		return ;
	key = get_key(entry);
	if (!key)
		return ;
	value = ft_strdup(equal + 1);
	index = find_env_index(shell->env, key);
	if (index != -1)
	{
		free(shell->env[index]);
		shell->env[index] = ft_strdup(entry);
	}
	else
		append_env(shell, entry);
	free(value);
	free(key);
}

static void	export_token(t_shell *shell, char *token)
{
	char	*equal;
	char	*key;

	equal = ft_strchr(token, '=');
	if (equal)
		key = ft_substr(token, 0, equal - token);
	else
		key = ft_strdup(token);
	if (!(ft_isalpha(key[0]) || key[0] == '_'))
		error_custom(shell, 1, "export: not a valid identifier", key);
	else if (!is_valid_key(key))
		error_custom(shell, 1, "export: not valid in this context:", key);
	else if (equal && !is_valid_value(equal))
		error_custom(shell, 2, "syntax error near unexpected token", NULL);
	else
		ft_env_set(shell, token, equal);
	free(key);
}

void	ft_export(char **tokens, t_shell *shell)
{
	int	i;

	if (!shell || !tokens)
		return ;
	shell->last_status = 0;
	if (!tokens[1])
		return (ft_print_env(shell));
	i = 1;
	while (tokens[i])
	{
		export_token(shell, tokens[i]);
		i++;
	}
}
