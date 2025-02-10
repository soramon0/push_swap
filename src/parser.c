/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/11/05 14:07:37 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	ft_isnum(char *str)
{
	ssize_t	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (-1);
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (-1);
		i++;
	}
	return (1);
}

static ssize_t	find_index(t_stack *s, int needle)
{
	size_t	i;

	if (s->len == 0)
		return (-1);
	i = 0;
	while (i < s->len)
	{
		if (s->data[i] == needle)
			return (i);
		i++;
	}
	return (-1);
}

// (TODO): check overflow
t_swapable	*create_swaparea(char *input)
{
	t_swapable	*area;
	char		**nums;
	int			num;
	size_t		i;

	i = 0;
	nums = ft_split(input, ' ');
	if (nums == NULL)
		return (NULL);
	while (nums[i] != NULL)
		i++;
	if (i == 0)
		return (ft_split_free(nums), NULL);
	area = swapable_init(i);
	if (area == NULL)
		return (ft_split_free(nums), NULL);
	while (i--)
	{
		if (ft_isnum(nums[i]) == -1)
			return (ft_split_free(nums), swapable_free(area), NULL);
		num = ft_atoi(nums[i]);
		if (find_index(area->a, num) != -1)
			return (ft_split_free(nums), swapable_free(area), NULL);
		area->a->data[area->a->len++] = num;
	}
	ft_split_free(nums);
	return (area);
}
