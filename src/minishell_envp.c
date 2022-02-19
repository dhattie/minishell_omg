//
// Created by user on 10.02.2022.
//

#include "../include/minishell.h"

void	get_environment(t_shell *minishell, char **env)
{
    char	**tmp;
    int		i;

    i = 0;
    while (env[i])
    {
        tmp = ft_split(env[i], '=');
        ft_lstadd_back_minishell(&minishell->environment,
                                 ft_lstnew_minishell(tmp[0], tmp[1]));
        i++;
        free(tmp);
    }
}




