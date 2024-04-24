/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-23 16:44:39 by user              #+#    #+#             */
/*   Updated: 2024-04-23 16:44:39 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MSG_H
# define ERROR_MSG_H

void	error_msg_for_cmd(const char *filename);
void	err_msg_for_exit(char *str);
void	error_and_exit(const char *filename, int exit_code, bool is_tilda);
// void	error_and_exit(const char *filename, int exit_code);

#endif
