/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fcntl_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoyuki <hoyuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:44:00 by hoyuki            #+#    #+#             */
/*   Updated: 2024/04/19 14:44:00 by hoyuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_INIT_H
# define HEREDOC_INIT_H

int	set_sigint_flag(int i);
int	get_sigint_flag(void);
void	signal_handler_heredoc(int signum);
int	heredoc_hook(void);
void	heredoc_init(int gfd[2]);

# endif
