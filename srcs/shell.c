/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:00:40 by jarregui          #+#    #+#             */
/*   Updated: 2025/11/15 20:46:45 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_shell	*ft_get_shell_address(t_shell *new_shell)
{
	static t_shell	*shell_ptr = NULL;

	if (new_shell)
		shell_ptr = new_shell;
	return (shell_ptr);
}

void	ft_disable_echoctl(t_shell *shell)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	shell->termios_saved = term;
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	ft_restore_term_settings(t_shell *shell)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &shell->termios_saved);
}

static void	extra_init(t_shell *shell)
{
	shell->fd = -1;
	shell->heredoc_fd = -1;
	shell->is_child = 0;
	shell->len = 0;
	shell->cmds = NULL;
	shell->nread = 0;
	shell->i = 0;
	shell->n = 0;
	shell->flag = 0;
	shell->syntax_error = 0;
}

void	ft_init_shell(t_shell *shell, char **env)
{
	if (ft_env_init(shell, env) && DEBUG)
		printf(COL_MAGENTA "DEBUG: Environment initialized OK\n" COL_RESET);
	shell->cwd = NULL;
	shell->prompt = NULL;
	shell->hist = NULL;
	shell->status = 0;
	shell->last_status = 0;
	shell->exit = 0;
	shell->builtin = 0;
	shell->eof = 0;
	shell->line = NULL;
	shell->line2 = NULL;
	shell->stdin_save = STDIN_FILENO;
	shell->stdout_save = STDOUT_FILENO;
	restore_std(shell);
	extra_init(shell);
	ft_get_shell_address(shell);
	ft_disable_echoctl(shell);
}
