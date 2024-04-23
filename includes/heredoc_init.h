/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_init.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosonu <hoyuki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 20:48:54 by hosonu            #+#    #+#             */
/*   Updated: 2024/04/23 20:52:01 by hosonu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_INIT_H
# define HEREDOC_INIT_H

int		set_sigint_flag(int i);
int		get_sigint_flag(void);
void	signal_handler_heredoc(int signum);
int		heredoc_hook(void);
void	heredoc_init(int gfd[2]);

#endif
