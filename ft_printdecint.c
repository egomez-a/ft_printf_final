/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printdecint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 15:07:09 by egomez-a          #+#    #+#             */
/*   Updated: 2021/04/27 18:03:55 by egomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Include in the temp1 the result of the pointer, after allocating memory
** for it
*/

static void	ft_ptfdec1(t_flags *flags, char **temp, char **str)
{
	if (flags->hasprecision == 1)
	{
		if (flags->precision > ft_strlen(*str))
		{
			flags->d = flags->precision - ft_strlen(*str);
			if ((*str)[0] == '-')
				flags->d++;
		}
		else
			flags->d = 0;
		flags->spaces = ft_calloc(flags->d, sizeof(char));
		ft_memset(flags->spaces, '0', (flags->d));
		flags->spaces[flags->d] = '\0';
		(*temp) = ft_strjoin(flags->spaces, (*str));
		free(flags->spaces);
	}
	else
	{
		(*temp) = ft_calloc(ft_strlen(*str), sizeof(char));
		ft_memcpy((*temp), (*str), ft_strlen(*str));
		(*temp)[ft_strlen(*str)] = '\0';
	}
}

/*
** Take into account width elements, considering where to put spaces
*/

static void	ft_ptfdecwidth2(t_flags *flags, char **temp, char **tempw)
{
	flags->d = flags->width - ft_strlen(*temp);
	flags->spaces = ft_calloc(flags->d, sizeof(char));
	if ((flags->width >= flags->precision) || (flags->haszero == 0))
		ft_memset(flags->spaces, ' ', flags->d);
	else
		ft_memset(flags->spaces, '0', flags->d);
	flags->spaces[(flags->d)] = '\0';
	(*tempw) = ft_strjoin(*(temp), flags->spaces);
}

static void	ft_ptfdecwidth(t_flags *flags, char **temp, char **tempw)
{
	if (flags->hasleft == 0)
	{
		if (flags->width > ft_strlen(*temp))
		{
			flags->d = flags->width - ft_strlen(*temp);
			flags->spaces = ft_calloc(flags->d, sizeof(char));
			if ((flags->haszero == 1) && ((flags->hasprecision == 0)
					|| ((flags->hasprecision == 1)
						&& (flags->precision > flags->width))))
				ft_memset(flags->spaces, '0', flags->d);
			else
				ft_memset(flags->spaces, ' ', flags->d);
			flags->spaces[(flags->d)] = '\0';
			(*tempw) = ft_strjoin(flags->spaces, *(temp));
		}
		else
			(*tempw) = ft_strjoin("", *temp);
	}
	else if (flags->hasleft == 1)
	{
		if (flags->width > ft_strlen(*temp))
			ft_ptfdecwidth2(flags, &(*temp), &(*tempw));
		else
			(*tempw) = ft_strjoin("", *temp);
	}
}

static void	ft_ptfdecnull(t_flags *flags, char **str)
{
	if (flags->d == 0 && flags->hasprecision == 1)
	{
		(*str) = malloc(sizeof(char));
		(*str)[0] = '\0';
	}
	else
		(*str) = ft_itoa(flags->d);
}

void	ft_printdecint(va_list args, t_flags *flags, int *pos)
{
	char	*str;
	char	*temp;
	char	*tempw;

	temp = NULL;
	tempw = NULL;
	flags->d = va_arg(args, int);
	ft_ptfdecnull(flags, &str);
	ft_ptfdec1(flags, &temp, &str);
	ft_moveminus(temp);
	if (flags->haswidth == 1)
		ft_ptfdecwidth(flags, &temp, &tempw);
	else
		(tempw) = ft_strjoin("", (temp));
	if ((flags->haswidth == 1) && (flags->haszero == 1)
		&& (flags->precision == 0))
		ft_moveminus(tempw);
	ft_putstr_fd(tempw, 1);
	(flags->count) += ft_strlen(tempw);
	free(temp);
	free(tempw);
	free(str);
	(*pos)++;
}
