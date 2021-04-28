/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrtohex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 12:23:03 by egomez-a          #+#    #+#             */
/*   Updated: 2021/04/22 13:23:17 by egomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_revstr(char *str)
{
	int		len;
	char	*temp;
	int		i;

	len = 0;
	i = 0;
	while (str[len] != '\0')
		len++;
	temp = malloc(sizeof(char) * (len + 1));
	while (len > 0)
	{
		temp[i] = str[(len - 1)];
		i++;
		len--;
	}
	temp[i] = '\0';
	return (temp);
}

char	*ft_uitohex(unsigned int decimalnumber)
{
	unsigned int	quotient;
	unsigned int	temp;
	char			*str;
	int				i;
	char			hex[20];

	i = 0;
	quotient = decimalnumber;
	while (i < 20)
		hex[i++] = '\0';
	i = 0;
	while (quotient != 0)
	{
		temp = quotient % 16;
		if (temp < 10)
			temp = temp + 48;
		else
			temp = temp + 87;
		hex[i++] = temp;
		quotient = quotient / 16;
	}
	str = ft_revstr(ft_strdup(hex));
	return (str);
}

char	*ft_ulongtohex(unsigned long decimalnumber)
{
	unsigned long	quotient;
	unsigned long	temp;
	char			*str;
	int				i;
	char			hex[100];

	i = 0;
	quotient = decimalnumber;
	while (i < 100)
		hex[i++] = '\0';
	i = 0;
	while (quotient != 0)
	{
		temp = quotient % 16;
		if (temp < 10)
			temp = temp + 48;
		else
			temp = temp + 87;
		hex[i++] = temp;
		quotient = quotient / 16;
	}
	str = ft_revstr(ft_strdup(hex));
	return (str);
}
