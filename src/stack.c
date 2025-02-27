/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
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
		cap = 8;
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

ssize_t	stack_resize(t_stack *s, size_t cap)
{
	int		*data;
	size_t	i;

	if (s->cap == cap || s->len == cap)
		return (0);
	if (cap < s->len)
		return (-1);
	data = malloc(sizeof(int) * cap);
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
	s->cap = cap;
	return (0);
}

ssize_t	stack_push(t_stack *s, int num)
{
	ssize_t	new_cap;

	if (s->len == s->cap)
	{
		if (s->cap == SIZE_MAX)
			return (-1);
		if (s->cap > SIZE_MAX / 2)
			new_cap = SIZE_MAX;
		else
			new_cap = s->cap * 2;
		if (stack_resize(s, new_cap) != 0)
			return (-1);
	}
	s->data[s->len++] = num;
	return (0);
}

void	stack_print(t_stack *s)
{
	ssize_t	i;

	if (s == NULL)
	{
		debug_msg("stack = NULL\n");
		return ;
	}
	debug_msg("stack(%x) = %d/%d\n", s, s->len, s->cap);
	if (s->len == 0)
	{
		debug_msg("[]\n");
		return ;
	}
	i = (ssize_t)s->len - 1;
	while (i >= 0)
	{
		debug_msg("| %d\t|\n", s->data[i]);
		i--;
	}
}
