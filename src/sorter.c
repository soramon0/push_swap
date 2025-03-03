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

void	bubble_sort(t_stack *s)
{
	ssize_t	i;
	int		is_sorted;

	is_sorted = 0;
	while (!is_sorted)
	{
		is_sorted = 1;
		i = s->len - 1;
		while (i >= 1)
		{
			if (s->data[i] > s->data[i - 1])
			{
				swap_ints(s->data + i, s->data + (i - 1));
				is_sorted = 0;
			}
			i--;
		}
	}
}

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

ssize_t	find_insert_order(t_stack *pivot, t_stack *haystack, int needle)
{
	ssize_t	i;
	size_t	index;
	int		target;

	if (stack_push(pivot, needle) != 0)
		return (-1);
	bubble_sort(pivot);
	index = stack_find_index(pivot, needle);
	if (index == 0)
		index = pivot->len - 1;
	else
		index--;
	target = pivot->data[index];
	i = haystack->len - 1;
	while (i >= 0)
	{
		if (haystack->data[i] == target)
		{
			index = i;
			break ;
		}
		i--;
	}
	return (haystack->len - 1 - index);
}

int	min(int num1, int num2)
{
	if (num1 < num2)
		return (num1);
	return (num2);
}

// typedef struct s_move
// {
// 	t_stack_op ops[512];
// 	size_t count;
// } t_move;

// ssize_t create_move(t_stack *moves, size_t count, ssize_t ops)
// {
// 	t_move *m;
// 	if (ops == -1)
// 		return (-1);
// 	m = malloc(sizeof(t_move));
// 	if (m == NULL)
// 		return (-1);
// 	m->ops = 0;
// 	if (stack_push(moves, ops + moves->len) != 0)
// 		return (stack_free(moves), -1);
// 	return (ops);
// }

ssize_t	cal_best_move(t_stack *moves, size_t count)
{
	ssize_t	best_move;

	(void)count;
	best_move = moves->data[0];
	stack_free(moves);
	return (best_move);
}

ssize_t	find_best_move(t_stack *pivot, t_swapable *area)
{
	ssize_t	ops;
	t_stack	*moves;
	size_t	moves_count;
	int needle;

	ops = find_insert_order(pivot, area->a, area->b->data[area->b->len - 1]);
	moves_count = min(area->b->len, ops);
	if (moves_count <= 1)
		return (ops);
	moves = stack_init(moves_count);
	if (moves == NULL)
		return (-1);
	if (stack_push(moves, ops) != 0)
		return (stack_free(moves), -1);
	while (moves->len < moves_count - moves->len)
	{
		needle = area->b->data[area->b->len - 1 - moves->len];
		ops = find_insert_order(pivot, area->a, needle);
		if (ops == -1)
			return (stack_free(moves), -1);
		if (stack_push(moves, ops + moves->len) != 0)
			return (stack_free(moves), -1);
	}
	return (cal_best_move(moves, moves_count));
}

ssize_t	push_sorted(t_swapable *area)
{
	ssize_t	ops;
	t_stack	*pivot;

	pivot = stack_copy(area->a);
	if (pivot == NULL)
		return (-1);
	while (area->b->len > 0)
	{
		ops = find_best_move(pivot, area);
		if (ops == -1)
			return (stack_free(pivot), -1);
		while (ops > 0)
		{
			stack_do_op(area, OP_RA);
			ops--;
		}
		stack_do_op(area, OP_PA);
		stack_print(area->a, "A");
		stack_print(area->b, "B");
	}
	return (stack_free(pivot), 0);
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
