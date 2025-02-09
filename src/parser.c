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

// (TODO): check overflow and duplicates
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

t_swapable	*create_swaparea(char *input)
{
	char		**nums;
	t_swapable	*area;
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
		area->a->data[area->a->len++] = ft_atoi(nums[i]);
	}
	return (area);
}
