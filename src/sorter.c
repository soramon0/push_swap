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

t_move	*find_best_move(t_stack *pivot, t_swapable *area)
{
	ssize_t				ops;
	size_t				moves_count;
	size_t				count;
	int					needle;
	t_move_collection	*coll;

	ops = find_insert_pos(pivot, area->a, area->b->data[area->b->len - 1]);
	moves_count = ft_min(area->b->len, ops);
	if (moves_count == 0)
		return (create_move(OP_PA, 1));
	coll = coll_init(moves_count);
	if (coll == NULL)
		return (NULL);
	count = 0;
	while (count < moves_count - count)
	{
		needle = area->b->data[area->b->len - 1 - count];
		if (coll_save_up(coll, pivot, area->a, needle) != 0)
			return (coll_free(coll, NULL), NULL);
		needle = area->b->data[count];
		if (coll_save_down(coll, pivot, area->a, needle) != 0)
			return (coll_free(coll, NULL), NULL);
		count++;
	}
	return (get_best_move(coll));
}

ssize_t	push_sorted(t_swapable *area)
{
	t_move	*move;
	t_stack	*pivot;

	pivot = stack_copy(area->a);
	if (pivot == NULL)
		return (-1);
	while (area->b->len > 0)
	{
		move = find_best_move(pivot, area);
		if (move == NULL)
			return (stack_free(pivot), -1);
		move_apply(area, move, 1);
		move_free(move);
		if (stack_push(pivot, area->a->data[area->a->len - 1]) != 0)
			return (stack_free(pivot), -1);
	}
	stack_free(pivot);
	return (0);
}

ssize_t	best_out_of_three(t_swapable *area)
{
	t_stack	*lis;

	lis = get_best_lis(area);
	if (lis == NULL)
		return (-1);
	if (lis->len == 3)
		return (stack_free(lis), 0);
	else
		stack_do_op(area, OP_SA, 1);
	if (push_top(area) != 0)
		return (stack_free(lis), -1);
	return (stack_free(lis), 0);
}

ssize_t	push_small_list(t_swapable *area)
{
	if (area->a->len == 5)
		stack_do_op(area, OP_PB, 1);
	if (area->a->len == 4)
		stack_do_op(area, OP_PB, 1);
	if (best_out_of_three(area) != 0)
		return (-1);
	if (area->b->len == 0)
		return (0);
	if (push_sorted(area) != 0)
		return (-1);
	if (push_top(area) != 0)
		return (-1);
	area->c = stack_copy(area->a);
	if (area->c == NULL)
		return (-1);
	bubble_sort(area->c);
	debug_msg("Stack is sorted = %d\n", stack_equal(area->a, area->c));
	return (0);
}

ssize_t	sort(t_swapable *area)
{
	if (area->a->len <= 1 || stack_is_sorted(area->a) == 0)
		return (0);
	if (area->a->len <= 5)
		return (push_small_list(area));
	if (push_unsorted_chunks(area) != 0)
		return (-1);
	if (push_sorted(area) != 0)
		return (-1);
	if (push_top(area) != 0)
		return (-1);
	area->c = stack_copy(area->a);
	if (area->c == NULL)
		return (-1);
	bubble_sort(area->c);
	debug_msg("Sorted in %d ops\n", area->ops_done);
	debug_msg("Stack is sorted = %d\n", stack_equal(area->a, area->c));
	return (0);
}
