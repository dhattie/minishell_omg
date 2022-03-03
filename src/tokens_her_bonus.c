//
// Created by user on 13.02.2022.
//

#include "../include/minishell.h"


int	handle_or(t_shell *minishell, int *i)
{
    char	*ret;

    ret = NULL;
    if (*i != 0)
        expand_argv(minishell, i);
    ++(*i);
    minishell->apps->token = TOKEN_OR;
    add_application(minishell);
	while (minishell->input[*i] != 0 && (minishell->input[*i + 1] == ' '
    	|| minishell->input[*i + 1] == '\t'))
        ++(*i);
//изменение №1
	  if (ft_strchr("0|<>&", (int)minishell->input[*i + 1]))
		  return (syntax_error(minishell, minishell->input + *i + 1, 1));
// было изначально
//	if (minishell->input[*i + 1] == 0 || minishell->input[*i + 1] == '|'
//        || minishell->input[*i + 1] == '<' || minishell->input[*i + 1] == '>'
//        || minishell->input[*i + 1] == '&')
//        return (syntax_error(minishell, minishell->input + *i + 1, 1));

    if (minishell->input[*i] != 0 && minishell->input[*i + 1] != 0)
        ret = ft_strdup(minishell->input + *i + 1);
    (*i) = -1;
    free(minishell->input);
    minishell->input = ret;
    return (0);
}

int	heredoc(t_shell *minishell, int *i)
{
    char	*ret;

   // ret = NULL;
    if (*i != 0)
        expand_argv(minishell, i);
    minishell->apps->token = TOKEN_HEREDOC;
    ++(*i);

	//изменения 1
	skip_space_tab(minishell, i);
//	while (minishell->input[*i] != 0 && (minishell->input[*i + 1] == ' '
//                                         || minishell->input[*i + 1] == '\t'))
//        ++(*i);
	if (ft_strchr("0|<>&", (int)minishell->input[*i + 1]))
		return (syntax_error(minishell, minishell->input + *i + 1, 1));
// изменения 2

//    if (minishell->input[*i + 1] == 0 || minishell->input[*i + 1] == '|'
//        || minishell->input[*i + 1] == '<' || minishell->input[*i + 1] == '>'
//        || minishell->input[*i + 1] == '&')
//        return (syntax_error(minishell, minishell->input + *i + 1, 1));

//изменения 4
	ret = check_for_data(minishell, *i);
//    if (minishell->input[*i] != 0 && minishell->input[*i + 1] != 0)
//        ret = ft_strdup(minishell->input + *i + 1);
    (*i) = -1;
    free(minishell->input);
    minishell->input = ret;
    return (0);
}

int	single_ampersand(t_shell *minishell, int *i)
{
    return (syntax_error(minishell, minishell->input + *i, 1));
}

int	double_ampersand(t_shell *minishell, int *i)
{
    char	*ret;

//    ret = NULL;
    if (*i != 0)
        expand_argv(minishell, i);
    ++(*i);
    minishell->apps->token = TOKEN_AND;
    add_application(minishell);

// Изменения 1
	skip_space_tab(minishell, i);
//	while (minishell->input[*i] != 0 && (minishell->input[*i + 1] == ' '
//                                         || minishell->input[*i + 1] == '\t'))
//        ++(*i);

// Изменение 2
	if (ft_strchr("0|<>&", (int)minishell->input[*i + 1]))
		return (syntax_error(minishell, minishell->input + *i + 1, 1));

//    if (minishell->input[*i + 1] == 0 || minishell->input[*i + 1] == '|'
//        || minishell->input[*i + 1] == '<' || minishell->input[*i + 1] == '>'
//        || minishell->input[*i + 1] == '&')
//        return (syntax_error(minishell, minishell->input + *i + 1, 1));

//изменения 3
	ret = check_for_data(minishell, *i);

//    if (minishell->input[*i] != 0 && minishell->input[*i + 1] != 0)
//        ret = ft_strdup(minishell->input + *i + 1);

    (*i) = -1;
    free(minishell->input);
    minishell->input = ret;
    return (0);
}
