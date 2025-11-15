/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:30:09 by jarregui          #+#    #+#             */
/*   Updated: 2025/11/15 20:43:07 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntax_pipe(t_shell *shell, int i)
{
	int	index;

	index = i + 1;
	shell->flag = 0;
	while (shell->line[index] == ' ')
		index++;
	if (shell->line[index] == '|' || shell->line[index] == '\0')
	{
		shell->flag = 1;
		ft_putendl_fd("Minishell: parse error near `|'", 2);
		shell->last_status = 1;
		ft_free_array(shell->cmds);
	}
	return (shell->flag);
}

static int	redir_syntax_error(t_shell *shell)
{
	error_custom(shell, 1,
		"Minishell: syntax error near unexpected token `>'", NULL);
	shell->syntax_error = 1;
	return (-1);
}

int	redir_syntax(t_shell *shell)
{
	char	*s;
	int		len;
	char	first;

	s = shell->line;
	while (*s)
	{
		if (*s == '<' || *s == '>')
		{
			len = 0;
			first = *s;
			while (*s == '<' || *s == '>')
			{
				if (*s != first)
					break ;
				len++;
				s++;
			}
			if ((len != 1 && len != 2) || *s == '<' || *s == '>')
				return (redir_syntax_error(shell));
			continue ;
		}
		s++;
	}
	return (0);
}
