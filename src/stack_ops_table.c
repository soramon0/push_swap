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

char	*op_r_str(t_stack_op op, char *str)
{
	if (op == 5)
		str = "ra";
	if (op == 6)
		str = "rb";
	if (op == 7)
		str = "rr";
	if (op == 8)
		str = "rra";
	if (op == 9)
		str = "rrb";
	if (op == 10)
		str = "rrr";
	return (str);
}

char	*op_str(t_stack_op op)
{
	static char	*str;

	str = "unknown";
	if (op == 0)
		str = "sa";
	if (op == 1)
		str = "sb";
	if (op == 2)
		str = "ss";
	if (op == 3)
		str = "pa";
	if (op == 4)
		str = "pb";
	return (op_r_str(op, str));
}

void	print_op(int print, char *fmt, ...)
{
	va_list	args;

	if (print && fmt != NULL)
	{
		va_start(args, fmt);
		ft_vprintf(args, fmt);
		va_end(args);
	}
}

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
	table[OP_RRA] = (t_op_table){"rrotate_op", &stack_rrotate_op};
	table[OP_RRB] = (t_op_table){"rrotate_op", &stack_rrotate_op};
	table[OP_RRR] = (t_op_table){"rrotate_op", &stack_rrotate_op};
	return (table);
}

ssize_t	stack_do_op(t_swapable *area, t_stack_op op, int print)
{
	t_op_table	*table;
	ssize_t		ops_done;

	ops_done = area->ops_done;
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
	ops_done = table[op].method(area->a, area->b, op, print);
	if (ops_done == -1)
	{
		debug_msg("%s(%s): failed\n", table[op].name, op_str(op));
		return (-1);
	}
	area->ops_done += ops_done;
	return (0);
}
