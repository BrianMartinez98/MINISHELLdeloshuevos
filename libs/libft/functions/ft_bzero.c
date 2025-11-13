/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juancho <juancho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 18:53:55 by juancho           #+#    #+#             */
/*   Updated: 2023/12/14 12:23:51 by juancho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_bzero(void *s, unsigned int n)
{
	ft_memset(s, 0, n);
}

/* According to the man this function writes n zeroed bytes to the string s. If
n is zero, ft_bzero does nothing. Another way of saying this is that we will
be making a string of size n and filling each index position with a 0. We
use our previously made ft_memset function to do this. Review ft_memset to
understand how it works and notice the parameters we give it here when we
call it. We set it ahead of time to fill whatever string at size n with 0s.*/