/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:00:40 by jarregui          #+#    #+#             */
/*   Updated: 2025/11/07 15:02:04 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_array(char ***array)
{
	size_t	i;

	if (!array || !*array)
		return ;
	i = 0;
	while ((*array)[i])
	{
		free((*array)[i]);
		i++;
	}
	free(*array);
	*array = NULL;
}

void	ft_free_matrix(char ****matrix)
{
	size_t	i;

	if (!matrix || !*matrix)
		return ;
	i = 0;
	while ((*matrix)[i])
	{
		ft_free_array(&(*matrix)[i]);
		i++;
	}
	free(*matrix);
	*matrix = NULL;
}

int	ft_exit_shell(t_shell *shell)
{
	if (DEBUG && shell->eof)
		printf("\033[1;33m\n\t   ↳ Pulsada tecla Ctrl+D (EOF)\n\033[0m");
	printf("\033[1;32mExiting minishell...\033[0m\n");
	if (shell->prompt)
		free(shell->prompt);
	if (shell->cwd)
		free(shell->cwd);
	if (shell->hist)
		ft_free_history(shell);
	if (shell->env)
		ft_free_env(shell);
	if (shell->line)
		ft_free_line(shell);
	if (shell->line2)
		ft_free_line(shell);
	if (shell->cmds)
		ft_free_matrix(&shell->cmds);
	if (shell->stdin_save != -1)
		close(shell->stdin_save);
	if (shell->stdout_save != -1)
		close(shell->stdout_save);
	ft_restore_term_settings(shell);
	return (0);
}
