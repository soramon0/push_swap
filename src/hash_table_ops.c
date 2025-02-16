/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_ops.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/11/05 14:07:37 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_ht_node	*add_node_first(t_hash_table *ht, int idx, int key)
{
	t_ht_node	*node;

	node = ft_ht_newkey(key);
	if (node == NULL)
		return (NULL);
	idx = ft_hash_table_hash(ht, key);
	if (ht->keys[idx] == NULL)
	{
		ht->keys[idx] = node;
		return (NULL);
	}
	return (node);
}

void	ft_hash_table_insert(t_hash_table *ht, int key)
{
	size_t		idx;
	t_ht_node	*node;
	t_ht_node	*current;
	t_ht_node	*tmp;

	idx = ft_hash_table_hash(ht, key);
	node = add_node_first(ht, idx, key);
	if (node == NULL)
		return ;
	current = ht->keys[idx];
	tmp = ht->keys[idx];
	while (current && current->content < key)
	{
		tmp = current;
		current = current->next;
	}
	if (tmp == ht->keys[idx])
	{
		node->next = ht->keys[idx];
		ht->keys[idx] = node;
		return ;
	}
	node->next = tmp->next;
	tmp->next = node;
}

ssize_t	ft_hash_table_exists(t_hash_table *ht, int key)
{
	t_ht_node	*node;
	size_t		idx;

	idx = ft_hash_table_hash(ht, key);
	if (ht->keys[idx] == NULL)
		return (-1);
	if (ht->keys[idx]->content == key)
		return (0);
	node = ht->keys[idx]->next;
	while (node != NULL)
	{
		if (node->content == key)
			return (0);
		node = node->next;
	}
	return (-1);
}
