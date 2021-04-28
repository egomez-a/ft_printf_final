/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:42:27 by egomez-a          #+#    #+#             */
/*   Updated: 2021/04/19 15:45:06 by egomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putspace(size_t i, t_flags *flags)
{
	while (i < flags->width - 1)
	{
		ft_putchar_fd(' ', 1);
		i++;
		flags->count++;
	}
}

void	ft_printchar(va_list args, t_flags *flags, int *pos)
{
	size_t	i;
	char	c;

	i = 0;
	c = va_arg(args, int);
	if ((flags->haswidth == 1) && (flags->hasleft == 0))
		ft_putspace(i, flags);
	ft_putchar_fd(c, 1);
	flags->count++;
	if ((flags->haswidth == 1) && (flags->hasleft == 1))
		ft_putspace(i, flags);
	(*pos)++;
}

void	ft_putcharfdflags(char c, int fd, int *pos, t_flags *flags)
{
	write(fd, &c, 1);
	(*pos)++;
	flags->count++;
}

char	*ft_strtoupper(char *str)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		str[i] = ft_toupper(str[i]);
		i++;
	}
	return (str);
}
