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

t_move_collection	*create_move_coll(size_t moves_count)
{
	t_move_collection	*coll;

	coll = malloc(sizeof(t_move_collection) * moves_count);
	if (coll == NULL)
		return (NULL);
	coll->count = 0;
	coll->cap = 10;
	coll->moves = malloc(sizeof(t_move *) * coll->cap);
	if (coll->moves == NULL)
		return (NULL);
	return (coll);
}

ssize_t	add_move(t_move_collection *coll, t_move **move)
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

void	move_coll_free(t_move_collection *coll, t_move **move_skip)
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
