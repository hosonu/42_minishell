#include "../../includes/minishell.h"

void	export_display(t_env *env)
{
	while (env != NULL)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

int	ft_export(char *av[], t_env *env)
{
	int	i;
	t_env	*new;

	i = 0;
	if (av[0] == NULL)
		export_display(env);
	while (av[i] != NULL)
	{
		if (ft_strchr(av[i], '=') == NULL)
		{
			i++;
			continue ;
		}
		if (ft_strchr(av[i], ' ') == NULL)
			;
		else if (ft_strchr(av[i], '=') > ft_strchr(av[i], ' '))
		{
			printf("export: not valid identifier");
			i++;
			continue ;
		}
		new = new_env(av[i]);
		addlast_env(&env, new);
		i++;
	}
}
