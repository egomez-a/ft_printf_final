/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flagsfunctions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 11:36:03 by egomez-a          #+#    #+#             */
/*   Updated: 2021/04/19 12:09:46 by egomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Funciones para ir inicializando flags:
** flagsreset para resetear todos los flags
** El signo '-' para justificar a la izqda (hasleft)
** '0' para rellenar con ceros (haszero)
** '*' como comodín para reemplazar con otros caracteres
** '.' para añadir precision en decimales (hasprecision)
** 'x' para indicar hexadecimal (hashex)
** 'X' para indicar hexadecimal con mayusculas (hasxcaps)
*/

void	ft_flagsreset(t_flags *flags)
{
	flags->haswidth = 0;
	flags->haszero = 0;
	flags->hasprecision = 0;
	flags->hasleft = 0;
	flags->hashex = 0;
	flags->hasxcaps = 0;
	flags->width = 0;
	flags->precision = 0;
	flags->left = 0;
}

static void	ft_cf4(va_list args, const char *str, t_flags *flags, int *pos)
{
	int		num;

	num = 0;
	if (str[*pos] == '*')
	{
		num = va_arg(args, int);
		if (num < 0)
		{
			flags->hasprecision = 0;
			flags->precision = 0;
		}
		else
			flags->precision = num;
		(*pos)++;
	}
	else
	{
		flags->precision = ft_atoi(&str[(*pos)]);
	}
}

static void	ft_cf3(va_list args, const char *str, t_flags *flags, int *pos)
{
	if (ft_isdigit(str[*pos]) == 1)
	{
		flags->haswidth = 1;
		flags->width = ft_atoi(&str[*pos]);
		while (str[*pos] != 'c' && str[*pos] != 's' && str[*pos] != 'p'
			&& str[*pos] != 'd' && str[*pos] != 'i' && str[*pos] != 'u'
			&& str[*pos] != 'x' && str[*pos] != 'X' && str[*pos] != '%'
			&& str[*pos] != '.')
			(*pos)++;
	}
	if (str[*pos] == '.')
	{
		flags->hasprecision = 1;
		(*pos)++;
		ft_cf4(args, str, flags, pos);
		while (str[*pos] != 'c' && str[*pos] != 's' && str[*pos] != 'p'
			&& str[*pos] != 'd' && str[*pos] != 'i' && str[*pos] != 'u'
			&& str[*pos] != 'x' && str[*pos] != 'X' && str[*pos] != '%')
			(*pos)++;
	}
	if (str[*pos] == 'x')
		flags->hashex = 1;
	if (str[*pos] == 'X')
		flags->hasxcaps = 1;
}

static void	ft_cf2(const char *str, t_flags *flags, int *pos)
{
	if (str[(*pos)] == '0')
	{
		flags->haszero = 1;
		(*pos)++;
	}
	if (str[(*pos)] == '-')
	{
		flags->hasleft = 1;
		(*pos)++;
	}
}

void	ft_ckflags(va_list args, const char *str, t_flags *flags, int *pos)
{
	int	num;

	num = 0;
	ft_cf2(str, flags, pos);
	if (str[(*pos)] == '*')
	{
		flags->haswidth = 1;
		num = va_arg(args, int);
		if (num < 0)
		{
			flags->hasleft = 1;
			flags->width = (-1) * num;
		}
		else
			flags->width = num;
		(*pos)++;
	}
	ft_cf3(args, str, flags, pos);
}
