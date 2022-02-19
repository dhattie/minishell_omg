//
// Created by user on 12.02.2022.
//

#include "../include/minishell.h"


char	**ft_split_once(char *str, char ch)
{
    int		i;
    char	**new_str;

    if (!str || !ch)
        return (NULL);
    i = 0;
    new_str = (char **)malloc(sizeof(char *) * 3);
    if (!new_str)
        return (NULL);
    while (str[i])
    {
        if (str[i] == ch)
            break ;
        i++;
    }
    new_str[0] = ft_substr(str, 0, i);
    new_str[1] = ft_substr(str, i + 1, ft_strlen(str));
    new_str[2] = NULL;
    return (new_str);
}
