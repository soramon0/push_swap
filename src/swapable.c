/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swapable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/11/05 14:07:37 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*stack_init(size_t cap)
{
	t_stack	*s;

	s = (t_stack *)malloc(sizeof(t_stack));
	if (s == NULL)
		return (NULL);
	if (cap == 0)
		cap = 1;
	s->cap = cap;
	s->len = 0;
	s->data = ft_calloc(1, sizeof(int) * cap);
	if (s->data == NULL)
		return (NULL);
	return (s);
}

void	stack_free(t_stack *s)
{
	if (s != NULL)
	{
		if (s->data != NULL)
		{
			free(s->data);
			s->data = NULL;
		}
		free(s);
	}
}

ssize_t	stack_push(t_stack *s, int num)
{
	int		*data;
	size_t	i;
	size_t	new_cap;

	if (s->len == s->cap)
	{
		if (s->cap > SIZE_MAX / 2)
			return (-1);
		new_cap = s->cap * 2;
		data = malloc(sizeof(int) * new_cap);
		if (data == NULL)
			return (-1);
		i = 0;
		while (i < s->len)
		{
			data[i] = s->data[i];
			i++;
		}
		free(s->data);
		s->data = data;
		s->cap = new_cap;
	}
	s->data[s->len++] = num;
	return (0);
}

void	swapable_free(t_swapable *area)
{
	if (area != NULL)
	{
		stack_free(area->a);
		stack_free(area->b);
		area->a = NULL;
		area->b = NULL;
		free(area);
	}
}

t_swapable	*swapable_init(size_t cap)
{
	t_swapable	*area;

	area = malloc(sizeof(t_swapable));
	if (area == NULL)
		return (NULL);
	area->a = stack_init(cap);
	if (area->a == NULL)
		return (swapable_free(area), NULL);
	area->b = stack_init(cap);
	if (area->b == NULL)
		return (swapable_free(area), NULL);
	return (area);
}
