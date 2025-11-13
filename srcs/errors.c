/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brimarti <brimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 12:42:53 by jarregui          #+#    #+#             */
/*   Updated: 2025/11/13 14:36:24 by brimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_strjoin3(const char *s1, const char *s2, const char *s3)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(s1, s2);
	res = ft_strjoin(tmp, s3);
	free(tmp);
	return (res);
}

int	error_custom(t_shell *shell, int err_code, char *err_msg, char *err_key)
{
	char	*err;
	char	*temp_err;

	shell->last_status = err_code;
	if (err_key)
		temp_err = ft_strjoin3(err_msg, " ", err_key);
	else
		temp_err = err_msg;
	err = ft_strjoin(temp_err, "\n");
	if (DEBUG)
	{
		printf(COL_MAGENTA "Exit Error Code: %d\n" COL_RESET, err_code);
		printf(COL_MAGENTA "Error Message: %s\n" COL_RESET, err);
	}
	ft_putstr_fd(COL_RESET, STDERR);
	ft_putstr_fd(err, STDERR);
	if (err_key)
		free(temp_err);
	free(err);
	if (shell->is_child)
		exit(err_code);
	return (-1);
}

static void	print_errors(t_errorlst error, char *error_msg[])
{
	write(2, "ERROR: ", 7);
	if (error == FD)
		perror("open");
	else if (error >= 0 && error_msg[error])
		write(STDERR, error_msg[error], ft_strlen(error_msg[error]));
	else
		write(STDERR, "Unknown error\n", 14);
}

int	ft_error(const char *msg)
{
	if (msg)
		handle_error(MSG, NULL);
	return (1);
}

void	handle_error(t_errorlst error, t_shell *shell)
{
	char	*error_msg[42];

	if (DEBUG)
		printf(COL_MAGENTA "Error gestionado por handle_error\n" COL_RESET);
	error_msg[PIPES] = "Error en el pipe!\n";
	error_msg[MALLOCERROR] = "Error Malloc!\n";
	error_msg[FD] = "Fallo en el fd!\n";
	error_msg[GETCWD] = "Error en GETCWD!\n";
	error_msg[MSG] = "Error en el MSG!\n";
	error_msg[NCMD] = "Command not found!\n";
	print_errors(error, error_msg);
	ft_exit_shell(shell);
	exit(1);
}
