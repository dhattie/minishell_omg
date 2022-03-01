
//
// Created by user on 12.02.2022.
//

#include "../include/minishell.h"


int	dollar_child_status(t_shell *minishell, int *i, int j)
{

	char	*tmp1;
	char	*tmp2;
	char	*tmp3;

	j = 0;
//	//Изменения №2
//	tmp2 = ft_itoa(minishell->child_exit_status);
//	tmp3 = ft_strdup(minishell->input + *i + 1);
//	*i = *i + ft_strlen(tmp2) - 2;
//	tmp2 = ft_strjoin_free(tmp2, tmp3);
//	free(minishell->input);
//	minishell->input = tmp2;
//	return (0);

//изменеиея №1
//    char	*tmp1;
//    char	*tmp2;
//    char	*tmp3;
//
//	tmp1 = ft_substr(minishell->input, 0, j);
//	tmp2 = ft_itoa(minishell->child_exit_status);
//	j = ft_strlen(tmp2);
//	tmp3 = ft_strdup(minishell->input + *i + 1);
//	tmp2 = ft_strjoin_free(tmp2, tmp3);
//	free(minishell->input);
//	minishell->input = ft_strjoin_free(tmp1, tmp2);
//	*i = *i + j - 2;
//	return (0);

/** Изначальное состояние */
    tmp1 = ft_substr(minishell->input, 0, j);
	//printf("tmp1 = %s\n", tmp1);

    tmp2 = ft_itoa(minishell->child_exit_status);
	//printf("tmp2 = %s\n", tmp2);

    j = ft_strlen(tmp2);

	tmp3 = ft_strdup(minishell->input + *i + 1);
	//printf("tmp3 = %s\n", tmp3);
	//printf("------------------\n\n");
    tmp2 = ft_strjoin_free(tmp2, tmp3);
    tmp1 = ft_strjoin_free(tmp1, tmp2);
    free(minishell->input);
    minishell->input = tmp1;
    *i += j - 2;
    return (0);
}

//int	dollar_is_space(int *i)
//{
//    *i = *i - 1;
//    return (0);
//}

int	dollar_cases(t_shell *minishell, int *i, int j)
{
    char	*tmp1;
    char	*tmp2;

	tmp1 = ft_substr(minishell->input, 0, j);
	tmp2 = ft_strdup(minishell->input + *i);
	free(minishell->input);
	*i = *i - 2;
	minishell->input = ft_strjoin_free(tmp1, tmp2);

//    tmp1 = ft_substr(minishell->input, 0, j);
//    tmp2 = ft_strdup(minishell->input + *i);
//    tmp1 = ft_strjoin_free(tmp1, tmp2);
//    free(minishell->input);
//    *i = *i - 2;
//    minishell->input = tmp1;
    return (0);
}

int	dollar_env(t_shell *minishell, int *i, int j)
{
    char	*tmp1;
    char	*tmp2;
    char	*tmp3;
    char	*env_value;

    while (ft_isalnum(minishell->input[*i]) || minishell->input[*i] == '_')
        (*i)++;
    tmp1 = ft_substr(minishell->input, 0, j);
	tmp2 = ft_substr(minishell->input, j + 1, *i - j - 1);
	env_value = ft_getenv_value(minishell->environment, tmp2);
    tmp3 = ft_strdup(minishell->input + *i);
    *i = *i + ft_strlen(env_value) - ft_strlen(tmp2) - 2;
    free(tmp2);
    tmp2 = ft_strjoin(env_value, tmp3);
    free(tmp3);
    tmp1 = ft_strjoin_free(tmp1, tmp2);
	if (ft_strlen(tmp1) == 0)
    {
        free(tmp1);
        tmp1 = NULL;
    }
    free(minishell->input);
    minishell->input = tmp1;
    return (0);
}

int	dollar_handler(t_shell *minishell, int *i)
{
	int		j;
	char	input;

	j = *i;
	(*i) = (*i) + 1;
	input = minishell->input[*i];
	if (input == '?')
		return (dollar_child_status(minishell, i, j));
	else if (input == ' ' || input == '\t' || input == '\0')
	{
		*i = *i - 1;
		return (0);
	}
	//return (dollar_is_space(i));
	else if (ft_isdigit(input) || input == '\'' || input == '\"')
		return (dollar_cases(minishell, i, j));
	else
		return (dollar_env(minishell, i, j));
//	return (0);

//    int		j;
//
//    j = *i;
//    ++(*i);
//    if (minishell->input[*i] == '?')
//        return (dollar_child_status(minishell, i, j));
//    else if (minishell->input[*i] == ' ' || minishell->input[*i] == '\t'
//             || minishell->input[*i] == '\0')
//        return (dollar_is_space(i));
//    else if (ft_isdigit(minishell->input[*i]) || minishell->input[*i] == '\''
//             || minishell->input[*i] == '\"')
//        return (dollar_cases(minishell, i, j));
//    else
//        return (dollar_env(minishell, i, j));
//    return (0);
}
