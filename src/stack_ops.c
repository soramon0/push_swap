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

void	stack_swap_op(t_stack *a, t_stack *b, t_stack_op op)
{
	if (op == OP_SA && a->len >= 2)
	{
		ft_printf("%s\n", op_str(op));
		swap_ints(a->data + a->len - 1, a->data + a->len - 2);
	}
	if (op == OP_SA && b->len >= 2)
	{
		ft_printf("%s\n", op_str(op));
		swap_ints(b->data + b->len - 1, b->data + b->len - 2);
	}
	if (op == OP_SS && (a->len >= 2 || b->len >= 2))
	{
		ft_printf("%s\n", op_str(op));
		if (a->len >= 2)
			swap_ints(a->data + a->len - 1, a->data + a->len - 2);
		if (b->len >= 2)
			swap_ints(b->data + b->len - 1, b->data + b->len - 2);
	}
}

ssize_t	stack_push_op(t_stack *a, t_stack *b, t_stack_op op)
{
	t_stack	*src;
	t_stack	*dst;

	src = NULL;
	dst = NULL;
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
			return (-1);
		ft_printf("%s\n", op_str(op));
		src->len--;
	}
	return (0);
}

ssize_t	stack_do_op(t_swapable *area, t_stack_op op)
{
	if (op == OP_SA || op == OP_SB || op == OP_SS)
		return (stack_swap_op(area->a, area->b, op), 0);
	if (op == OP_PA || op == OP_PB)
	{
		if (stack_push_op(area->a, area->b, op) != 0)
			return (debug_msg("push_op(%s): failed\n", op_str(op)), -1);
		return (0);
	}
	debug_msg("do_op(%s): invalid OP(%d)\n", op_str(op), op);
	return (-1);
}
