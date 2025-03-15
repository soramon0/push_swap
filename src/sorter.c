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

#include "libft/libft.h"
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

ssize_t	push_top(t_swapable *area)
{
	int			sm;
	size_t		index;
	t_stack_op	op;

	sm = stack_min_max(area->a, 0);
	index = stack_find_index(area->a, sm);
	if (index >= (area->a->len) / 2)
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
			return (-1);
		index--;
	}
	return (0);
}

ssize_t	all_mutation(t_swapable *area)
{
	size_t	index;

	index = stack_find_index(area->a, stack_min_max(area->a, 0));
	if (index == 0 && area->a->data[2] > area->a->data[1])
	{
		if (stack_do_op(area, OP_SA, 1) != 0)
			return (-1);
		if (stack_do_op(area, OP_RRA, 1) != 0)
			return (-1);
		return (0);
	}
	if (index == 1 && area->a->data[0] > area->a->data[1]
		&& area->a->data[1] < area->a->data[2])
	{
		if (stack_do_op(area, OP_RA, 1) != 0)
			return (-1);
		return (0);
	}
	else
	{
		if (stack_do_op(area, OP_SA, 1) != 0)
			return (-1);
		return (0);
	}
	if (index == 2 && area->a->data[1] > area->a->data[0])
	{
		if (stack_do_op(area, OP_RA, 1) != 0)
			return (-1);
		if (stack_do_op(area, OP_SA, 1) != 0)
			return (-1);
		if (stack_do_op(area, OP_RRA, 1) != 0)
			return (-1);
	}
	return (0);
}

t_stack	*best_lis(t_swapable *area)
{
	t_stack	*lis;
	size_t	best;
	size_t	index;
	ssize_t	rotation;

	best = 0;
	index = 0;
	while (index < area->a->len)
	{
		lis = create_lis_stack(area->a);
		if (lis == NULL)
			return (NULL);
		if (lis->len > best)
		{
			rotation = index;
			best = lis->len;
		}
		stack_do_op(area, OP_RA, 0);
		++index;
		stack_free(lis);
	}
	while (index--)
		stack_do_op(area, OP_RRA, 0);
	while (rotation--)
		stack_do_op(area, OP_RA, 1);
	return (create_lis_stack(area->a));
}

ssize_t	push_small_list(t_swapable *area)
{
	t_stack	*lis;

	if (area->a->len == 5)
	{
		stack_do_op(area, OP_PB, 1);
		stack_do_op(area, OP_PB, 1);
	}
	lis = best_lis(area);
	if (lis == NULL)
		return (-1);
	if (lis->len == 3 && area->b->len == 0)
		return (stack_free(lis), 0);
	else
		stack_do_op(area, OP_SA, 1);
	if (area->b->len > 0 && push_sorted(area) != 0)
		return (stack_free(lis), -1);
	if (push_top(area) != 0)
		return (stack_free(lis), -1);
	return (stack_free(lis), 0);
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
