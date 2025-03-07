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

int	min(int num1, int num2)
{
	if (num1 < num2)
		return (num1);
	return (num2);
}

typedef struct s_move
{
	t_stack_op		op;
	size_t			count;
	struct s_move	*next;
}					t_move;

typedef struct s_move_collection
{
	t_move			**moves;
	size_t			count;
}					t_move_collection;

// coll = new s_move_collection()
// coll[0].op = OP_SB
// coll[0].count = 2
// coll[1].op = OP_PA
// coll[1].count = 1

t_move	*create_move(t_stack_op op, size_t count)
{
	t_move	*move;

	move = malloc(sizeof(t_move));
	if (move == NULL)
		return (NULL);
	move->op = op;
	move->count = count;
	move->next = NULL;
	return (move);
}

ssize_t	add_move(t_move_collection *coll, t_move **move)
{
	t_move	**moves;
	size_t	i;

	moves = malloc(sizeof(t_move *) * coll->count + 1);
	if (moves == NULL)
		return (-1);
	if (coll->moves == NULL)
	{
		moves[0] = *move;
		coll->moves = moves;
	}
	else
	{
		moves = malloc(sizeof(t_move *) * coll->count + 1);
		if (moves == NULL)
			return (-1);
		i = 0;
		while (i < coll->count)
		{
			moves[i] = coll->moves[i];
			i++;
		}
		moves[i] = *move;
		coll->moves = moves;
	}
	coll->count++;
	return (0);
}

size_t	move_total(t_move *move)
{
	size_t	total;

	total = 0;
	while (move != NULL)
	{
		total += move->count;
		move = move->next;
	}
	return (total);
}

t_move	*cal_best_move(t_move_collection *coll)
{
	t_move	*move;
	t_move	*best;
	size_t	i;
	size_t	smallest;
	size_t	total;

	i = 0;
	move = coll->moves[i++];
	best = move;
	smallest = move_total(move);
	while (i < coll->count)
	{
		move = coll->moves[i];
		total = move_total(move);
		if (smallest > total)
		{
			smallest = total;
			best = move;
		}
		i++;
	}
	return (best);
}

t_move	*create_rapa_move(size_t ra_count)
{
	t_move	*move;

	move = create_move(OP_RA, ra_count);
	if (move == NULL)
		return (NULL);
	move->next = create_move(OP_PA, 1);
	if (move->next == NULL)
		return (free(move), NULL);
	return (move);
}
t_move	*create_rbpa_move(size_t rb_count)
{
	t_move	*move;

	move = create_move(OP_RB, rb_count);
	if (move == NULL)
		return (NULL);
	move->next = create_move(OP_PA, 1);
	if (move->next == NULL)
		return (free(move), NULL);
	return (move);
}

t_move	*create_rr_move(size_t rb_count, size_t ra_count)
{
	t_move	*move;
	size_t	reminder;

	reminder = 0;
	if (rb_count > ra_count)
	{
		reminder = rb_count - ra_count;
		move = create_move(OP_RR, ra_count);
	}
	else if (rb_count < ra_count)
	{
		reminder = ra_count - rb_count;
		move = create_move(OP_RR, rb_count);
	}
	else
		move = create_move(OP_RR, ra_count);
	if (move == NULL)
		return (NULL);
	if (rb_count > ra_count)
		move->next = create_rbpa_move(reminder);
	else if (rb_count < ra_count)
		move->next = create_rapa_move(reminder);
	else
		move->next = create_move(OP_PA, 1);
	if (move->next == NULL)
		return (free(move), NULL);
	return (move);
}

t_move	*find_best_move(t_stack *pivot, t_swapable *area)
{
	ssize_t				ops;
	size_t				moves_count;
	int					needle;
	t_move				*coll_move;
	t_move_collection	*coll;

	needle = area->b->data[area->b->len - 1];
	ops = find_insert_order(pivot, area->a, needle);
	moves_count = min(area->b->len, ops);
	coll = malloc(sizeof(t_move_collection) * moves_count);
	if (coll == NULL)
		return (NULL);
	coll->moves = NULL;
	coll->count = 0;
	coll_move = create_rapa_move(ops);
	if (coll_move == NULL)
		return (free(coll_move), NULL);
	add_move(coll, &coll_move);
	if (moves_count <= 1)
		return (free(coll), coll_move);
	while (coll->count < moves_count - (coll->count - 1))
	{
		needle = area->b->data[area->b->len - 1 - coll->count];
		ops = find_insert_order(pivot, area->a, needle);
		if (ops == -1)
			return (free(coll), NULL); // walk linked list array and free
		coll_move = create_rr_move(coll->count, ops);
		if (coll_move == NULL)
			return (free(coll), NULL); // walk linked list array and free
		if (add_move(coll, &coll_move) != 0)
			return (free(coll), NULL);
	}
	return (cal_best_move(coll));
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
		while (move != NULL)
		{
			while (move->count--)
				stack_do_op(area, move->op);
			move = move->next;
		}
		// stack_do_op(area, OP_PA);
		stack_print(area->a, "A");
		stack_print(area->b, "B");
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
