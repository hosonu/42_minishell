#ifndef TOKEN_SPLIT_H
# define TOKEN_SPLIT_H

char	**token_split(char *s);
int	count_words(char *s);
void	free_split_all(char **strs, int i);

#endif
