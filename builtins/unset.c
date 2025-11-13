/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 13:54:59 by jarregui          #+#    #+#             */
/*   Updated: 2025/10/07 23:05:28 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_token_valid_or_warn(char *key, t_shell *shell)
{
	if (!is_valid_key(key))
	{
		printf("unset: `%s': not a valid identifier\n", key);
		shell->last_status = 1;
		return (0);
	}
	return (1);
}

void	unset_key_from_env(char *key, t_shell *shell)
{
	int		i;
	int		j;
	size_t	key_len;

	if (!shell || !shell->env || !key)
		return ;
	key_len = ft_strlen(key);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], key, key_len) == 0
			&& shell->env[i][key_len] == '=')
		{
			free(shell->env[i]);
			j = i;
			while (shell->env[j])
			{
				shell->env[j] = shell->env[j + 1];
				j++;
			}
			return ;
		}
		i++;
	}
}

void	ft_unset(char **tokens, t_shell *shell)
{
	int	i;

	i = 1;
	while (tokens[i])
	{
		if (!is_token_valid_or_warn(tokens[i], shell))
		{
			i++;
			continue ;
		}
		unset_key_from_env(tokens[i], shell);
		shell->last_status = 0;
		i++;
	}
}
