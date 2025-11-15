/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brimarti <brimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 23:47:36 by jarregui          #+#    #+#             */
/*   Updated: 2025/11/13 13:29:33 by brimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	ft_init_shell(&shell, env);
	ft_build_prompt(&shell);
	rl_attempted_completion_function = my_completion;
	while (shell.exit == 0)
	{
		ft_setup_signals_prompt();
		ft_readline(&shell);
		if (!shell.line && !shell.exit)
			shell.eof = 1;
		if (!shell.line || shell.exit)
			break ;
		if (*shell.line == '\0')
			continue ;
		ft_add_history(&shell);
		split_line(&shell);
		if (!shell.cmds || !shell.cmds[0])
			continue ;
		ft_execute_pipes(&shell);
	}
	ft_exit_shell(&shell);
	exit(shell.last_status);
}

//tester: https://github.com/LucasKuhn/minishell_tester
