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

	if (rb_count > ra_count)
		move = create_move(OP_RR, ra_count);
	else if (rb_count < ra_count)
		move = create_move(OP_RR, rb_count);
	else
		move = create_move(OP_RR, ra_count);
	if (move == NULL)
		return (NULL);
	if (rb_count > ra_count)
		move->next = create_rbpa_move(rb_count - ra_count);
	else if (rb_count < ra_count)
		move->next = create_rapa_move(ra_count - rb_count);
	else
		move->next = create_move(OP_PA, 1);
	if (move->next == NULL)
		return (move_free(move), NULL);
	return (move);
}
