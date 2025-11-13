/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 13:54:59 by jarregui          #+#    #+#             */
/*   Updated: 2025/11/12 21:24:04 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_env(t_shell *shell)
{
	int	i;

	if (!shell->env)
	{
		printf("No environment variables set.\n");
		return ;
	}
	i = 0;
	if (DEBUG)
		printf(COL_MAGENTA "[\n" COL_RESET);
	while (shell->env[i])
	{
		if (DEBUG)
			printf(COL_MAGENTA "  \"" COL_RESET);
		printf("%s", shell->env[i]);
		if (DEBUG)
			printf(COL_MAGENTA "\"" COL_RESET);
		printf("\n");
		i++;
	}
	if (DEBUG)
		printf(COL_MAGENTA "  NULL\n]\n" COL_RESET);
}

char	*ft_getenv(t_shell *shell, const char *key)
{
	int		i;
	size_t	len;

	if (!shell || !shell->env || !key)
		return (NULL);
	i = 0;
	len = ft_strlen(key);
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], key, len) == 0
			&& shell->env[i][len] == '=')
			return (shell->env[i] + len + 1);
		i++;
	}
	return (NULL);
}

void	ft_free_env(t_shell *shell)
{
	int	i;

	if (!shell->env)
		return ;
	i = 0;
	while (shell->env[i])
	{
		free(shell->env[i]);
		i++;
	}
	free(shell->env);
	shell->env = NULL;
}

int	append_env(t_shell *shell, const char *entry)
{
	size_t	count;
	char	**new_vars;
	size_t	i;

	if (!shell || !entry)
		return (0);
	count = 0;
	while (shell->env && shell->env[count])
		count++;
	new_vars = malloc(sizeof(char *) * (count + 2));
	if (!new_vars)
		return (ft_error("Malloc failed for append_env"));
	i = 0;
	while (i < count)
	{
		new_vars[i] = shell->env[i];
		i++;
	}
	new_vars[count] = ft_strdup(entry);
	if (!new_vars[count])
		return (free(new_vars), ft_error("Malloc failed for append_env"));
	new_vars[count + 1] = NULL;
	free(shell->env);
	shell->env = new_vars;
	return (1);
}
