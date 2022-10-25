/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgoncalv <hgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:49:11 by hgoncalv          #+#    #+#             */
/*   Updated: 2022/10/25 23:14:37 by hgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define CYN "\x1B[36m"
# define GRN "\x1b[92m"

# define RESET "\x1B[0m"

# define FT_TOK_BUFSIZE 64
# define FT_TOK_DELIM " \t\r\n\a"
# define FT_RL_BUFSIZE 1024

# include "libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_values
{
	int			quote;
	int			i;
	int			start;
	int			j;
	int			z;
}				t_values;

typedef struct s_envp
{
	char		**envp;
	int			to_exit;
	char		*exit_str;
	int			test_int;
	bool		valid_input;
}				t_envp;

typedef struct s_builtin
{
	int			num_functions;
	char		*builtin_str[9];
	int			(*builtin_func[9])(char **);

	char		**envp;
}				t_builtin;

typedef struct s_vars
{
	int			i;
	int			j;
	int			k;
	int			l;
	int			m;
	int			start;
	int			end;
	int			size;
	int			inner_quote;
	int			outer_quote;
	char		*ptr2str;
	char		*ptr2char;
	char		***p2p2p;
	char		*str;
	char		*str2;
	char		*tmp_str;
	char		*tmp_str2;
	char		**matrix;
	char		**matrix2;
	char		**tmp_matrix;
	char		**tmp_matrix2;

}				t_vars;

extern t_envp	g_envp;

//validation
bool			ft_checker(char *line);

//Initialize Structs
void			ft_inicialize_vars(t_vars *vars);
t_values		ft_init_values(t_values value);
void			ft_inicialize_builtins(t_builtin *builtins);

//Parse Functions
char			**ft_split_line(char *line, char *delimiters);
char			**ft_split_line2(char *line, char *delimiters);
char			***ft_parse_cmds(char **pipes);
char			*ft_strtok_quote_aware(char *str, const char *sep,
					char *chars2jump);
char			*ft_strtok_quote_aware_start(char *str, char **lasts,
					const char *sep);
void			ft_chk_n_exit_if_null_pchar(char *str, char *error_str);
void			ft_chk_n_exit_if_null_ppchar(char **matrix, char *error_str);
char			*ft_update_line(char *line);
int				ft_count_words(char *line);
char			*ft_strchr_byarrayofchars(char *str, char *sepa);
char			**ft_get_jump_interval(char **str, char *chars2jump);
t_values		ft_get_the_value_for_sub(char *line, t_values value);
int				ft_the_word(char *line, t_values help, int words);
char			**ft_split_quote_aware(char *str, char *chars2split);
char			**ft_get_token(char *token, char **tokens, char *delimiters,
					char *chars2jump);
t_values		ft_helper_quote(t_values v, char *line);
t_values		ft_helper_count(t_values v, char *line);
t_values		ft_if_quote_z(char *line, t_values value);
int				check_cmds_for_redir_errors(char ***cmd);

//Variable Expansion
char	**ft_var_expansion_allocate_matrix_n_start_ints(char *str,
														t_vars *vars);
void			ft_var_exp_case1(char *str, t_vars *vars);
void			ft_var_exp_case2(char *str, t_vars *vars);
char			*ft_var_expansion(char *str);
int				ft_var_expansion_is_var(char *ptr, int quote);

//Utils
char			*ft_copy_str_without_chars(char *str, char *chars2remove);
char			*ft_concat3(char *s1, char *s2, char *s3);
char			*ft_concat_multi_getsize_n_alloc(char **s, char *glue);
char			*ft_concat_multi(char **s, char *glue);
char			*ft_concat_multi_glue_first(char **s, char *glue);
void			ft_swap2str(char **str1, char **str2);
void			*ft_realloc(void *ptr, size_t size);
int				ft_closed_quotes(char *line);
int				ft_is_quote(char c, int quote);
int				ft_pipe_end(char *line);
void			ft_get_quotes_inner_outer(char c, t_vars *vars);
int				ft_isnum(char *str);
int				ft_is_cmd_a_no_input(char **cmd);
char			**ft_args_matrix(char **cmd, char **argv);
void			ft_is_the_end(int end, int status);
void			ft_free_redir(t_vars *vars, char *filename, char *chars_str);

//Concat
char			*ft_copy_str_without_chars(char *str, char *chars2remove);
char			*ft_concat3(char *s1, char *s2, char *s3);
char			*ft_concat_string_between_chars(char c_start, char *s,
					char c_end);
char			*ft_concat_multi_getsize_n_alloc(char **s, char *glue);
char			*ft_concat_multi(char **s, char *glue);

//Matrix
int				ft_matrix_get_num_col(char **matrix);
char			**ft_matrix_dup(char **matrix, int push);
char			**ft_matrix_push(char **matrix, char *str);
void			ft_matrix_free(char **matrix);
char			**ft_matrix_remove_col_by_index(char **matrix, int index);
void			ft_print_matrix(char **matrix);
void			ft_print_matrix_add_str2line_start(char **matrix, char *str,
					char *glue);

//Built-In
int				ft_echo(char **argv);
int				ft_env(char **argv);
int				ft_cd(char **argv);
int				ft_pwd(char **argv);
int				ft_exit(char **argv);
int				ft_help(char **argv);
int	ft_set_cd_folder_return_if_free_folder_or_not(char **argv,
													char **ptr2folder);
int				ft_cat(char **argv);
int				ft_heredoc(char **argv);

//Env Functions
int				ft_unset(char **argv);
int				ft_export(char **argv);
char			*ft_getenv(char *name, int trimmed);
int				ft_setenv(char *name, char *value, int overwrite);

//Exec
int				ft_execute(char **cmd);
void			ft_launch_pid0(int *ret, char ***argv, char **path);
int				ft_launch(char **argv);
int				ft_child_proces(int *fd_in, int *p, char ***cmd);
int				ft_setup_pipes(char ***cmd);
int				ft_exec_pipe(char ***cmd, int end);
char			**ft_check_export_return_argv(char **cmd);
void	ft_check_if_back_redir_fill_matrix(t_vars *vars,
										char *chars2replace);
int				ft_check_if_back_redirection(char **argv);
int				ft_check_set_output2file(char **argv, int piped);
int				ft_execute_if_builtin_run(char **argv, int is_piped);
int				ft_execute_if_back_redir(char **argv);
char			**ft_tokenized_str2_matrix(char **cmd);
char			**ft_tokenized_str2_matrix_remove_nps(char **cmd);
char			*ft_get_exec_path(char **argv);
int				ft_get_exec_path_chk_access(char *path, char **env_path,
					char ***matrix);
char			*ft_add_cat_redir(char **pipes);
void			ft_help_pipe(t_vars val, char ***matrix, char ***cmd);

t_vars			*ft_get_out(t_vars *vars, char *glue, char *glue_end);
t_vars			*ft_get_redir(t_vars *vars, char *glue, char *glue_end);
t_vars			*ft_get_vars(t_vars *vars, char *chars2replace);
char			**ft_check_export_return_argv(char **cmd);
int				is_valid_env_var_name(char **name_value);

//Prompt
char			*ft_get_prompt(void);
int				ft_history(char **argv);
char			*ft_get_line_n_set_shell_prompt(void);
char			*ft_check_input(char **ptr2line);
int				ft_check_argv(char *line);

//Minishell
int				ft_loop(void);
void			ft_free_cmd(char ***cmd);
void			ft_free_loop(char ***cmd, char **pipes, char *line);
void			ft_set_env_cmd_return(int status);
void			ft_handler(int signum);

//Extra
char			*ft_remove_char(char **str, char c);
char			*ft_str_replace(char *str, char *sremove, char *sadd);
char			*ft_remove_chars(char *str, char *chars2remove,
					int free_original);

#endif
