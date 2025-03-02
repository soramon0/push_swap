/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/11/05 14:07:37 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

ssize_t	stack_find_index(t_stack *s, int num)
{
	size_t	i;
	ssize_t	index;

	i = 0;
	index = -1;
	while (i < s->len)
	{
		if (s->data[i] == num)
		{
			index = i;
			break ;
		}
		i++;
	}
	return (index);
}

ssize_t	stack_is_sorted(t_stack *s)
{
	size_t	start;

	start = s->len - 1;
	while (start >= 1)
	{
		if (s->data[start] > s->data[start - 1])
			return (-1);
		start--;
	}
	return (0);
}

t_stack	*stack_copy(t_stack *s)
{
	size_t	i;
	t_stack	*new;

	new = stack_init(s->cap);
	if (new == NULL)
		return (NULL);
	i = 0;
	while (i < s->len)
		new->data[new->len++] = s->data[i++];
	return (new);
}
