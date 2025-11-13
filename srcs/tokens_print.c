/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 22:59:24 by jarregui          #+#    #+#             */
/*   Updated: 2025/11/07 14:12:16 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	print_tokens(char **tokens)
{
	size_t	i;

	if (!tokens)
		return (1);
	i = 0;
	while (tokens[i])
	{
		printf(COL_MAGENTA "		Token[%zu]: '" COL_RESET, i);
		printf("%s", tokens[i]);
		printf(COL_MAGENTA "'\n" COL_RESET);
		i++;
	}
	return (0);
}

void	print_tokens_array(t_shell *shell)
{
	size_t	i;

	if (DEBUG)
	{
		if (!shell->cmds)
		{
			printf(COL_MAGENTA "\nDEBUG: split_line, " COL_RESET);
			printf(COL_MAGENTA "no hay array de tokens!\n" COL_RESET);
		}
		else
		{
			printf(COL_MAGENTA "shell->cmds = \n[\n" COL_RESET);
			i = 0;
			while (shell->cmds[i])
			{
				printf(COL_MAGENTA "	[\n" COL_RESET);
				print_tokens(shell->cmds[i]);
				printf(COL_MAGENTA "	]\n" COL_RESET);
				i++;
			}
			printf(COL_MAGENTA "];\n\n" COL_RESET);
		}
	}
}
