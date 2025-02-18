/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_ops.c                                        :+:      :+:    :+:   */
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

static char	*op_str(t_stack_op op)
{
	static char	*str;

	str = NULL;
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
	if (op == 5)
		str = "ra";
	if (op == 6)
		str = "rb";
	if (op == 7)
		str = "rr";
	return (str);
}

static void	swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	stack_swap_op(t_stack *a, t_stack *b, t_stack_op op)
{
	if (op != OP_SA && op != OP_SB && op != OP_SS)
		err_exit("swap_op: invalid OP(%s)\n", op_str(op));
	if (op == OP_SA && a->len >= 2)
	{
		ft_printf("%s\n", op_str(op));
		swap(a->data + a->len - 1, a->data + a->len - 2);
	}
	if (op == OP_SA && b->len >= 2)
	{
		ft_printf("%s\n", op_str(op));
		swap(b->data + b->len - 1, b->data + b->len - 2);
	}
	if (op == OP_SS && (a->len >= 2 || b->len >= 2))
	{
		ft_printf("%s\n", op_str(op));
		if (a->len >= 2)
			swap(a->data + a->len - 1, a->data + a->len - 2);
		if (b->len >= 2)
			swap(b->data + b->len - 1, b->data + b->len - 2);
	}
}

void	stack_push_op(t_stack *a, t_stack *b, t_stack_op op)
{
	t_stack	*src;
	t_stack	*dst;

	src = NULL;
	dst = NULL;
	if (op != OP_PA && op != OP_PB)
		err_exit("push_op: invalid OP(%s)\n", op_str(op));
	if (op == OP_PA && b->len >= 1)
	{
		src = b;
		dst = a;
	}
	if (op == OP_PB && a->len >= 1)
	{
		src = a;
		dst = b;
	}
	if (src != NULL && dst != NULL)
	{
		if (stack_push(dst, src->data[src->len - 1]) != 0)
			err_exit("push_op: failed to push to stack using OP(%s)\n",
				op_str(op));
		ft_printf("%s\n", op_str(op));
		src->len--;
	}
}
