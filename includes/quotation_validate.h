/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotation_validate.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoyuki <hoyuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:58:59 by kojwatan          #+#    #+#             */
/*   Updated: 2024/05/09 14:59:45 by hoyuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTATION_VALIDATE_H
# define QUOTATION_VALIDATE_H

# include "./minishell.h"

int		quotation_validate(char *prompt, t_status *status);
int		validate_quote_nesting_util(t_quotes *list, t_quotes quotes);
int		validate_quote_nesting(t_quotes *list1, t_quotes *list2);
int		count_chr(char *str, char c);

#endif
