/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juancho <juancho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 12:43:24 by jarregui          #+#    #+#             */
/*   Updated: 2023/12/14 12:23:51 by juancho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		return (c + 32);
	return (c);
}

// esto es de mi función antigua ft_strlowcase. revisar este main --->
//
// int	main(void)
// {
// 	char	*str;

// 	str = (char *)malloc(100);
// 	strcpy(str, "AQU1habiaTEXTOy_db3_salir # TODOen minusculas");
// 	printf("%s\n", str);
// 	ft_strlowcase(str);
// 	printf("%s\n", str);
// 	free(str);
// 	return (0);
// }