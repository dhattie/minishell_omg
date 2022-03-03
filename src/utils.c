//
// Created by user on 13.02.2022.
//

#include "../include/minishell.h"

int	ft_lstsize(t_envp *lst)
{
    unsigned int	i;

    i = 0;
    while (lst)
    {
        lst = lst->next;
        i++;
    }
    return (i);
}

void	check_list(t_envp *list)
{
    t_envp	*tmp_lst;

    tmp_lst = list;
    while (tmp_lst)
    {
        write(1, "declare -x ", 11);
        write(1, tmp_lst->key, ft_strlen(tmp_lst->key));
        write(1, "=\"", 2);
        write(1, tmp_lst->value, ft_strlen(tmp_lst->value));
        write(1, "\"\n", 2);
        tmp_lst = tmp_lst->next;
    }
}

char	**get_arr_env(t_envp *env)
{
    t_envp	*tmp_env;
    char	**arr;
    char	*tmp;
    int		i;

    tmp_env = env;
    i = ft_lstsize(tmp_env);
    arr = (char **)malloc(sizeof(char *) * (i + 1));
    i = 0;
    while (tmp_env)
    {
        tmp = ft_strjoin(tmp_env->key, "=");
        arr[i] = ft_strjoin(tmp, tmp_env->value);
        free(tmp);
        tmp_env = tmp_env->next;
        i++;
    }
    arr[i] = NULL;
    return (arr);
}

void	computing_exit_status(t_shell *minishell)
{
    int	ret;

    waitpid(-1, &ret, 0);
    if WIFSIGNALED(ret)
    	minishell->child_exit_status = WTERMSIG(ret) + 128;
    else
    	minishell->child_exit_status = WEXITSTATUS(ret);
}

void	heredoc_free(t_shell *minishell)
{
    close(minishell->apps->fd_heredoc[0]);
    free(minishell->apps->heredoc);
    minishell->apps->heredoc = NULL;
}


char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;
	int		length;
	int		index;

	if (!s1 || !s2)
		return (0);
	length = 0;
	index = 0;
	result = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (result == 0)
	{
		free(s1);
		free(s2);
		return (NULL);
	}
	while (*(s1 + length))
		result[index++] = s1[length++];
	length = 0;
	while (*(s2 + length))
		result[index++] = s2[length++];
	result[index] = '\0';
	free(s1);
	free(s2);
	return (result);
}


int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

void	ft_putstr(char *a)
{
	int	i;

	if (!a)
		return ;
	i = 0;
	while (a[i])
	{
		write(1, &a[i], 1);
		i++;
	}
}

void skip_space_tab(t_shell *minishell, int *i)
{
	while (minishell->input[*i] != 0 && (minishell->input[*i + 1] == ' '
		|| minishell->input[*i + 1] == '\t'))
		++(*i);
}

char *check_for_data(t_shell *minishell, int i)
{
	char *ret;

	if (minishell->input[i] != 0 && minishell->input[i + 1] != 0)
		ret = ft_strdup(minishell->input + i + 1);
	else
		ret = NULL;
	return (ret);
}