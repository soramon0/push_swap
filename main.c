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
	printf("stack_a->len = %zu, stack->cap = %zu\n", area->a->len, area->a->cap);
	printf("stack_b->len = %zu, stack->cap = %zu\n", area->b->len, area->b->cap);
	printf("a[top]   -> %d\n", area->a->data[area->a->len - 1]);
	printf("a[top-1] -> %d\n", area->a->data[area->a->len - 2]);
	stack_swap(area->a, area->b, STACK_A);
	printf("a[top]   -> %d\n", area->a->data[area->a->len - 1]);
	printf("a[top-1] -> %d\n", area->a->data[area->a->len - 2]);
	stack_swap(area->a, area->b, STACK_B);
	printf("b[top]   -> %d\n", area->b->data[area->b->len - 1]);
	printf("b[top-1] -> %d\n", area->b->data[area->b->len - 2]);
	stack_swap(area->a, area->b, STACK_BOTH);
	printf("a[top]   -> %d\n", area->a->data[area->a->len - 1]);
	printf("a[top-1] -> %d\n", area->a->data[area->a->len - 2]);
	printf("b[top]   -> %d\n", area->b->data[area->b->len - 1]);
	printf("b[top-1] -> %d\n", area->b->data[area->b->len - 2]);
	swapable_free(area);
	return (0);
}
