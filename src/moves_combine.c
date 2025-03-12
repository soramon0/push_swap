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

t_move	*create_rrapa_move(size_t b_moves)
{
	t_move	*move;

	move = create_move(OP_RRA, b_moves);
	if (move == NULL)
		return (NULL);
	move->next = create_move(OP_PA, 1);
	if (move->next == NULL)
		return (free(move), NULL);
	return (move);
}

t_move	*create_rr_move(size_t b_moves, size_t a_moves)
{
	t_move	*move;

	if (b_moves > a_moves)
		move = create_move(OP_RR, a_moves);
	else if (b_moves < a_moves)
		move = create_move(OP_RR, b_moves);
	else
		move = create_move(OP_RR, a_moves);
	if (move == NULL)
		return (NULL);
	if (b_moves > a_moves)
		move->next = create_rbpa_move(b_moves - a_moves);
	else if (b_moves < a_moves)
		move->next = create_rapa_move(a_moves - b_moves);
	else
		move->next = create_move(OP_PA, 1);
	if (move->next == NULL)
		return (move_free(move), NULL);
	return (move);
}

t_move	*create_rrarrbpa_move(size_t a_moves, size_t b_moves)
{
	t_move	*move;

	if (b_moves > a_moves)
		move = create_move(OP_RRR, a_moves);
	else if (b_moves < a_moves)
		move = create_move(OP_RRR, b_moves);
	else
		move = create_move(OP_RRR, b_moves);
	if (move == NULL)
		return (NULL);
	if (b_moves > a_moves)
		move->next = create_rrbpa_move(b_moves - a_moves);
	else if (b_moves < a_moves)
		move->next = create_rrapa_move(a_moves - b_moves);
	else
		move->next = create_move(OP_PA, 1);
	if (move->next == NULL)
		return (free(move), NULL);
	return (move);
}
