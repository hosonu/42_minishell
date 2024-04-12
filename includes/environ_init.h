#ifndef ENVIRON_INIT_H
# define ENVIRON_INIT_H

t_env	*new_env(char *var);
void	addlast_env(t_env **env, t_env *new);
t_env	*environ_init(void);

#endif
