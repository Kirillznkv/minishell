#include "../includes/minishell.h"

int	ft_counter_lstenv(t_env *lst)
{
	t_env	*ptr;
	int		size;

	size = 0;
	ptr = lst;
	while (ptr)
	{
		ptr = ptr->next;
		size++;
	}
	return (size);
}

t_env	*new_elem_env(void)
{
	t_env	*new_elem;

	new_elem = (t_env *)malloc(sizeof(t_env));
	if (!new_elem)
		exit(1);
	new_elem->content = (t_content *)malloc(sizeof(t_content));
	if (!new_elem->content)
		exit(1);
	new_elem->next = NULL;
	new_elem->content->value = NULL;
	new_elem->content->key = NULL;
	return (new_elem);
}

void	add_elem_env(t_env *env, t_env *new_env,
				void (*wrt)(t_env *, char *), char *s)
{
	t_env	*ptr;

	wrt(new_env, s);
	ptr = env;
	if (env == NULL)
		env = new_env;
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new_env;
	}
}

t_env	*delete_head(t_env *root)
{
	t_env		*temp;

	temp = root->next;
	free_t_env(root);
	return (temp);
}

t_env	*delet_elem(t_env *lst, t_env *root)
{
	t_env	*temp;

	temp = root;
	while (temp->next != lst)
		temp = temp->next;
	temp->next = lst->next;
	free_t_env(lst);
	return (temp);
}
