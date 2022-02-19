//
// Created by user on 12.02.2022.
//

#include "../include/minishell.h"


void	check_shlvl(t_shell *minishell)
{
    t_envp	*tmp;
    int		shlvl;

    tmp = minishell->environment;
    while (1)
    {
        if (!tmp)
        {
            ft_lstadd_back_minishell(&minishell->environment,
            ft_lstnew_minishell(ft_strdup("SHLVL"), ft_strdup("1")));
            break ;
        }
        else if (!(ft_strcmp(tmp->key, "SHLVL")))
        {
            shlvl = ft_atoi(tmp->value);
            if (tmp->value != NULL)
                free(tmp->value);
            if (shlvl < 0)
                tmp->value = ft_strdup("0");
            else
                tmp->value = ft_itoa(shlvl + 1);
            break ;
        }
        tmp = tmp->next;
    }
}
