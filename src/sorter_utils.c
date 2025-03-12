/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorter_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/11/05 14:07:37 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

ssize_t	find_insert_pos(t_stack *pivot, t_stack *haystack, int needle)
{
	ssize_t	index;
	ssize_t	needle_index;
	int		target;

	if (stack_push(pivot, needle) != 0)
		return (-1);
	bubble_sort(pivot);
	index = stack_find_index(pivot, needle);
	needle_index = index;
	if (index == 0)
		index = pivot->len - 1;
	else
		index--;
	target = pivot->data[index];
	index = stack_find_index(haystack, target);
	if (index == -1)
		return (-1);
	pivot->data[needle_index] = pivot->data[--pivot->len];
	return (haystack->len - 1 - index);
}

ssize_t	find_insert_pos_rev(t_stack *pivot, t_stack *haystack, int needle)
{
	ssize_t	index;
	ssize_t	needle_index;
	int		target;

	if (stack_push(pivot, needle) != 0)
		return (-1);
	bubble_sort_rev(pivot);
	index = stack_find_index(pivot, needle);
	needle_index = index;
	if (index == (ssize_t)pivot->len - 1)
		index = 0;
	else
		index++;
	target = pivot->data[index];
	index = stack_find_index(haystack, target);
	if (index == -1)
		return (-1);
	pivot->data[needle_index] = pivot->data[--pivot->len];
	return (index);
}
