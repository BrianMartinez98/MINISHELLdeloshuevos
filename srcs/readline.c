/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 01:24:42 by jarregui          #+#    #+#             */
/*   Updated: 2025/11/15 17:23:51 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_readline(t_shell *shell)
{
	ft_free_line(shell);
	shell->syntax_error =  0;
	shell->line = readline(shell->prompt);
}

void	ft_free_line(t_shell *shell)
{
	if (shell->line)
		free(shell->line);
	shell->line = NULL;
}

char	**my_completion(const char *text, int start, int end)
{
	(void)end;
	if (start == 0 && text[0] == '\0')
	{
		rl_attempted_completion_over = 1;
		return (NULL);
	}
	return (rl_completion_matches(text, rl_filename_completion_function));
}
