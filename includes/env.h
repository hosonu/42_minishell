# ifndef ENV_H
# define ENV_H

#include "./minishell.h"

// environ1.c
void	key_cpy(char *dst, char *var);
void	value_cpy(char *dst, char *var);
t_env   *new_env(char *var);
void    destroy_env(t_env *data);
void    delone_env(t_env *env, t_env *data);

// environ2.c
void    addlast_env(t_env *env, t_env *new);
t_env   *environ_init(void);
char    *ft_getenv(t_env *env, char *key);
t_env   *getenv_node(t_env *env, char *key);
char **env_int_str(t_env *env);
int	is_special_char(char c);

//environ3.c
int	key_strlen(char *var);
int	value_strlen(char *var);
int	varname_validate(char *var);
char	**env_split(char *var);

#endif
