/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 00:12:49 by jarregui          #+#    #+#             */
/*   Updated: 2025/11/07 17:48:08 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_build_prompt(t_shell *shell)
{
	char	*tmp;

	if (shell->prompt)
		free(shell->prompt);
	if (shell->cwd)
		free(shell->cwd);
	shell->prompt = NULL;
	shell->cwd = getcwd(NULL, 0);
	if (!shell->cwd)
		handle_error(GETCWD, shell);
	shell->prompt = ft_strjoin("\001\033[0;36m\033[1m\002", shell->cwd);
	tmp = shell->prompt;
	shell->prompt = ft_strjoin(tmp, " > \001\033[0m\002");
	free(tmp);
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

static void	copy_non_redirs(char **args, char ***tokens, t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (args[i])
	{
		if (is_redir_token(args[i]))
		{
			i++;
			if (args[i])
				i++;
			continue ;
		}
		(*tokens)[j++] = ft_strdup(args[i++]);
		if (!(*tokens)[j - 1])
			handle_error(MALLOCERROR, shell);
	}
	(*tokens)[j] = NULL;
}

static int	count_non_redirs(char **args)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (args[i])
	{
		if (is_redir_token(args[i]))
		{
			i++;
			if (args[i])
				i++;
			continue ;
		}
		count++;
		i++;
	}
	return (count);
}

void	filter_args(char **args, char ***tokens, t_shell *shell)
{
	int	count;

	if (!args || !tokens)
		return ;
	count = count_non_redirs(args);
	*tokens = malloc(sizeof(char *) * (count + 1));
	if (!*tokens)
		handle_error(MALLOCERROR, shell);
	copy_non_redirs(args, tokens, shell);
}
