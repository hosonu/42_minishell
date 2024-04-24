/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_func.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosonu <hoyuki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 20:44:14 by hosonu            #+#    #+#             */
/*   Updated: 2024/04/20 20:44:20 by hosonu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef X_FUNC_H
# define X_FUNC_H

# include "./minishell.h"

// x_func.c

pid_t	x_fork(void);
void	*x_malloc(size_t size);
int		x_sstrncmp(const char *s1, const char *s2, size_t len);
void	double_free(char **str);

// x_func_second.c

int		x_execve(const char *filename, char *const argv[], char *const envp[]);
int		x_access(const char *pathname, int mode);
int		x_unlink(const char *pathname);
int		x_open(const char *pathname, int flags, mode_t mode);

// x_func_third.c

int		x_dup(int oldfd);
int		x_dup2(int oldfd, int newfd);
int		x_pipe(int pipefd[2]);
int		x_close(int fd);

#endif
