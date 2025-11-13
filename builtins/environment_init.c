/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 13:54:59 by jarregui          #+#    #+#             */
/*   Updated: 2025/11/12 22:13:43 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_env_default(t_shell *shell)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		cwd = ft_strdup("");
	shell->env[0] = ft_strjoin("PWD=", cwd);
	free(cwd);
	shell->env[1] = ft_strdup("SHLVL=1");
	shell->env[2] = NULL;
}

static int	get_num_variables(char **env_array)
{
	int		num_variables;

	num_variables = 0;
	if (DEBUG && (!env_array || !env_array[0]))
		printf(COL_MAGENTA "NO EXISTE ENTORNO SISTEMA\n" COL_RESET);
	if (!env_array || !env_array[0])
		num_variables = 2;
	else
		while (env_array[num_variables])
			num_variables++;
	return (num_variables);
}

int	ft_env_init(t_shell *shell, char **env_array)
{
	int		i;
	int		num_variables;

	i = 0;
	num_variables = get_num_variables(env_array);
	shell->env = malloc(sizeof(char *) * (num_variables + 1));
	if (!shell->env)
		return (ft_error("Memory allocation failed for env copy"));
	if (!env_array || !env_array[0])
		ft_env_default(shell);
	else
	{
		while (i < num_variables)
		{
			shell->env[i] = ft_strdup(env_array[i]);
			if (!shell->env[i])
				return (ft_error("Memory allocation failed for env entry"));
			i++;
		}
		shell->env[num_variables] = NULL;
	}
	return (num_variables);
}
