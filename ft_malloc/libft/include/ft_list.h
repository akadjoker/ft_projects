
#define FREE 1
#define DONTFREE 0

typedef struct s_node
{
	void *data;
	struct s_node *prev;
	struct s_node *next;
} node;

node *ft_lst_back(node *lst);
void ft_lst_clear(node *lst);
void ft_lst_del(node *lst, node *nd);
void ft_lst_delhard(node *lst, node *nd);
int ft_lst_empty(node *lst);
void ft_lst_free(node *lst);
node *ft_lst_front(node *lst);
node *ft_lst_init(void);
void ft_lst_iter(node *lst, void (*f)(void *));
node *ft_lst_min(node *lst, int (*cmp)(void *, void *));
node *ft_lst_new(void *data);
void ft_lst_pushback(node *lst, node *n);
void ft_lst_pushfront(node *lst, node *n);
void ft_lst_rev(node *lst);
int ft_lst_size(node *lst);
node *ft_lst_sort(node *lst, int (*cmp)(void *, void *));