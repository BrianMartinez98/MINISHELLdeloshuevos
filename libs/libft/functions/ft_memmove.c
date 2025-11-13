/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juancho <juancho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 12:23:39 by jarregui          #+#    #+#             */
/*   Updated: 2023/12/14 12:23:51 by juancho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*cp_dst;
	unsigned const char	*cp_src;

	cp_dst = dst;
	cp_src = src;
	if (!dst && !src)
		return (0);
	if (cp_dst > cp_src)
	{
		cp_dst += len;
		cp_src += len;
		while (len--)
			*--cp_dst = *--cp_src;
	}
	else
		while (len--)
			*cp_dst++ = *cp_src++;
	return (dst);
}
