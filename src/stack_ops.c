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

void	stack_swap(t_stack *a, t_stack *b, t_stack_target target)
{
	int		tmp;
	t_stack	*src;

	if ((target == STACK_A && a->len < 2) || (target == STACK_B && b->len < 2))
		return ;
	if (target == STACK_A || target == STACK_BOTH)
	{
		ft_putstr_fd("sa\n", 1);
		src = a;
	}
	else
	{
		ft_putstr_fd("sb\n", 1);
		src = b;
	}
	tmp = src->data[src->len - 1];
	src->data[src->len - 1] = src->data[src->len - 2];
	src->data[src->len - 2] = tmp;
	if (target == STACK_BOTH)
		stack_swap(a, b, STACK_B);
}
