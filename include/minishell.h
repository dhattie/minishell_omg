//
// Created by user on 10.02.2022.
//

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <unistd.h>
# include <signal.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/errno.h>
# include <sys/stat.h>

# define IS_PIPE						1
# define TOKEN_OR						2
# define TOKEN_REDIRECT_OUTPUT			3
# define TOKEN_REDIRECT_OUTPUT_APPEND	4
# define TOKEN_REDIRECT_INPUT			5
# define TOKEN_HEREDOC					6
# define TOKEN_AND						7
# define WILDCARD_ASTERISK				8

# define omg_minisheel	"\e[0;32mminishell$\e[0;39m "


typedef struct s_envp
{
    char			*key;
    char			*value;
    struct s_envp	*next;
    struct s_envp	*prev;
}	t_envp;

typedef struct s_prog
{
    int				argc;
    char			**argv;
    int				is_argv;
    int				token;
    char			*output_file;
    int				fd_output_file;
    char			*input_file;
    int				fd_input_file;
    char			*heredoc;
    int				fd[2];
    int				fd_heredoc[2];
    int				do_not_launch;
    struct s_prog	*head;
    struct s_prog	*next;
}	t_prog;

typedef struct s_shell
{
    char	*input;
    int		child_exit_status;
    int		fd0_source;
    int		fd1_source;
    int		fd2_source;
    int		launch_method;
    t_prog	*apps;
    t_envp	*environment;
    int		argc;
    char	**argv;
}			t_shell;


typedef struct s_aster
{
    DIR				*dir;
    struct dirent	*cmp;
    int				k;
    int				j;
    int				argc;
}					t_aster;

typedef struct s_temp /** change */
{
    char	*tmp1;
    char	*tmp2;
    char	*tmp3;
	char	*tmp4;
}			t_temp;


/** minishell_signals.c */
void	base_signal(void);
void	input_eof(void);
void	cntrl_c(int sig);
void	cntrl_c2(int sig);

/** shlvl_handler.c */
void	check_shlvl(t_shell *minishell);  /** change code*/

/** minishell.c */
void    initialization(t_shell *minishell, int argc, char **argv); // it wil bee static function
int     minishell_pre_parser(t_shell *minishell); // it wil bee static function
int		preparing_head(t_shell *minishell);
int		minishell_parser(t_shell *minishell, int *i); // change code

/** exec_apps.c */
void	minishell_scheduler(t_shell *minishell);
void	shell_executor(t_shell *minishell);
int	minishell_executor_pipe(t_shell *minishell);
int	source_fd_replacer(t_shell *minishell, int switcher); // it wil bee static function
int	minishell_executor_no_pipe(t_shell *minishell); // it wil bee static function

/** grabage_collector.c */
void	garbage_collector2(t_shell *minishell);
void	garbage_collector(t_shell *minishell);

/** app_handler.c */
void	add_application(t_shell *minishell); /** change code */
t_prog	*new_application(void);

/** buitin_errors.c */
int	ft_error_unset(t_shell *minishell, char *str);
int	ft_error_export(t_shell *minishell, char *str);
int	ft_error_cd_no_file(t_shell *minishell, char *str);
int	ft_error_cd_not_set(t_shell *minishell, char *str);
int	ft_error_cd(t_shell *minishell);

/** dollar_hendler.c */
int	dollar_child_status(t_shell *minishell, int *i, int j); // it wil bee
// static function /** change code*/
int	dollar_cases(t_shell *minishell, int *i, int j); // static function /**
// change code*/
int	ft_error_cd_not_set(t_shell *minishell, char *str); // it wil bee static function
int	ft_error_cd_no_file(t_shell *minishell, char *str); // it wil bee static function
int	ft_error_export(t_shell *minishell, char *str); // it wil bee static function
int	ft_error_unset(t_shell *minishell, char *str);
int	dollar_handler(t_shell *minishell, int *i); /**  change code */

/** exec_u_apps.c */
char	*get_prog_name(t_shell *minishell);
int	builtin_exec(t_shell *minishell);
int	minishell_pre_executor(t_shell *minishell);
int	minishell_post_executor(t_shell *minishell);

/** ft_split_once */
char	**ft_split_once(char *str, char ch);

/** minishell_cd.c */
int	cd_get_home(t_shell *minishell); // it wil bee static function
int	cd_swap(t_shell *minishell); // it wil bee static function
int	cd_arg(t_shell *minishell, char *str); // it wil bee static function
int	get_cd(t_shell *minishell, char **str);

/** minishell_cd_u.c */
void	change_old_new_pwd(t_shell *minishell, char *str, char *key);
char	*find_pwd(t_shell *minishell, char *str);

/** minishell_cd_u.c */
void	change_old_new_pwd(t_shell *minishell, char *str, char *key);
char	*find_pwd(t_shell *minishell, char *str);

/** minishell_echo.c */
int		echo_check_flag(char *str);
void	write_echo(char **args, int i, int n);
int		get_echo(t_shell *minishell, char **args);

