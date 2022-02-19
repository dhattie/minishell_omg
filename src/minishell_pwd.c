//
// Created by user on 12.02.2022.
//

#include "../include/minishell.h"

int	get_pwd(t_shell *minishell, char **str)
{
    char	*tmp;

    if (!ft_strcmp("pwd", str[0]))
    {
        tmp = getcwd(NULL, 0);
        write(1, tmp, ft_strlen(tmp));
        write(1, "\n", 1);
        free(tmp);
        minishell->child_exit_status = 0;
        return (0);
    }
    return (1);
}

