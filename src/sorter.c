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

int	max(int num1, int num2)
{
	if (num1 > num2)
		return (num1);
	return (num2);
}

int	*init_lis(size_t size)
{
	int		*lis;
	size_t	i;

	if (size == 0)
		return (NULL);
	lis = malloc(sizeof(int) * size);
	if (lis == NULL)
		return (NULL);
	i = 0;
	while (i < size)
		lis[i++] = 1;
	return (lis);
}

ssize_t	lengthOfLIS(int data[], size_t size)
{
	int		*lis;
	ssize_t	len;
	size_t	i;
	size_t	j;
	int		num;

	lis = init_lis(size);
	if (lis == NULL)
		return (-1);
	len = 0;
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < i)
		{
			if (data[i] > data[j])
				lis[i] = max(lis[i], lis[j] + 1);
			j++;
		}
		i++;
	}
	i = 0;
	// len wrong for some reason
	while (i < size)
	{
		num = lis[i];
		len = max(len, num);
		i++;
	}
	free(lis);
	return (len);
}

ssize_t	is_sorted(t_stack *s)
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

void	bubble_sort(t_swapable *area)
{
	ssize_t	i;
	int		is_sorted;

	is_sorted = 0;
	while (!is_sorted)
	{
		is_sorted = 1;
		i = area->a->len - 1;
		while (i >= 1)
		{
			if (area->a->data[i] > area->a->data[i - 1])
			{
				swap_ints(area->a->data + i, area->a->data + (i - 1));
				is_sorted = 0;
			}
			i--;
		}
	}
}

ssize_t	sort(t_swapable *area)
{
	stack_print(area->a);
	stack_print(area->b);
	ft_printf("LIS = %d\n", lengthOfLIS(area->a->data, area->a->len));
	if (area->a->len <= 1 || is_sorted(area->a) == 0)
		return (0);
	bubble_sort(area);
	stack_print(area->a);
	stack_print(area->b);
	return (0);
}
