// char   *remove_quote(char *token)
// {
//     int i;
//     int look_at_behind;
//     int quoted;
//     int dblquoted;
    
//     i = 0;
//     look_at_behind = 0;
//     quoted = 0;
//     dblquoted = 0;
//     while(token[i] != '\0')
//     {
//         if(is_quote(token[i - look_at_behind]) == 2 && dblquoted == 0)
//         {     
//             token[i - look_at_behind] = '\0';       
//             token = ft_strjoin(token, token + i + 1 - look_at_behind);
//             look_at_behind = 1;
//             quoted = 1;
//         }
//         else if(is_quote(token[i - look_at_behind]) == 1 && quoted == 0)
//         {     
//             token[i - look_at_behind] = '\0';       
//             token = ft_strjoin(token, token + i + 1 - look_at_behind);
//             look_at_behind = 1;
//             dblquoted = 1;
//         }
//         else if(token[i + 1] == '\0' && is_quote(token[i]) > 0 
//         && (quoted == 1 || dblquoted == 1))
//         {
//             token[i] = '\0';       
//             token = ft_strjoin(token, token + i);
//         }
//         i++;
//     }
//     return token;
// }