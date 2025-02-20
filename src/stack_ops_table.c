/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_ops_table.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/11/05 14:07:37 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_op_table	*stack_op_table_init(void)
{
	static t_op_table	table[11];

	table[OP_SA] = (t_op_table){"swap_op", &stack_swap_op};
	table[OP_SB] = (t_op_table){"swap_op", &stack_swap_op};
	table[OP_SS] = (t_op_table){"swap_op", &stack_swap_op};
	table[OP_PA] = (t_op_table){"push_op", &stack_push_op};
	table[OP_PB] = (t_op_table){"push_op", &stack_push_op};
	table[OP_RA] = (t_op_table){"rotate_op", &stack_rotate_op};
	table[OP_RB] = (t_op_table){"rotate_op", &stack_rotate_op};
	table[OP_RR] = (t_op_table){"rotate_op", &stack_rotate_op};
	table[OP_RRA] = (t_op_table){"rrotate_op", NULL};
	table[OP_RRB] = (t_op_table){"rrotate_op", NULL};
	table[OP_RRR] = (t_op_table){"rrotate_op", NULL};
	return (table);
}

ssize_t	stack_do_op(t_swapable *area, t_stack_op op)
{
	t_op_table	*table;

	if (op < OP_SA || op > OP_RRR)
	{
		debug_msg("do_op(%s): out of range OP(%d)\n", op_str(op), op);
		return (-1);
	}
	table = stack_op_table_init();
	if (table[op].method == NULL)
	{
		debug_msg("%s(%s): not implemented \n", table[op].name, op_str(op));
		return (-1);
	}
	if (table[op].method(area->a, area->b, op) != 0)
	{
		debug_msg("%s(%s): failed\n", table[op].name, op_str(op));
		return (-1);
	}
	return (0);
}
