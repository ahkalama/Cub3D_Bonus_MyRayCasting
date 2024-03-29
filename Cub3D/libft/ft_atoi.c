/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahkalama <@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 13:56:35 by ahkalama          #+#    #+#             */
/*   Updated: 2024/02/10 13:56:36 by ahkalama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	size_t			i;
	unsigned int	res;
	int				sign;
	size_t			sign_nbr;

	i = 0;
	res = 0;
	sign = 1;
	sign_nbr = 0;
	while ((str[i] == 32 || (str[i] >= 9 && str[i] <= 14)))
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		sign_nbr++;
		i++;
	}
	if (sign_nbr > 1)
		return (0);
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
		res = res * 10 + (str[i++] - 48);
	if (sign_nbr == 1 && sign == -1)
		return (-res);
	return (res);
}
