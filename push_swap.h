/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/11/05 14:07:37 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>

typedef struct s_stack
{
	int		*data;
	size_t	len;
	size_t	cap;
}			t_stack;

typedef struct s_swapable
{
	t_stack	*a;
	t_stack	*b;
}			t_swapable;

t_stack		*stack_init(size_t cap);
void		stack_free(t_stack *s);
t_swapable	*swapable_init(size_t cap);
void		swapable_free(t_swapable *area);
t_swapable	*create_swaparea(char *input);

#endif
