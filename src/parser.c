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

#include "libft/libft.h"
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
	return (0);
}

static size_t	append_items(t_swapable *area, t_hash_table *map, char **nums)
{
	int		num;
	size_t	i;

	i = 0;
	if (nums[0] == NULL)
		return (-1);
	while (nums[i] != NULL)
	{
		if (ft_isnum(nums[i]) == -1)
			return (-1);
		if (ft_atoi(nums[i], &num) != 0)
			return (-1);
		if (ft_hash_table_exists(map, num) == 0)
			return (-1);
		if (stack_push(area->a, num) != 0)
			return (-1);
		ft_hash_table_insert(map, num);
		i++;
	}
	return (0);
}

t_swapable	*create_swaparea(char **input)
{
	t_swapable		*area;
	char			**nums;
	t_hash_table	*map;

	map = ft_create_hash_table(507);
	if (map == NULL)
		return (NULL);
	area = swapable_init(64);
	if (area == NULL)
		return (ft_hash_table_free(map), NULL);
	while (*input)
	{
		nums = ft_split(*input, ' ');
		if (nums == NULL)
			return (ft_hash_table_free(map), swapable_free(area), NULL);
		if (append_items(area, map, nums) != 0)
			return (ft_split_free(nums), ft_hash_table_free(map),
				swapable_free(area), NULL);
		ft_split_free(nums);
		input++;
	}
	ft_hash_table_free(map);
	return (area);
}
