/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 14:31:05 by jarregui          #+#    #+#             */
/*   Updated: 2025/11/12 15:31:35 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_free(char *s1, char *s2, int free_flag)
{
	char	*joined;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	joined = ft_strjoin(s1, s2);
	if (free_flag == 1 || free_flag == 3)
		free(s1);
	if (free_flag == 2 || free_flag == 3)
		free(s2);
	return (joined);
}

char	*ft_strjoin_char(char *s, char c)
{
	char	buf[2];
	char	*tmp;

	buf[0] = c;
	buf[1] = '\0';
	tmp = ft_strjoin(s, buf);
	free(s);
	return (tmp);
}

int	ft_redirect(t_shell *shell, char **cmd, int i)
{
	shell->fd = open(cmd[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (shell->fd < 0)
	{
		perror(cmd[i]);
		return (-1);
	}
	dup2(shell->fd, STDOUT_FILENO);
	close(shell->fd);
	return (0);
}

int	ft_adding(t_shell *shell, char **cmd, int i)
{
	shell->fd = open(cmd[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (shell->fd < 0)
	{
		perror(cmd[i]);
		return (-1);
	}
	dup2(shell->fd, STDOUT_FILENO);
	close(shell->fd);
	return (0);
}

int	is_redir_token(const char *t)
{
	if (!t)
		return (0);
	return (strcmp(t, "<") == 0
		|| strcmp(t, ">") == 0
		|| strcmp(t, "<<") == 0
		|| strcmp(t, ">>") == 0
		|| strcmp(t, "2>") == 0
		|| strcmp(t, "|") == 0);
}
