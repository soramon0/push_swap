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

ssize_t	stack_swap_op(t_stack *a, t_stack *b, t_stack_op op)
{
	ssize_t	ops;

	ops = 0;
	if (op == OP_SA && a->len >= 2 && ++ops)
	{
		ft_printf("%s\n", op_str(op));
		swap_ints(a->data + a->len - 1, a->data + a->len - 2);
	}
	if (op == OP_SB && b->len >= 2 && ++ops)
	{
		ft_printf("%s\n", op_str(op));
		swap_ints(b->data + b->len - 1, b->data + b->len - 2);
	}
	if (op == OP_SS && (a->len >= 2 || b->len >= 2) && ++op)
	{
		ft_printf("%s\n", op_str(op));
		if (a->len >= 2)
			swap_ints(a->data + a->len - 1, a->data + a->len - 2);
		if (b->len >= 2)
			swap_ints(b->data + b->len - 1, b->data + b->len - 2);
	}
	return (ops);
}

ssize_t	stack_push_op(t_stack *a, t_stack *b, t_stack_op op)
{
	t_stack	*src;
	t_stack	*dst;
	ssize_t	ops;

	ops = 0;
	src = NULL;
	dst = NULL;
	if (op == OP_PA && b->len >= 1 && ++ops)
	{
		src = b;
		dst = a;
	}
	if (op == OP_PB && a->len >= 1 && ++ops)
	{
		src = a;
		dst = b;
	}
	if (src != NULL && dst != NULL)
	{
		if (stack_push(dst, src->data[src->len - 1]) != 0)
			return (-1);
		ft_printf("%s\n", op_str(op));
		src->len--;
	}
	return (ops);
}

ssize_t	stack_rotate_op(t_stack *a, t_stack *b, t_stack_op op)
{
	int		direction;
	t_stack	*src;
	ssize_t	ops;

	src = NULL;
	direction = 1;
	ops = 0;
	if ((op == OP_RA || op == OP_RRA) && a->len >= 2)
		src = a;
	if ((op == OP_RB || op == OP_RRB) && b->len >= 2)
		src = b;
	if (op == OP_RRA || op == OP_RRB || op == OP_RRR)
		direction = 0;
	if (src != NULL && ++ops)
	{
		ft_printf("%s\n", op_str(op));
		shift_ints(src, direction);
	}
	if ((op == OP_RR || op == OP_RRR) && (a->len >= 2 || b->len >= 2) && ++ops)
	{
		ft_printf("%s\n", op_str(op));
		if (a->len >= 2)
			shift_ints(a, direction);
		if (b->len >= 2)
			shift_ints(b, direction);
	}
	return (ops);
}
