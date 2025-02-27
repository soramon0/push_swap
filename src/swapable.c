/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swapable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/11/05 14:07:37 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swapable_free(t_swapable *area)
{
	if (area != NULL)
	{
		stack_free(area->a);
		stack_free(area->b);
		area->a = NULL;
		area->b = NULL;
		free(area);
	}
}

t_swapable	*swapable_init(size_t cap)
{
	t_swapable	*area;

	area = malloc(sizeof(t_swapable));
	if (area == NULL)
		return (NULL);
	area->a = stack_init(cap);
	if (area->a == NULL)
		return (swapable_free(area), NULL);
	area->b = stack_init(cap);
	if (area->b == NULL)
		return (swapable_free(area), NULL);
	area->ops_done = 0;
	return (area);
}

void	stack_reverse(t_stack *s)
{
	size_t	start;
	size_t	end;

	start = 0;
	end = s->len - 1;
	while (start < end)
		swap_ints(s->data + start++, s->data + end--);
}
