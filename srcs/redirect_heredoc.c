/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 14:27:07 by jarregui          #+#    #+#             */
/*   Updated: 2025/11/12 15:15:50 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_heredoc_warning(const char *delimiter)
{
	char	buffer[256];

	ft_strlcpy(buffer,
		"minishell: warning: here-document delimited by end-of-file (wanted `",
		sizeof(buffer));
	ft_strlcat(buffer, delimiter, sizeof(buffer));
	ft_strlcat(buffer, "')", sizeof(buffer));
	ft_putendl_fd(buffer, STDERR_FILENO);
}

static void	process_heredoc_line(t_shell *shell, int fd, char *line, int expand)
{
	char	*expanded;

	if (expand)
		expanded = expand_heredoc_line(line, shell);
	else
		expanded = ft_strdup(line);
	write(fd, expanded, ft_strlen(expanded));
	write(fd, "\n", 1);
	free(expanded);
}

static int	is_end_heredoc(t_shell *shell, char *line, char *delimiter)
{
	if (shell->nread == -1)
	{
		print_heredoc_warning(delimiter);
		free(line);
		return (1);
	}
	line[shell->nread - 1] = '\0';
	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		return (1);
	}
	return (0);
}

void	heredoc_child(t_shell *shell, int *pipefd, char *delimiter, int expand)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	close(pipefd[0]);
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = NULL;
		shell->nread = getline(&line, &shell->len, stdin);
		if (is_end_heredoc(shell, line, delimiter))
			break ;
		process_heredoc_line(shell, pipefd[1], line, expand);
		free(line);
	}
	close(pipefd[1]);
	exit(0);
}
