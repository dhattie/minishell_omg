
//
// Created by user on 12.02.2022.
//

#include "../include/minishell.h"


t_prog	*new_application(void)
{
    t_prog	*tmp;

    tmp = (t_prog *)malloc(sizeof(t_prog));
    tmp->argc = 0;
    tmp->argv = NULL;
    tmp->is_argv = 0;
    tmp->token = 0;
    tmp->output_file = NULL;
    tmp->input_file = NULL;
    tmp->heredoc = NULL;
    tmp->do_not_launch = 0;
    tmp->head = tmp;
    tmp->next = NULL;
    return (tmp);
}

void	add_application(t_shell *minishell)
{
	t_prog	*head;

	if (minishell->apps == NULL)
		minishell->apps = new_application();
	else
	{
		head = minishell->apps->head;
		minishell->apps->next = new_application();
		minishell->apps = minishell->apps->next;
		minishell->apps->head = head;
	}

//    t_prog	*head;
//    t_prog	*new_app;
//
//    if (minishell->apps == NULL)
//        minishell->apps = new_application();
//    else
//    {
//        head = minishell->apps->head;
//        new_app = new_application();
//        minishell->apps->next = new_app;
//        minishell->apps = minishell->apps->next;
//        minishell->apps->head = head;
//    }
}
