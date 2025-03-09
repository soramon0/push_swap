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

ssize_t	stack_swap_op(t_stack *a, t_stack *b, t_stack_op op, int print)
{
	ssize_t	ops;

	ops = 0;
	if (op == OP_SA && a->len >= 2 && ++ops)
	{
		print_op(print, "%s\n", op_str(op));
		swap_ints(a->data + a->len - 1, a->data + a->len - 2);
	}
	if (op == OP_SB && b->len >= 2 && ++ops)
	{
		print_op(print, "%s\n", op_str(op));
		swap_ints(b->data + b->len - 1, b->data + b->len - 2);
	}
	if (op == OP_SS && (a->len >= 2 || b->len >= 2) && ++op)
	{
		print_op(print, "%s\n", op_str(op));
		if (a->len >= 2)
			swap_ints(a->data + a->len - 1, a->data + a->len - 2);
		if (b->len >= 2)
			swap_ints(b->data + b->len - 1, b->data + b->len - 2);
	}
	return (ops);
}

ssize_t	stack_push_op(t_stack *a, t_stack *b, t_stack_op op, int print)
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
		print_op(print, "%s\n", op_str(op));
		src->len--;
	}
	return (ops);
}

ssize_t	stack_rotate_op(t_stack *a, t_stack *b, t_stack_op op, int print)
{
	t_stack	*src;
	ssize_t	ops;

	src = NULL;
	ops = 0;
	if (op == OP_RA && a->len >= 2)
		src = a;
	if (op == OP_RB && b->len >= 2)
		src = b;
	if (src != NULL)
	{
		ops++;
		print_op(print, "%s\n", op_str(op));
		shift_ints(src, 1);
	}
	if (op == OP_RR && (a->len >= 2 || b->len >= 2))
	{
		ops++;
		print_op(print, "%s\n", op_str(op));
		if (a->len >= 2)
			shift_ints(a, 1);
		if (b->len >= 2)
			shift_ints(b, 1);
	}
	return (ops);
}

ssize_t	stack_rrotate_op(t_stack *a, t_stack *b, t_stack_op op, int print)
{
	t_stack	*src;
	ssize_t	ops;

	src = NULL;
	ops = 0;
	if (op == OP_RRA && a->len >= 2)
		src = a;
	if (op == OP_RRB && b->len >= 2)
		src = b;
	if (src != NULL)
	{
		ops++;
		print_op(print, "%s\n", op_str(op));
		shift_ints(src, 0);
	}
	if (op == OP_RRR && (a->len >= 2 || b->len >= 2))
	{
		ops++;
		print_op(print, "%s\n", op_str(op));
		if (a->len >= 2)
			shift_ints(a, 0);
		if (b->len >= 2)
			shift_ints(b, 0);
	}
	return (ops);
}
