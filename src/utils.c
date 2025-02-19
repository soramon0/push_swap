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

char	*op_r_str(t_stack_op op, char *str)
{
	if (op == 5)
		str = "ra";
	if (op == 6)
		str = "rb";
	if (op == 7)
		str = "rr";
	if (op == 8)
		str = "rra";
	if (op == 9)
		str = "rrb";
	if (op == 10)
		str = "rrr";
	return (str);
}

char	*op_str(t_stack_op op)
{
	static char	*str;

	str = "unknown";
	if (op == 0)
		str = "sa";
	if (op == 1)
		str = "sb";
	if (op == 2)
		str = "ss";
	if (op == 3)
		str = "pa";
	if (op == 4)
		str = "pb";
	return (op_r_str(op, str));
}
