/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 12:05:52 by jarregui          #+#    #+#             */
/*   Updated: 2025/11/13 12:05:57 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_key(const char *key)
{
	int	i;

	i = 0;
	if (!key || (!ft_isalpha(key[0]) && key[0] != '_'))
		return (0);
	while (key[i] && key[i] != '=')
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_value(char *equal)
{
	char	*value;
	int		valid;

	value = ft_strdup(equal + 1);
	valid = 1;
	if (!ft_strcmp(value, ">") || !ft_strcmp(value, ">>")
		|| !ft_strcmp(value, "<") || !ft_strcmp(value, "<<"))
		valid = 0;
	free(value);
	return (valid);
}
