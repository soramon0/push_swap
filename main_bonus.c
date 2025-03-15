/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/11/05 14:07:37 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/libft/libft.h"
#include "src/push_swap.h"

ssize_t	process_move(t_swapable *area, char *data)
{
	ssize_t		bytes;
	t_stack_op	op;
	t_move		*move;
	t_move		*head_move;

	move = NULL;
	while (1)
	{
		op = str_to_op(data);
		if (op == OP_UNKNOWN)
			return (swapable_free(area), free(data), err_exit(NULL), -1);
		if (move == NULL)
		{
			move = create_move(op, 1);
			head_move = move;
		}
		else
		{
			move->next = create_move(op, 1);
			move = move->next;
		}
		if (move == NULL)
			return (swapable_free(area), free(data), move_free(head_move),
				err_exit(NULL), -1);
		free(data);
		bytes = get_next_line(0, &data);
		if (bytes == -1)
			return (swapable_free(area), move_free(head_move), err_exit(NULL),
				-1);
		if (bytes == 0)
			break ;
	}
	move_apply(area, head_move, 0);
	move_free(head_move);
	return (0);
}

ssize_t	process(t_swapable *area)
{
	char	*data;
	ssize_t	bytes;

	data = NULL;
	bytes = get_next_line(0, &data);
	if (bytes == -1)
		return (swapable_free(area), err_exit(NULL), -1);
	if (bytes == 0)
	{
		if (stack_is_sorted(area->a) != 0)
			return (-1);
		return (0);
	}
	if (process_move(area, data) != 0)
		return (-1);
	if (stack_is_sorted(area->a) != 0)
	{
		ft_printf("GOT HERE\n");
		return (-1);
	}
	if (area->b->len != 0)
		return (-1);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_swapable	*area;

	if (argc < 2)
		return (1);
	area = create_swaparea(++argv);
	if (area == NULL)
		err_exit("Parsing failed\n", 2);
	if (process(area) != 0)
	{
		swapable_free(area);
		ft_putstr_fd("KO\n", 2);
		return (-1);
	}
	ft_printf("OK\n");
	swapable_free(area);
	return (0);
}
