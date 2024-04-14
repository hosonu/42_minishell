# ifndef ENV_H
# define ENV_H

#include "./minishell.h"

t_env   *environ_init(void);
int     ft_env(t_env *env);
void    addlast_env(t_env **env, t_env *new);
t_env   *new_env(char *var);
void    destroy_env(t_env *data);
void    delone_env(t_env **env, t_env *data);
char    *ft_getenv(t_env *env, char *key);
t_env   *getenv_node(t_env *env, char *key);
char    **env_int_str(t_env *env);

#endif
