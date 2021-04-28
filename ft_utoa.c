/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 13:23:21 by egomez-a          #+#    #+#             */
/*   Updated: 2021/04/22 13:53:21 by egomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_utoacheck(long lnbr)
{
	size_t	lenght;

	if (lnbr > 0)
		lenght = 0;
	else
	{
		lenght = 1;
		lnbr = (-1) * lnbr;
	}
	while (lnbr > 0)
	{
		lenght++;
		lnbr /= 10;
	}
	return (lenght);
}

char 	*ft_utoastr(long lnbr, size_t len)
{
	char	*str;

	if (lnbr != 0)
	{
		str = (char *)malloc(sizeof(str) * (len + 1));
		return (str);
	}
	else
	{
		str = ft_strdup("0");
		return (str);
	}
	if (!(str))
		return (0);
}

char	*ft_utoa(unsigned int u)
{
	long	lnbr;
	int		len;
	char	*s;
	int		isneg;

	lnbr = u;
	isneg = 0;
	len = ft_utoacheck(lnbr);
	s = ft_utoastr(lnbr, len);
	if (lnbr < 0)
	{
		lnbr = -1 * lnbr;
		isneg = 1;
	}
	s[len] = '\0';
	while (--len)
	{
		s[len] = (lnbr % 10) + '0';
		lnbr /= 10;
	}
	if (isneg == 1)
		s[0] = '-';
	else
		s[0] = (lnbr % 10) + '0';
	return (s);
}
