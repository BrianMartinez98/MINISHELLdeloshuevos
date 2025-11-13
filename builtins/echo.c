/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 00:14:01 by jarregui          #+#    #+#             */
/*   Updated: 2025/10/31 10:29:13 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_echo_token(char *token, int *suppress_nl, int *supress_first)
{
	size_t	i;

	if (*supress_first && ft_strlen(token) >= 2)
	{
		if (token[0] == '-' && token[1] == 'n')
		{
			i = 2;
			while (token[i] == 'n')
				i++;
			if (token[i] == '\0')
			{
				*suppress_nl = 1;
				return (0);
			}
		}
	}
	if (ft_strcmp(token, "") == 0)
		return (0);
	*supress_first = 0;
	printf("%s", token);
	return (1);
}

void	ft_echo(char **tokens, t_shell *shell)
{
	int		i;
	int		suppress_nl;
	int		supress_first;
	int		printed;

	i = 1;
	suppress_nl = 0;
	supress_first = 1;
	while (tokens[i])
	{
		printed = ft_echo_token(tokens[i], &suppress_nl, &supress_first);
		if (printed && tokens[i + 1])
			printf(" ");
		i++;
	}
	if (!suppress_nl)
		printf("\n");
	shell->last_status = 0;
}
