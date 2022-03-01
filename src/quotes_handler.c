//
// Created by user on 12.02.2022.
//

#include "../include/minishell.h"

int	single_quote(t_shell *minishell, int *i)
{
//    char	*tmp1;
//    char	*tmp2;
//    char	*tmp3;
	t_temp	str;
    int		j;

    j = *i;
    while (minishell->input[++(*i)])
        if (minishell->input[*i] == '\'')
            break ;
    if (minishell->input[*i] == 0)
        return (syntax_error(minishell, minishell->input + *i, 1));

	str.tmp1 = ft_substr(minishell->input, j + 1, *i - j - 2);
	str.tmp2 = ft_strjoin("\'", str.tmp1);
	str.tmp3 = ft_strjoin(str.tmp2, "\'");

	free(str.tmp1);
	free(str.tmp2);

	str.tmp4 = ft_strdup(minishell->input + *i + 1);
	str.tmp3 = ft_strjoin_free(str.tmp3, str.tmp4);
//    tmp1 = ft_substr(minishell->input, 0, j);
//    tmp2 = ft_substr(minishell->input, j + 1, *i - j - 1);
//    tmp3 = ft_strdup(minishell->input + *i + 1);
//    tmp2 = ft_strjoin_free(tmp2, tmp3);
//    tmp1 = ft_strjoin_free(tmp1, tmp2);
    free(minishell->input);
    *i -= 2;
    minishell->input = str.tmp3;
    return (0);
}

int	double_quote(t_shell *minishell, int *i)
{
	t_temp	str;
    int		j;

    j = *i;
    while (minishell->input[++(*i)])
    {
        if (minishell->input[*i] == '\"')
            break ;
        else if (minishell->input[*i] == '$'           /** Что это такое? */
                 && minishell->input[*i + 1] != '\"')
            dollar_handler(minishell, i);
    }
    if (minishell->input[*i] == 0)
        return (syntax_error(minishell, minishell->input + *i, 1));

	str.tmp1 = ft_substr(minishell->input, j + 1, *i - j - 2);
	str.tmp2 = ft_strjoin("\"", str.tmp1);
	str.tmp3 = ft_strjoin(str.tmp2, "\"");

	free(str.tmp1);
	free(str.tmp2);

	str.tmp4 = ft_strdup(minishell->input + *i + 1);
	str.tmp3 = ft_strjoin_free(str.tmp3, str.tmp4);

//	printf("%s \n", minishell->input);
//	t.tmp1 = ft_substr(minishell->input, 1, j);
//	//	t.tmp1 = ft_substr(minishell->input, 0, j);
//    printf("tmp1 = %s\n", t.tmp1);
//	//t.tmp2 = ft_substr(minishell->input, j + 2, *i - j);
//	t.tmp2 = ft_substr(minishell->input, j + 1, *i - j - 2);
//	printf("tmp2 = %s\n", t.tmp2);
//    t.tmp3 = ft_strdup(minishell->input + *i + 1);
//	printf("tmp3 = %s\n", t.tmp3);
//    t.tmp1 = ft_strjoin_free(t.tmp1, ft_strjoin_free(t.tmp2, t.tmp3));
    free(minishell->input);
    *i -= 2;
    minishell->input = str.tmp3;
    return (0);
}
