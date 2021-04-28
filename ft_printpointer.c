/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printpointer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:57:48 by egomez-a          #+#    #+#             */
/*   Updated: 2021/04/27 18:04:27 by egomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** if precision, then include zeros in the string in excess of ftstrlen of the
** lenght of the pointer. if not we just translate this to the pointer temp.
*/

void	ft_ppointer1(t_flags *flags, char **temp, char **str)
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

void	ft_ppointer3(t_flags *flags, char **temp2, char **tempw)
{
	if (flags->width > ft_strlen(*temp2))
	{
		flags->d = flags->width - ft_strlen(*temp2);
		flags->spaces = ft_calloc(flags->d, sizeof(char));
		if ((flags->hasprecision == 0) || ((flags->hasprecision == 1)
				&& (flags->precision < flags->width)))
			ft_memset(flags->spaces, ' ', flags->d);
		else
			ft_memset(flags->spaces, '0', flags->d);
		flags->spaces[(flags->d)] = '\0';
		(*tempw) = ft_strjoin(flags->spaces, *(temp2));
	}
	else
		(*tempw) = ft_strjoin("", *temp2);
}

/*
** Here we check width flags and hasleft. No haszero in pointers
*/

void	ft_ppointer2(t_flags *flags, char **temp2, char **tempw)
{
	if (flags->hasleft == 0)
		ft_ppointer3(flags, temp2, tempw);
	else if (flags->hasleft == 1)
	{
		if (flags->width > ft_strlen(*temp2))
		{
			flags->d = flags->width - ft_strlen(*temp2);
			flags->spaces = ft_calloc(flags->d, sizeof(char));
			if ((flags->width > flags->precision))
				ft_memset(flags->spaces, ' ', flags->d);
			else
				ft_memset(flags->spaces, '0', flags->d);
			flags->spaces[(flags->d)] = '\0';
			(*tempw) = ft_strjoin(*(temp2), flags->spaces);
		}
		else
			(*tempw) = ft_strjoin("", *temp2);
	}
}

void	ft_ppointerchecknull(unsigned long ul, t_flags *flags, char **str)
{
	if (ul == 0)
	{
		if (flags->hasprecision == 1)
			*str = ft_calloc(sizeof(char), 1);
		else
		{
			*str = ft_calloc(sizeof(char), 2);
			*str[0] = '0';
		}
	}
	else
		*str = ft_ulongtohex(ul);
}

/*
** First we take the unsigned int pointer. We check if is 0, because
** then we need to return a 0. If not we transform it into
** an hexadecimal string. Then we include it in a variable temp
** Then we add the '0x' string and then we check width, zero
** and left flags
*/

void	ft_printpointer(va_list args, t_flags *flags, int *pos)
{
	char			*str;
	unsigned long	ul;
	char			*temp1;
	char			*temp2;
	char			*tempw;

	str = NULL;
	temp1 = NULL;
	temp2 = NULL;
	tempw = NULL;
	ul = va_arg(args, unsigned long);
	ft_ppointerchecknull(ul, flags, &str);
	ft_ppointer1(flags, &temp1, &str);
	temp2 = ft_strjoin("0x", temp1);
	if (flags->haswidth == 1)
		ft_ppointer2(flags, &temp2, &tempw);
	else
		tempw = ft_strjoin("", (temp2));
	(*pos)++;
	ft_putstr_fd(tempw, 1);
	(flags->count) += ft_strlen(tempw);
	free(temp1);
	free(temp2);
	free(tempw);
	free(str);
}
