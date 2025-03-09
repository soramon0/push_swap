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
			stack_do_op(area, OP_PB, 1);
			diff--;
		}
		else if (stack_find_index(lis, area->a->data[0]) == -1)
		{
			stack_do_op(area, OP_RRA, 1);
			stack_do_op(area, OP_PB, 1);
			diff--;
		}
		else
			stack_do_op(area, OP_RA, 1);
	}
	return (stack_free(lis), 0);
}

t_move	*find_best_move(t_stack *pivot, t_swapable *area)
{
	ssize_t				ops;
	size_t				moves_count;
	int					needle;
	t_move_collection	*coll;

	ops = find_insert_pos(pivot, area->a, area->b->data[area->b->len - 1]);
	moves_count = ft_min(area->b->len, ops);
	if (moves_count == 0)
		return (create_move(OP_PA, 1));
	coll = coll_init(moves_count);
	if (coll == NULL)
		return (NULL);
	while (coll->count < moves_count - coll->count)
	{
		needle = area->b->data[area->b->len - 1 - coll->count];
		if (coll_save(coll, pivot, area->a, needle) != 0)
			return (coll_free(coll, NULL), NULL);
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
		move_apply(area, move, 1);
		stack_print(area->a, "A");
		stack_print(area->b, "B");
		move_free(move);
		stack_free(pivot);
	}
	return (0);
}

ssize_t	push_top(t_swapable *area)
{
	int			sm;
	size_t		index;
	t_stack_op	op;

	sm = stack_min_max(area->a, 0);
	index = stack_find_index(area->a, sm);
	if (index > (area->a->len) / 2)
	{
		index = area->a->len - 1 - index;
		op = OP_RA;
	}
	else
	{
		++index;
		op = OP_RRA;
	}
	while (index > 0)
	{
		if (stack_do_op(area, op, 1) != 0)
			return (0);
		index--;
	}
	return (0);
}

ssize_t	sort(t_swapable *area)
{
	stack_print(area->a, "A");
	stack_print(area->b, "B");
	if (area->a->len <= 1 || stack_is_sorted(area->a) == 0)
		return (0);
	area->c = stack_copy(area->a);
	if (area->c == NULL)
		return (-1);
	bubble_sort(area->c);
	if (push_unsorted(area) != 0)
		return (-1);
	stack_print(area->a, "A");
	stack_print(area->b, "B");
	if (push_sorted(area) != 0)
		return (-1);
	if (push_top(area) != 0)
		return (0);
	stack_print(area->a, "A");
	debug_msg("Sorted in %d ops\n", area->ops_done);
	debug_msg("Stack is sorted = %d\n", stack_equal(area->a, area->c));
	return (0);
}
