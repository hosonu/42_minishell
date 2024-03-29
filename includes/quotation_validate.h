#ifndef QUOTATION_VALIDATE_H
# define QUOTATION_VALIDATE_H

#include "./minishell.h"

void	quotation_validate(char *str);
void	validate_quote_nesting_util(t_quotes *list, t_quotes quotes);
void	validate_quote_nesting(t_quotes *list1, t_quotes *list2);
void	print_quote(t_quotes *list);
int	count_chr(char *str, char c);
t_quotes	*quote_list(char *str, char quote);

#endif
