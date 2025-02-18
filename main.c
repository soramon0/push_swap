/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/11/05 14:07:37 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/push_swap.h"

int	main(int argc, char *argv[])
{
	t_swapable	*area;

	if (argc < 2)
		return (1);
	area = create_swaparea(++argv);
	if (area == NULL)
	{
		ft_putstr_fd("Error\n", 2);
		return (1);
	}
	printf("stack_a->len = %zu, stack->cap = %zu\n", area->a->len,
		area->a->cap);
	printf("stack_b->len = %zu, stack->cap = %zu\n", area->b->len,
		area->b->cap);
	stack_push_op(area->a, area->b, OP_PB);
	stack_push_op(area->a, area->b, OP_PB);
	stack_push_op(area->a, area->b, OP_PA);
	swapable_free(area);
	return (0);
}
