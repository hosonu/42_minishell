#include "../includes/minishell.h"


int ft_pwd(char *av[], t_env *env)
{
	while (env != NULL)
	{
		if (ft_strncmp("PWD", env->key, ft_strlen("PWD")) == 0)
		{
			if (ft_strncmp("PWD", env->key, ft_strlen(env->key)) == 0)
				printf("%s\n", env->value);
		}
		env = env->next;
	}
}
/*
int main(int argc, char *argv[])
{
	t_env	*env;

	env = environ_init();
	ft_pwd(argv, env);
}
*/
