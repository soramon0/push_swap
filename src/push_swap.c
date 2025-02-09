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

int	main(int argc, char *argv[])
{
	t_swapable	*area;
	size_t		i;

	if (argc != 2)
		return (0);
	area = create_swaparea(argv[1]);
	if (area == NULL)
	{
		ft_putstr_fd("Error\n", 2);
		return (0);
	}
	i = 0;
	while (i < area->a->len)
	{
		printf("%d\n", area->a->data[i++]);
	}
	return (0);
}
