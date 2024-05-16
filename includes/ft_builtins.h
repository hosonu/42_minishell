/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-23 16:49:34 by user              #+#    #+#             */
/*   Updated: 2024-04-23 16:49:34 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BUILTINS_H
# define FT_BUILTINS_H

# include "./minishell.h"

//42_echo.c
int		ft_echo(char *argv[]);
int		cnt_option_n(char **argv);
bool	get_option_n(char *argv);

//42cd.c
int		ft_cd(char *av[], t_env *env);
void	cd_change_env(t_env *env);
int		cd_export(t_env *env, char *arg, char *buff);

//42pwd.c
int		ft_pwd(void);

//42export.c
int		ft_export(char *av[], t_env *env);
char	*get_key(char *var);
void	export_display(t_env *env);

//42unset.c
int		ft_unset(char *av[], t_env *env);

//42env.c
int		ft_env(t_env *env);

//42exit.c
void	ft_exit(char *av[], int status, bool is_parent, t_env *env);

#endif
