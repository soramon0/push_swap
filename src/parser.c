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

// static ssize_t	find_index(t_stack *s, int needle)
// {
// 	size_t	i;
//
// 	if (s->len == 0)
// 		return (-1);
// 	i = 0;
// 	while (i < s->len)
// 	{
// 		if (s->data[i] == needle)
// 			return (i);
// 		i++;
// 	}
// 	return (-1);
// }

static size_t	append_item(int i, t_swapable *area, t_hash_table *map,
		char **nums)
{
	int	num;

	if (ft_isnum(nums[i]) == -1)
	{
		ft_split_free(nums);
		ft_hash_table_free(map);
		swapable_free(area);
		return (-1);
	}
	if (ft_atoi(nums[i], &num) != 0 || ft_hash_table_exists(map, num) == 1)
	{
		ft_split_free(nums);
		ft_hash_table_free(map);
		swapable_free(area);
		return (-1);
	}
	ft_hash_table_insert(map, num);
	area->a->data[area->a->len++] = num;
	return (0);
}

static size_t	ft_split_size(char **nums)
{
	size_t	i;

	i = 0;
	while (nums[i] != NULL)
		i++;
	return (i);
}

t_swapable	*create_swaparea(char *input)
{
	t_swapable		*area;
	char			**nums;
	size_t			i;
	t_hash_table	*map;

	nums = ft_split(input, ' ');
	if (nums == NULL)
		return (NULL);
	i = ft_split_size(nums);
	if (i == 0)
		return (ft_split_free(nums), NULL);
	area = swapable_init(i);
	if (area == NULL)
		return (ft_split_free(nums), NULL);
	map = ft_create_hash_table(i / 2);
	if (map == NULL)
		return (ft_split_free(nums), swapable_free(area), NULL);
	while (i--)
	{
		if (append_item(i, area, map, nums) != 0)
			return (NULL);
	}
	ft_split_free(nums);
	ft_hash_table_free(map);
	return (area);
}
