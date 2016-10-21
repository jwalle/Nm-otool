#include "ft_nm.h"

t_list	*merge(t_list *a, t_list *b)
{
	t_list *result;
	t_list64 *info_a;
	t_list64 *info_b;

	if (!a)
		return (b);
	if (!b)
		return (a);
	info_a = (t_list64*)a->data;
	info_b = (t_list64*)b->data;
	if (ft_strcmp(info_a->name, info_b->name) < 0)
	{
		result = a;
		result->next = merge(a->next, b);
	}
	else
	{
		result = b;
		result->next = merge(a, b->next);
	}
	return (result);
}

void	split(t_list *source, t_list **front, t_list **back)
{
	t_list	*fast;
	t_list	*slow;

	if (!source || !source->next)
	{
		*front = source;
		*back = NULL;
	}
	else
	{
		slow = source;
		fast = source->next;
		while (fast)
		{
			fast = fast->next;
			if (fast)
			{
				slow = slow->next;
				fast = fast->next;
			}
		}
		*front = source;
		*back = slow->next;
		slow->next = NULL;
	}
}

void	merge_sort(t_list **ref)
{
	t_list *head;
	t_list *a;
	t_list *b;

	head = *ref;
	if (!head || !head->next)
		return ;
	split(head, &a, &b);
	merge_sort(&a);
	merge_sort(&b);
	/*if (opt->sort == 't')
		*ref = (opt->r) ? (merge_time_r(a, b)) : (merge_time(a, b));
	else if (opt->sort == 'S')
		*ref = (opt->r) ? (merge_size_r(a, b)) : (merge_size(a, b));
	else if (opt->sort == 'd')
		*ref = (opt->r) ? (merge_r(a, b)) : (merge(a, b));*/
	merge(a, b);
}