/** minishell_env.c */
char	*ft_getenv_value(t_envp *lst, char *key);
int     get_env(t_shell *minishell, char **str);
void	get_environment(t_shell *minishell, char **env);

/** minishell_exit.c */
int	has_digit(char *str); // it wil bee static function
int	exit_error(char *str); // it wil bee static function
int	get_exit(t_shell *minishell, char **str);

/** minishell_export.c */
void	ft_lst_swap_01(t_envp **swap);
void	ft_lst_swap_02(t_envp **swap);
void	ft_lst_swap_03(t_envp **swap);
int     sort_export(t_envp **tmp_env);
int     get_export(t_shell *minishell, char **str);

/** minishell_export_u.c */
t_envp	*fullfill_env(t_envp *env);
int	check_export_dup(t_envp *env, char **arr);
int	ft_has_alnum(char *str); // it wil bee static function
int	check_export(t_shell *minishell, char **str);

/** minishell_pwd */
int	get_pwd(t_shell *minishell, char **str);

/** minishell_unset.c */
void	ft_lstdelone_minishell(t_envp *lst);
void	unset_del_elem(t_envp *tmp_exp, char *str, int f);
int		check_equal(char **str); // it wil bee static function
void	check_unset_params(t_shell *minishell, char **str); // it wil bee static function
int	get_unset(t_shell *minishell, char **str);

/** quotes_handler.c */
int	single_quote(t_shell *minishell, int *i); //change code
int	double_quote(t_shell *minishell, int *i); //change code

/** split_into_asterisk.c */
char	**upd_matches(t_aster *astr, char **argv); // it wil bee static function
int	search_half_matches(char *pattern, t_aster *astr); // it wil bee static function
void	compare_matches(t_aster *astr, char *pattern, char ***ret); // it wil bee static function
char	**search_matches(t_shell *minishell, int *i, t_aster	*astr); // it wil bee static function
void	split_into_asterisk(t_shell *minishell, int *i);

/** split_into_asterisk_u.c */
char	**lonely_pattern(char *pattern, t_aster	*astr);
t_aster	create_astr(void);

/** split_into_mandatory.c */
int	split_into_output_file(t_shell *minishell, int *i); // it wil bee static function
int	split_into_input_file(t_shell *minishell, int *i); // it wil bee static function
int	split_into_heredoc(t_shell *minishell, int *i); // it wil bee static function
void	expand_argv(t_shell *minishell, int *i);
int	split_input(t_shell *minishell, int *i);


/** tokkens_handler.c */
int	handle_pipe(t_shell *minishell, int *i); // it wil bee static function //
// change code
int	redirect_output(t_shell *minishell, int *i); // it wil bee static
// function // change code
int	redirect_output_append(t_shell *minishell, int *i); // it wil bee static
// function //change code
int	redirect_input(t_shell *minishell, int *i); // it wil bee static function
int	tokens_handler(t_shell *minishell, int *i);

/** tokens_her_bonus.c */
int	handle_or(t_shell *minishell, int *i); /** cgange code */
int	heredoc(t_shell *minishell, int *i);
int	single_ampersand(t_shell *minishell, int *i);
int	double_ampersand(t_shell *minishell, int *i);

/** utils.c */
int		ft_lstsize(t_envp *lst);
void	check_list(t_envp *list);
char	**get_arr_env(t_envp *env);
void	computing_exit_status(t_shell *minishell);
void	heredoc_free(t_shell *minishell);
char	*ft_strjoin_free(char *s1, char *s2); /** переделать и перенести в др файл*/
int		ft_strcmp(char *s1, char *s2); /** переделать и перенести в др файл*/
void	ft_putstr(char *a);
void	skip_space_tab(t_shell *minishell, int *i); /** my functions */
char	*check_for_data(t_shell *minishell, int i); /** my fuctions */

/** wildcards_handler.c */
int	wildcards_handler(t_shell *minishell, int *i);

/** errors_handler.c */
int	syntax_error(t_shell *minishell, const char *token, int len);
int	standard_error(t_shell *minishell, char *arg_name);
int	runtime_error(t_shell *minishell, char *arg_name);
int	executing_error(t_shell *minishell);
int	pid_error(t_shell *minishell);

/** `garbage_collector.c */
void	garbage_collector2(t_shell *minishell);
void	garbage_collector(t_shell *minishell);

/** minishell_export_u.c */
t_envp	*fullfill_env(t_envp *env);
int	check_export_dup(t_envp *env, char **arr);
int	ft_has_alnum(char *str);
int	check_export(t_shell *minishell, char **str);

/** lst_functions.c */
void	ft_lstadd_back_minishell(t_envp **lst, t_envp *new);
void	ft_lstclear_minishell(t_envp **lst);
t_envp	*ft_lstnew_minishell(char *key, char *value);
t_envp	*ft_lstlast_minishell(t_envp *lst);
t_envp	*ft_lstfirst_minishell(t_envp *lst);

#endif //MINISHELL_H
