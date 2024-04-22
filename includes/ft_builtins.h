#ifndef FT_BUILTINS_H
#define FT_BUILTINS_H

#include "./minishell.h"

//42_echo.c
int     ft_echo(int argc, char *argv[]);
int     cnt_option_n(char **argv);
bool    get_option_n(char *argv);

//42cd.c
int	    ft_cd(char *av[], t_env *env);
void	cd_change_env(t_env *env);
char	*format_path(char *av, char buff[PATH_MAX]);

//42pwd.c
int     ft_pwd(char *av[], t_env *env);

//42export.c
int	    ft_export(char *av[], t_env *env);
void	export_display(t_env *env);
void	env_sort_ascii(t_env **env);
void	update_pointers(t_env **env, t_env **prev, t_env **tmp);
void	swap_nodes(t_env **env, t_env *prev, t_env *current, int *sorted);

//42unset.c
int     ft_unset(char *av[], t_env *env);
int	    unset_util(char *key, char *av[]);

//42env.c
int	    ft_env(t_env *env);

//42exit.c
void	ft_exit(char *av[], int status);
int	check_digits(char *str);

#endif
    