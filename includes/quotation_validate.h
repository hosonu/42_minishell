/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotation_validate.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:58:59 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/02 15:50:16 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTATION_VALIDATE_H
# define QUOTATION_VALIDATE_H

#include "./minishell.h"

int	quotation_validate(char *str);
int	validate_quote_nesting_util(t_quotes *list, t_quotes quotes);
int	validate_quote_nesting(t_quotes *list1, t_quotes *list2);
int	count_chr(char *str, char c);
t_quotes	*quote_list(char *str, char quote);

#endif
