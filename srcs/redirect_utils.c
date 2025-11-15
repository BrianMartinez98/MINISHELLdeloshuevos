/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brimarti <brimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:28:43 by jarregui          #+#    #+#             */
/*   Updated: 2025/11/13 15:10:02 by brimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_left(t_shell *shell, char **cmd, int i)
{
	shell->fd = open(cmd[i], O_RDONLY);
	if (shell->fd == -1)
	{
		perror("open");
		return (-1);
	}
	if (shell->fd < 0)
	{
		perror(cmd[i]);
		return (-1);
	}
	dup2(shell->fd, STDIN_FILENO);
	close(shell->fd);
	return (0);
}

static int	handle_pipe_err(char *delimiter)
{
	perror("pipe");
	free(delimiter);
	return (-1);
}

static int	handle_fork_err(int *pipefd, char *delimiter)
{
	perror("fork");
	close(pipefd[0]);
	close(pipefd[1]);
	free(delimiter);
	return (-1);
}

static int	check_heredoc_signal(int status, t_shell *shell, int *pipefd)
{
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(pipefd[0]);
		shell->last_status = 130;
		return (1);
	}
	return (0);
}

char    *find_delimeter(char *line)
{
    int i;
    int start;
    int end;

    if (!line)
        return (NULL);
    i = 0;
    while (line[i])
    {
        if (line[i] == '<' && line[i + 1] == '<')
            break;
        i++;
    }
    if (!line[i])
        return (NULL);
    i += 2;
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if (!line[i])
        return (NULL);
    start = i;
    while (line[i] && line[i] != ' ' && line[i] != '\t')
        i++;
    end = i;
    return (ft_substr(line, start, end - start));
}


int	ft_leftleft(t_shell *shell, char **cmd, int i)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;
	char	*delimiter;
	int		expand;

	delimiter = find_delimeter(shell->line);
	i = i;
	cmd = cmd;
	if (!delimiter)
		return (-1);
	expand = remove_quotes_and_check_expand(&delimiter);
	if (pipe(pipefd) == -1)
		return (handle_pipe_err(delimiter));
	pid = fork();
	if (pid < 0)
		return (handle_fork_err(pipefd, delimiter));
	if (pid == 0)
		heredoc_child(shell, pipefd, delimiter, expand);
	free(delimiter);
	close(pipefd[1]);
	waitpid(pid, &status, 0);
	if (check_heredoc_signal(status, shell, pipefd))
		return (-1);
	return (pipefd[0]);
}
