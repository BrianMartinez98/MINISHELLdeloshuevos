/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_remove.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:03:51 by jarregui          #+#    #+#             */
/*   Updated: 2025/11/07 15:04:53 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**ft_dup_matrix(char **src)
{
	int		i;
	char	**dup;

	i = 0;
	while (src[i])
		i++;
	dup = malloc(sizeof(char *) * (i + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dup[i] = ft_strdup(src[i]);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

void	remove_initial_empty_cmds(t_shell *shell)
{
	int		i;
	int		j;
	char	**new;
	char	**cmd;

	i = 0;
	while (shell->cmds[i])
	{
		cmd = shell->cmds[i];
		j = 0;
		while (cmd[j] && !*cmd[j])
			j++;
		if (!cmd[j])
		{
			ft_free_array(&cmd);
			shell->cmds[i++] = NULL;
			continue ;
		}
		new = ft_dup_matrix(cmd + j);
		ft_free_array(&cmd);
		shell->cmds[i++] = new;
	}
}
