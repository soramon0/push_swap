/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/11/05 14:07:37 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

void	move_free(t_move *move)
{
	t_move	*tmp;

	while (move != NULL)
	{
		tmp = move;
		move = move->next;
		free(tmp);
	}
}

t_move	*get_best_move(t_move_collection *coll)
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
	coll_free(coll, &best);
	return (best);
}

void	move_apply(t_swapable *area, t_move *move, int print)
{
	while (move != NULL)
	{
		while (move->count > 0)
		{
			stack_do_op(area, move->op, print);
			move->count--;
		}
		move = move->next;
	}
}
