/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/11/05 14:07:37 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_ht_node	*ft_ht_newkey(int value)
{
	t_ht_node	*lst;

	lst = (t_ht_node *)malloc(sizeof(t_ht_node));
	if (lst == NULL)
		return (NULL);
	lst->content = value;
	lst->next = NULL;
	return (lst);
}

t_hash_table	*ft_create_hash_table(size_t keys_count)
{
	t_hash_table	*ht;
	size_t			i;

	if (keys_count == 0)
		return (NULL);
	ht = malloc(sizeof(t_hash_table));
	if (ht == NULL)
		return (NULL);
	if (keys_count < 2)
		keys_count = 2;
	ht->size = keys_count;
	ht->keys = ft_calloc(keys_count, sizeof(t_list));
	if (ht->keys == NULL)
		return (NULL);
	i = 0;
	while (i < keys_count)
		ht->keys[i++] = NULL;
	return (ht);
}

size_t	ft_hash_table_hash(t_hash_table *ht, int key)
{
	return (key % ht->size);
}

void	ft_hash_table_free(t_hash_table *ht)
{
	size_t		i;
	t_ht_node	*node;
	t_ht_node	*tmp;

	i = 0;
	while (i < ht->size)
	{
		node = ht->keys[i];
		while (node != NULL)
		{
			tmp = node->next;
			free(node);
			node = tmp;
		}
		i++;
	}
	free(ht->keys);
	free(ht);
}
