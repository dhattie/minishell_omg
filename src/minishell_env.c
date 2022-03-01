//
// Created by user on 12.02.2022.
//

#include "../include/minishell.h"

void	get_environment(t_shell *minishell, char **env)
{
    char	**tmp;
    int		i;

	tmp = NULL;
    i = -1;
    while (env[++i])
    {
        tmp = ft_split(env[i], '=');
        ft_lstadd_back_minishell(&minishell->environment,
        ft_lstnew_minishell(tmp[0], tmp[1]));
        //i++;
        free(tmp);
		tmp = NULL;
    }
}

int	get_env(t_shell *minishell, char **str)
{
    t_envp	*env_tmp;

    if (!ft_strcmp("env", str[0]))
    {
        env_tmp = minishell->environment;
        while (env_tmp != NULL)
        {
            write(1, env_tmp->key, ft_strlen(env_tmp->key));
            write(1, "=", 1);
            write(1, env_tmp->value, ft_strlen(env_tmp->value));
            write(1, "\n", 1);
            env_tmp = env_tmp->next;
        }
        minishell->child_exit_status = 0;
        return (0);
    }
    return (1);
}

char	*ft_getenv_value(t_envp *lst, char *key)
{
    t_envp	*tmp;

    tmp = lst;
    while (tmp)
    {
        if (!ft_strcmp(key, tmp->key))
            return (tmp->value);
        tmp = tmp->next;
    }
    return ("");
}
