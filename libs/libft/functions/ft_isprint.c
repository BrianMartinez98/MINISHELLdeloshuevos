/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juancho <juancho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 12:03:22 by jarregui          #+#    #+#             */
/*   Updated: 2023/12/14 12:23:51 by juancho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isprint(int c)
{
	if (c >= ' ' && c <= '~')
		return (1);
	return (0);
}

/* 
Printable ascii characteres are from 32 ' ' (space) 
to 126 '~'
Characters from 0 to 31 and 127 are not printable.
For more info check 'man ascii'
*/