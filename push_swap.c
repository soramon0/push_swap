/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/11/05 14:07:37 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_isnum(char *str)
{
	ssize_t	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	// check overflow
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (-1);
		i++;
	}
	return (1);
}

ssize_t	count_nums(char *input)
{
	char	**nums;
	int		num;
	ssize_t	i;

	i = 0;
	nums = ft_split(input, ' ');
	if (nums == NULL)
		return (-1);
	while (nums[i] != NULL)
	{
		if (ft_isnum(nums[i]) == -1)
			return (-1);
		num = ft_atoi(nums[i]);
		printf("%d\n", num);
		i++;
	}
	return (i);
}

int	main(int argc, char *argv[])
{
	if (argc != 2)
		return (0);
	if (count_nums(argv[1]) == -1)
		ft_putstr_fd("Error\n", 2);
	else
		ft_putstr_fd("Valid\n", 1);
	return (0);
}
