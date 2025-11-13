/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 01:24:42 by jarregui          #+#    #+#             */
/*   Updated: 2025/08/07 01:29:31 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_readline(t_shell *shell)
{
	ft_free_line(shell);
	shell->line = readline(shell->prompt);
}

void	ft_free_line(t_shell *shell)
{
	if (shell->line)
		free(shell->line);
	shell->line = NULL;
}
