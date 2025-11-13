/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 01:23:43 by jarregui          #+#    #+#             */
/*   Updated: 2025/09/10 19:33:04 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_add_history(t_shell *shell)
{
	t_hist	*new_hist;
	t_hist	*last_hist;

	add_history(shell->line);
	new_hist = malloc(sizeof(t_hist));
	if (!new_hist)
	{
		perror("Memory allocation failed for history node");
		return ;
	}
	new_hist->line = ft_strdup(shell->line);
	new_hist->next = NULL;
	if (!shell->hist)
		shell->hist = new_hist;
	else
	{
		last_hist = shell->hist;
		while (last_hist->next)
			last_hist = last_hist->next;
		last_hist->next = new_hist;
		new_hist->prev = last_hist;
	}
}

void	ft_print_history(t_shell *shell)
{
	size_t	i;
	t_hist	*current_hist;

	i = 1;
	current_hist = shell->hist;
	while (current_hist)
	{
		printf("%zu  %s\n", i++, current_hist->line);
		current_hist = current_hist->next;
	}
}

void	ft_free_history(t_shell *shell)
{
	t_hist	*next;

	while (shell->hist)
	{
		next = shell->hist->next;
		free(shell->hist->line);
		free(shell->hist);
		shell->hist = next;
	}
}
