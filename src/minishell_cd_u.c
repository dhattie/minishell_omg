//
// Created by user on 12.02.2022.
//

#include "../include/minishell.h"

char	*find_pwd(t_shell *minishell, char *str)
{
    t_envp	*tmp;

    tmp = minishell->environment;
    while (tmp)
    {
        if (!ft_strcmp(str, tmp->key))
            return (tmp->value);
        tmp = tmp->next;
    }
    return (NULL);
}

void	change_old_new_pwd(t_shell *minishell, char *str, char *key)
{
    t_envp	*tmp;

    tmp = minishell->environment;
    while (tmp)
    {
        if (!ft_strcmp(key, tmp->key))
        {
            free(tmp->value);
            tmp->value = ft_strdup(str);
            return ;
        }
        tmp = tmp->next;
    }
}
