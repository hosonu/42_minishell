/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-23 16:57:28 by user              #+#    #+#             */
/*   Updated: 2024-04-23 16:57:28 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_UTILS_H
# define STRING_UTILS_H

int	is_quoted(char *str, char *pnt);
int	is_metachar(char c);
int	is_quote(char c);
int	is_more_than_word(char *str);
int	is_space(char c);

#endif
