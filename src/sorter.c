/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/11/05 14:07:37 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

ssize_t	push_unsorted(t_swapable *area)
{
	t_stack	*lis;
	size_t	diff;

	lis = create_lis_stack(area->a);
	stack_print(lis, "LIS");
	if (lis == NULL)
		return (-1);
	diff = area->a->len - lis->len;
	while (diff > 0)
	{
		if (stack_find_index(lis, area->a->data[area->a->len - 1]) == -1)
		{
			stack_do_op(area, OP_PB);
			diff--;
		}
		else
			stack_do_op(area, OP_RA);
	}
	return (stack_free(lis), 0);
}

t_move	*find_best_move(t_stack *pivot, t_swapable *area)
{
	ssize_t				ops;
	size_t				moves_count;
	int					needle;
	t_move				*coll_move;
	t_move_collection	*coll;

	ops = find_insert_pos(pivot, area->a, area->b->data[area->b->len - 1]);
	moves_count = ft_min(area->b->len, ops);
	coll_move = create_rapa_move(ops);
	if (coll_move == NULL)
		return (NULL);
	if (moves_count <= 1)
		return (coll_move);
	coll = create_move_coll(moves_count);
	if (coll == NULL)
		return (move_free(coll_move), NULL);
	if (coll_add_move(coll, &coll_move) != 0)
		return (move_coll_free(coll, NULL), (move_free(coll_move)), NULL);
	while (coll->count < moves_count - (coll->count - 1))
	{
		needle = area->b->data[area->b->len - 1 - coll->count];
		if (save_rr_move(coll, pivot, area->a, needle) != 0)
			return (move_coll_free(coll, NULL), NULL);
	}
	return (get_best_move(coll));
}

ssize_t	push_sorted(t_swapable *area)
{
	t_move	*move;
	t_stack	*pivot;

	while (area->b->len > 0)
	{
		pivot = stack_copy(area->a);
		if (pivot == NULL)
			return (-1);
		move = find_best_move(pivot, area);
		if (move == NULL)
			return (stack_free(pivot), -1);
		move_apply(area, move);
		stack_print(area->a, "A");
		stack_print(area->b, "B");
		move_free(move);
		stack_free(pivot);
	}
	return (0);
}

ssize_t	sort(t_swapable *area)
{
	stack_print(area->a, "A");
	stack_print(area->b, "B");
	if (area->a->len <= 1 || stack_is_sorted(area->a) == 0)
		return (0);
	if (push_unsorted(area) != 0)
		return (-1);
	stack_print(area->a, "A");
	stack_print(area->b, "B");
	if (push_sorted(area) != 0)
		return (-1);
	stack_print(area->a, "A");
	stack_print(area->b, "B");
	debug_msg("Sorted in %d ops\n", area->ops_done);
	return (0);
}
