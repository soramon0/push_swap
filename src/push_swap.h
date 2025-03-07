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
# include <stdarg.h>
# include <stdint.h>
# include <stdlib.h>

typedef struct s_ht_node
{
	int					content;
	struct s_ht_node	*next;
}						t_ht_node;

typedef struct s_hash_table
{
	t_ht_node			**keys;
	size_t				size;
}						t_hash_table;

typedef struct s_stack
{
	int					*data;
	size_t				len;
	size_t				cap;
}						t_stack;

typedef struct s_swapable
{
	t_stack				*a;
	t_stack				*b;
	size_t				ops_done;
}						t_swapable;

typedef enum e_stack_op
{
	OP_SA,
	OP_SB,
	OP_SS,
	OP_PA,
	OP_PB,
	OP_RA,
	OP_RB,
	OP_RR,
	OP_RRA,
	OP_RRB,
	OP_RRR,
}						t_stack_op;

typedef ssize_t			t_op_func(t_stack *a, t_stack *b, t_stack_op op);

typedef struct s_op_table
{
	char				*name;
	t_op_func			*method;
}						t_op_table;

typedef struct s_lis
{
	int					max;
	int					max_pos;
	int					*seq_count;
	int					*seq;
	int					seq_size;
}						t_lis;

typedef struct s_move
{
	t_stack_op			op;
	size_t				count;
	struct s_move		*next;
}						t_move;

typedef struct s_move_collection
{
	t_move				**moves;
	size_t				count;
}						t_move_collection;

# ifndef LOG_DEBUG
#  define LOG_DEBUG 0
# endif

t_stack					*stack_init(size_t cap);
void					stack_print(t_stack *s, char *prefix);
ssize_t					stack_push(t_stack *s, int num);
ssize_t					stack_resize(t_stack *s, size_t cap);
ssize_t					stack_find_index(t_stack *s, int num);
ssize_t					stack_is_sorted(t_stack *s);
t_stack					*stack_copy(t_stack *s);
void					stack_free(t_stack *s);
t_op_table				*stack_op_table_init(void);
ssize_t					stack_do_op(t_swapable *area, t_stack_op op);
ssize_t					stack_push_op(t_stack *a, t_stack *b, t_stack_op op);
ssize_t					stack_swap_op(t_stack *a, t_stack *b, t_stack_op op);
ssize_t					stack_rotate_op(t_stack *a, t_stack *b, t_stack_op op);
ssize_t					stack_rrotate_op(t_stack *a, t_stack *b, t_stack_op op);
ssize_t					sort(t_swapable *area);
void					stack_reverse(t_stack *s);
void					err_exit(char *fmt, ...);
void					debug_msg(char *fmt, ...);
void					swap_ints(int *a, int *b);
void					shift_ints(t_stack *s, int dirction);
char					*op_str(t_stack_op op);
t_swapable				*swapable_init(size_t cap);
void					swapable_free(t_swapable *area);
t_swapable				*create_swaparea(char **input);
void					ft_hash_table_insert(t_hash_table *ht, int key);
t_hash_table			*ft_create_hash_table(size_t size);
size_t					ft_hash_table_hash(t_hash_table *ht, int key);
t_ht_node				*ft_ht_newkey(int value);
void					ft_hash_table_free(t_hash_table *ht);
ssize_t					ft_hash_table_exists(t_hash_table *ht, int key);
t_stack					*create_lis_stack(t_stack *src);
void					bubble_sort(t_stack *s);
int						ft_min(int num1, int num2);
t_move_collection		*create_move_coll(size_t moves_count);
void					move_coll_free(t_move_collection *coll,
							t_move **move_skip);
ssize_t					add_move(t_move_collection *coll, t_move **move);
t_move					*create_move(t_stack_op op, size_t count);
void					move_free(t_move *move);
size_t					move_total(t_move *move);
t_move					*get_best_move(t_move_collection *coll);
void					move_apply(t_swapable *area, t_move *move);
t_move					*create_rapa_move(size_t ra_count);
t_move					*create_rbpa_move(size_t rb_count);
t_move					*create_rr_move(size_t rb_count, size_t ra_count);
ssize_t	find_insert_pos(t_stack *pivot, t_stack *haystack, int needle);
#endif
