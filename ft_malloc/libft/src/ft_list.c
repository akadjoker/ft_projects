/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosa-do <lrosa-do@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 15:50:01 by lrosa-do           #+#    #+#             */
/*   Updated: 2021/08/03 18:29:50 by lrosa-do          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_list.h"

node	*ft_lst_init (void)
{
	node	*nil;

	if (!(nil = malloc(sizeof(node))))
		return (NULL);
	nil->data = NULL;
	nil->prev = nil;
	nil->next = nil;
	return (nil);
}

void	ft_lst_free (node *lst)
{
	ft_lst_clear(lst);
	free(lst);
}

int ft_lst_empty (node *lst)
{
	return (lst->next == lst);
}



int	ft_lst_size (node *lst)
{
	node	*current;
	int		count;

	current = lst->next;
	count = 0;
	while (current != lst)
	{
		current = current->next;
		count++;
	}
	return (count);
}

node	*ft_lst_min (node *lst, int (*cmp)(void *, void *))
{
	node	*current;
	node	*min;

	current = lst->next;
	min = current;
	while (current != lst)
	{
		if (cmp(min->data, current->data) > 0)
			min = current;
		current = current->next;
	}
	return (min);
}


void	ft_lst_clear (node *lst)
{
	node	*current;
	node	*next;

	if (!lst)
		return ;
	current = lst->next;
	while (current != lst)
	{
		next = current->next;
		if (current->data)
			free(current->data);
		free(current);
		current = next;
	}
}

node	*ft_lst_back (node *lst)
{
	return (lst->prev);
}

void	ft_lst_del (node *lst, node *nd)
{
	if (!lst || !nd)
		return ;
	nd->prev->next = nd->next;
	nd->next->prev = nd->prev;
	free(nd);
}


node	*ft_lst_front (node *lst)
{
	return (lst->next);
}

void	ft_lst_iter (node *lst, void (*f)(void *))
{
	node	*current;

	if (!lst || !f)
		return ;
	current = lst->next;
	while (current != lst)
	{
		f(current->data);
		current = current->next;
	}
}

node	*ft_lst_new (void *data)
{
	node	*new;

	if (!(new = malloc(sizeof(node))))
		return (NULL);
	new->data = data;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}


void	ft_lst_pushback (node *lst, node *new)
{
	if (!lst || !new)
		return ;
	new->prev = lst->prev;
	new->next = lst;
	lst->prev->next = new;
	lst->prev = new;
}

void	ft_lst_pushfront (node *lst, node *new)
{
	if (!lst || !new)
		return ;
	new->prev = lst;
	new->next = lst->next;
	lst->next->prev = new;
	lst->next = new;
}

void	ft_lst_rev (node *lst)
{
	node	*current;
	node	*tmp;

	current = lst->next;
	while (current != lst)
	{
		tmp = current->next;
		current->next = current->prev;
		current->prev = tmp;
		current = current->prev;
	}
	tmp = lst->next;
	lst->next = lst->prev;
	lst->prev = tmp;
}

node	*ft_lst_sort (node *lst, int (*cmp)(void *, void *))
{
	node	*sorted;
	node	*oldnd;
	node	*newnd;

	sorted = ft_lst_init();
	while (ft_lst_size(lst) > 0)
	{
		oldnd = ft_lst_min(lst, cmp);
		newnd = ft_lst_new(oldnd->data);
		ft_lst_pushback(sorted, newnd);
		ft_lst_del(lst, oldnd);
	}
	ft_lst_del(lst, lst);
	return (sorted);
}
