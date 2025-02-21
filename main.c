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

	if (argc < 2)
		return (1);
	area = create_swaparea(++argv);
	if (area == NULL)
		err_exit("Parsing failed\n", 2);
	if (sort(area) != 0)
	{
		swapable_free(area);
		err_exit("Sorting failed\n");
	}
	swapable_free(area);
	return (0);
}
