/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juancho <juancho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 15:48:36 by jarregui          #+#    #+#             */
/*   Updated: 2023/12/14 12:23:51 by juancho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	destlen;
	size_t	srclen;
	size_t	i;

	i = 0;
	if (!dst && size == 0)
		return (0);
	destlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (size < destlen || size == 0)
		return (srclen + size);
	while (src[i] && i + destlen < size - 1)
	{
		dst[destlen + i] = src[i];
		i ++;
	}
	dst[destlen + i] = '\0';
	return (destlen + srclen);
}
