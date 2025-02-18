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

static void	swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	stack_swap_op(t_stack *a, t_stack *b, t_stack_op op)
{
	if (op == OP_SA && a->len >= 2)
	{
		ft_putstr_fd("sa\n", 1);
		swap(a->data + a->len - 1, a->data + a->len - 2);
	}
	if (op == OP_SA && b->len >= 2)
	{
		ft_putstr_fd("sb\n", 1);
		swap(b->data + b->len - 1, b->data + b->len - 2);
	}
	if (op == OP_SS && (a->len >= 2 || b->len >= 2))
	{
		ft_putstr_fd("ss\n", 1);
		if (a->len >= 2)
			swap(a->data + a->len - 1, a->data + a->len - 2);
		if (b->len >= 2)
			swap(b->data + b->len - 1, b->data + b->len - 2);
	}
}
