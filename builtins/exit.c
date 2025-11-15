/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brimarti <brimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 17:03:58 by jarregui          #+#    #+#             */
/*   Updated: 2025/11/13 22:47:49 by brimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strisnum(const char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(t_shell *shell, char **cmd)
{
	shell->exit = 1;
	if (cmd[1] && cmd[2])
	{
		error_custom(shell, 1, "exit: too many arguments", NULL);
		shell->last_status = 1;
		ft_free_array(&cmd);
		exit(shell->last_status);
	}
	else if (cmd[1] && ft_strisnum(cmd[1]) == 0)
	{
		shell->last_status = 2;
		ft_putstr_fd("exit\n", STDERR);
		ft_putstr_fd("minishell: exit: ", STDERR);
		ft_putstr_fd(cmd[1], STDERR);
		ft_putendl_fd(": numeric argument required", STDERR);
		ft_free_array(&cmd);
		exit(shell->last_status);
	}
	else if (cmd[1])
	{
		shell->last_status = ft_atoi(cmd[1]);
		ft_free_array(&cmd);
		exit(shell->last_status);
	}
	else
	{
		shell->last_status = 0;
		ft_free_array(&cmd);
		exit(shell->last_status);
	}
}
