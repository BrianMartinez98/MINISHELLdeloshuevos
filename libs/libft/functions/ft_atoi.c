/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juancho <juancho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 19:34:36 by juancho           #+#    #+#             */
/*   Updated: 2023/12/14 12:23:51 by juancho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_atoi(const char *str)
{
	long			nb;
	int				sign;
	unsigned int	i;

	nb = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		nb = (nb * 10) + str[i] - '0';
		i++;
	}
	return ((int)(sign * nb));
}

/*
int	main(void)
{
	char	*number;

	number = "+9223372036854775807";

	printf("\nSTRING: %s", number);
	printf("\nft_atoi: %d", ft_atoi(number));
	printf("\natoi: %d", atoi(number));
	printf("\n");
	printf("\n(int)nb: %d\n", (int)(-2147483654));


	return (0);
}

*/
