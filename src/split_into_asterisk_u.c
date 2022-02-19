//
// Created by user on 12.02.2022.
//

#include "../include/minishell.h"


char	**lonely_pattern(char *pattern, t_aster	*astr)
{
    char	**ret;

    ret = (char **)malloc(sizeof(char *) * 2);
    ret[0] = pattern;
    ret[1] = NULL;
    astr->argc++;
    return (ret);
}

t_aster	create_astr(void)
{
    t_aster	astr;

    astr.dir = NULL;
    astr.cmp = NULL;
    astr.k = 0;
    astr.j = 0;
    astr.argc = 0;
    return (astr);
}
