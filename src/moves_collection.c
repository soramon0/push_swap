/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_collection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/11/05 14:07:37 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_move_collection	*coll_init(size_t moves_count)
{
	t_move_collection	*coll;

	coll = malloc(sizeof(t_move_collection) * moves_count);
	if (coll == NULL)
		return (NULL);
	coll->count = 0;
	coll->cap = 10;
	coll->up_offset = 0;
	coll->down_offset = 0;
	coll->moves = malloc(sizeof(t_move *) * coll->cap);
	if (coll->moves == NULL)
		return (NULL);
	return (coll);
}

ssize_t	coll_add(t_move_collection *coll, t_move **move)
{
	t_move	**moves;
	size_t	i;

	if (coll->count < coll->cap)
		coll->moves[coll->count] = *move;
	else
	{
		coll->cap += 10;
		moves = malloc(sizeof(t_move *) * coll->cap);
		if (moves == NULL)
			return (-1);
		i = 0;
		while (i < coll->count)
		{
			moves[i] = coll->moves[i];
			i++;
		}
		moves[i] = *move;
		free(coll->moves);
		coll->moves = moves;
	}
	coll->count++;
	return (0);
}

ssize_t	coll_save_up(t_move_collection *coll, t_stack *pivot, t_stack *haystack,
		int needle)
{
	int		ops;
	t_move	*coll_move;

	ops = find_insert_pos(pivot, haystack, needle);
	if (ops == -1)
		return (-1);
	if ((size_t)ops <= haystack->len / 2)
		coll_move = create_rr_move(coll->up_offset, ops);
	else
		coll_move = create_rrarbpa_move(coll->up_offset, haystack->len - ops);
	if (coll_move == NULL)
		return (-1);
	if (coll_add(coll, &coll_move) != 0)
		return ((move_free(coll_move)), -1);
	coll->up_offset++;
	return (0);
}

ssize_t	coll_save_down(t_move_collection *coll, t_stack *pivot,
		t_stack *haystack, int needle)
{
	int		ops;
	t_move	*coll_move;

	ops = find_insert_pos_rev(pivot, haystack, needle);
	if (ops == -1)
		return (-1);
	if ((size_t)ops <= haystack->len / 2)
		coll_move = create_rrarrbpa_move(ops, coll->down_offset + 1);
	else
	{
		coll_move = create_move(OP_RA, haystack->len - ops);
		if (coll_move == NULL)
			return (-1);
		coll_move->next = create_rrbpa_move(coll->down_offset + 1);
		if (coll_move->next == NULL)
			return (-1);
	}
	if (coll_move == NULL)
		return (-1);
	if (coll_add(coll, &coll_move) != 0)
		return ((move_free(coll_move)), -1);
	coll->down_offset++;
	return (0);
}

void	coll_free(t_move_collection *coll, t_move **move_skip)
{
	size_t	i;

	if (coll == NULL)
		return ;
	i = 0;
	while (i < coll->count)
	{
		if (move_skip != NULL && *move_skip != NULL)
		{
			if (*move_skip == coll->moves[i])
			{
				i++;
				continue ;
			}
		}
		move_free(coll->moves[i++]);
	}
	free(coll->moves);
	free(coll);
}
