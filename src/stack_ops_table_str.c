/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_ops_table_str.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/11/05 14:07:37 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "push_swap.h"

t_stack_op	str_to_op_r(const char *str, size_t len)
{
	if (ft_strncmp(str, "ra", len) == 0)
		return (5);
	if (ft_strncmp(str, "rb", len) == 0)
		return (6);
	if (ft_strncmp(str, "rr", len) == 0)
		return (7);
	if (ft_strncmp(str, "rra", len) == 0)
		return (8);
	if (ft_strncmp(str, "rrb", len) == 0)
		return (9);
	if (ft_strncmp(str, "rrr", len) == 0)
		return (10);
	return (OP_UNKNOWN);
}

t_stack_op	str_to_op(const char *str)
{
	size_t	len;

	if (!str)
		return (OP_UNKNOWN);
	len = ft_strlen(str);
	if (len > 1)
		len--;
	if (ft_strncmp(str, "sa", len) == 0)
		return (0);
	if (ft_strncmp(str, "sb", len) == 0)
		return (1);
	if (ft_strncmp(str, "ss", len) == 0)
		return (2);
	if (ft_strncmp(str, "pa", len) == 0)
		return (3);
	if (ft_strncmp(str, "pb", len) == 0)
		return (4);
	return (str_to_op_r(str, len));
}

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
