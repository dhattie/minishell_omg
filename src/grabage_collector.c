//
// Created by user on 12.02.2022.
//

#include "../include/minishell.h"

void	garbage_collector2(t_shell *minishell)
{
    if (minishell->input != NULL)
        free(minishell->input);
    minishell->launch_method = 0;
}

void	garbage_collector(t_shell *minishell)
{
    t_prog	*tmp;
    int		i;

    if (minishell->apps != NULL)
        minishell->apps = minishell->apps->head;
    while (minishell->apps != NULL)
    {
        i = 0;
        while (minishell->apps->argv && minishell->apps->argv[i])
            free(minishell->apps->argv[i++]);
        free(minishell->apps->argv);
        if (minishell->apps->output_file != NULL)
            free(minishell->apps->output_file);
        if (minishell->apps->input_file != NULL)
            free(minishell->apps->input_file);
        if (minishell->apps->heredoc != NULL)
            free(minishell->apps->heredoc);
        if (minishell->apps->token == IS_PIPE && minishell->apps->fd[0] != 0)
            close(minishell->apps->fd[0]);
        tmp = minishell->apps;
        minishell->apps = minishell->apps->next;
        free(tmp);
    }
    garbage_collector2(minishell);
}
