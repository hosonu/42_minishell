#include "../includes/minishell.h"

// t_env	*new_env(char *var)
// {
// 	t_env	*new;
// 	char	**splited;

// 	new = malloc(sizeof(t_env));
// 	splited = ft_split(var, '=');
// 	new->key = splited[0];
// 	new->value = splited[1];
// 	new->next = NULL;
// 	return new;
// }
// void	addlast_env(t_env **env, t_env *new)
// {
// 	t_env	*node;

// 	node = *env;
// 	if (*env == NULL)
// 		*env = new;
// 	else
// 	{
// 		while (node->next != NULL)
// 			node = node->next;
// 		node->next = new;
// 	}
// }

// t_env	*environ_init(void)
// {
// 	extern char	**environ;
// 	t_env	*env;
// 	t_env	*new;
// 	int	i;

// 	i = 0;
// 	env = NULL;
// 	while (environ[i] != NULL)
// 	{
// 		new = new_env(environ[i]);
// 		addlast_env(&env, new);
// 		i++;
// 	}
// 	return (env);
// }


t_env   *new_env(char *var)
{
        t_env   *new;
        char    **splited;

        if (ft_strchr(var, '=') == NULL)
                return NULL;
        new = malloc(sizeof(t_env));
        splited = ft_split(var, '=');
        new->key = splited[0];
        if (splited[1] != NULL)
                new->value = splited[1];
        else
                new->value = ft_strdup("");
        new->next = NULL;
        return new;
}

void    addlast_env(t_env **env, t_env *new)
{
        t_env   *node;

        node = *env;
        if (*env == NULL)
                *env = new;
        else
        {
                while (node->next != NULL)
                        node = node->next;
                node->next = new;
        }
}

void    destroy_env(t_env *data)
{
        free(data->key);
        free(data->value);
        free(data);
}

void    delone_env(t_env **env, t_env *data)
{
        t_env   *tmp;

        tmp = *env;
        if (*env == data)
                *env = (*env)->next;
        else
        {
                while (tmp != NULL)
                {
                        if (tmp->next == data)
                                tmp->next = data->next;
                        tmp = tmp->next;
                }
        }
        destroy_env(data);
}

t_env   *environ_init(void)
{
        extern char     **environ;
        t_env   *env;
        t_env   *new;
        int     i;

        i = 0;
        env = NULL;
        while (environ[i] != NULL)
        {
                new = new_env(environ[i]);
                addlast_env(&env, new);
                i++;
        }
        return (env);
}

char    *ft_getenv(t_env *env, char *key)
{
        char    *value;

        value = NULL;
        if (key == NULL)
                return NULL;
        while (env != NULL)
        {
                if (ft_strncmp(key, env->key, ft_strlen(key)) == 0)
                {
                        if (ft_strncmp(key, env->key, ft_strlen(env->key)) == 0)
                                value = ft_strdup(env->value);
                }
                env = env->next;
        }
        return value;
}

t_env   *getenv_node(t_env *env, char *key)
{
        while (env != NULL)
        {
                if (ft_strncmp(key, env->key, ft_strlen(key)) == 0)
                {
                        if (ft_strncmp(key, env->key, ft_strlen(env->key)) == 0)
                                return (env);
                }
                env = env->next;
        }
        return (NULL);
}

char **env_int_str(t_env *env)
{
        char **str;
        char *line;

        line = NULL;
         while (env != NULL)
        {
                line = ft_strjoin(line, env->key);
                line = ft_strjoin(line, "=");
                line = ft_strjoin(line, env->value);
                line = ft_strjoin(line, "\n");
                env = env->next;
        }
        str = ft_split(line, '\n');
        return str;
}
