/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/11/05 14:07:37 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_move	*create_rapa_move(size_t a_moves)
{
	t_move	*move;

	move = create_move(OP_RA, a_moves);
	if (move == NULL)
		return (NULL);
	move->next = create_move(OP_PA, 1);
	if (move->next == NULL)
		return (free(move), NULL);
	return (move);
}

t_move	*create_rbpa_move(size_t b_moves)
{
	t_move	*move;

	move = create_move(OP_RB, b_moves);
	if (move == NULL)
		return (NULL);
	move->next = create_move(OP_PA, 1);
	if (move->next == NULL)
		return (free(move), NULL);
	return (move);
}

t_move	*create_rrbpa_move(size_t b_moves)
{
	t_move	*move;

	move = create_move(OP_RRB, b_moves);
	if (move == NULL)
		return (NULL);
	move->next = create_move(OP_PA, 1);
	if (move->next == NULL)
		return (free(move), NULL);
	return (move);
}

t_move	*create_rrarbpa_move(size_t b_moves, size_t a_moves)
{
	t_move	*move;

	move = create_move(OP_RRA, a_moves);
	if (move == NULL)
		return (NULL);
	move->next = create_rbpa_move(b_moves);
	if (move->next == NULL)
		return (free(move), NULL);
	return (move);
}
