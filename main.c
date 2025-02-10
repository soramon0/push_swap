/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/11/05 14:07:37 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/push_swap.h"

int	main(int argc, char *argv[])
{
	t_swapable	*area;

	if (argc != 2)
		return (0);
	area = create_swaparea(argv[1]);
	if (area == NULL)
	{
		ft_putstr_fd("Error\n", 2);
		return (0);
	}
	printf("we have a list of %zu random numbers\n", area->a->len);
	swapable_free(area);
	return (0);
}
