/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/11/05 14:07:37 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	err_exit(char *fmt, ...)
{
	va_list	args;

	if (LOG_DEBUG == 1 && fmt != NULL)
	{
		va_start(args, fmt);
		ft_vprintf(args, fmt);
		va_end(args);
	}
	ft_putstr_fd("Error\n", 2);
	exit(1);
}

void	debug_msg(char *fmt, ...)
{
	va_list	args;

	if (LOG_DEBUG == 1 && fmt != NULL)
	{
		va_start(args, fmt);
		ft_vprintf(args, fmt);
		va_end(args);
	}
}

void	swap_ints(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	shift_ints(t_stack *s, int dirction)
{
	size_t	start;

	if (dirction == 1)
		start = s->len - 1;
	else
		start = 0;
	while (start >= 1 && dirction == 1)
	{
		swap_ints(s->data + (start - 1), s->data + start);
		start--;
	}
	while (start < s->len - 1 && dirction != 1)
	{
		swap_ints(s->data + (start + 1), s->data + start);
		start++;
	}
}
