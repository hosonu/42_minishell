#include "../includes/minishell.h"

// typedef struct	s_env
// {
// 	char	*key;
// 	char	*value;
// 	struct s_env	*next;
// }	t_env;

// t_env	*environ_init(void);
// void	destroy_env(t_env *data);
// void	delone_env(t_env **env, t_env *data);
// int	ft_env(t_env *env);
// int	ft_export(char *av[], t_env *env);

int	unset_util(char *key, char *av[])
{
	int	i;

	i = 0;
	while (av[i] != NULL)
	{
		if (ft_strncmp(key, av[i], ft_strlen(key)) == 0)
		{
			if (ft_strncmp(key, av[i], ft_strlen(av[i])) == 0)
				return (1);
		}
		i++;
	}
	return 0;
}

int ft_unset(char *av[], t_env *env)
{
	int	i;
	t_env	*tmp;
	t_env	*head;

	i = 0;
	head = env;
	while (env != NULL)
	{
		if (unset_util(env->key, av) == 1)
		{
			tmp = env;
			env = env->next;
			delone_env(&head, tmp);
		}
		else
			env = env->next;
	}
}
/*
int	main(void)
{
	t_env	*env;
	char	*av1[] = {"TEST=42", "TEST2=52", NULL};
	char	*av2[] = {"TEST", "PS2", NULL};

	env = environ_init();
	ft_export(av1, env);
	ft_env(env);
	ft_unset(av2, env);
	ft_env(env);
}*/
