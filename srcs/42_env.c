#include "../includes/minishell.h"


int	ft_env(t_env *env)
{
	while (env != NULL)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}
/*
int	main(void)
{
	t_env	*env;

	env = environ_init();
	ft_env(env);
}
*/
