#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <signal.h>
# include <errno.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>
# include <fcntl.h>

# define ERROR 1
# define HEREDOC "/tmp/thisisaheredocument"

enum				e_token_type
{
	COMMAND = 0,
	R_APPEND,
	R_HEREDOC,
	R_TRUNC,
	R_INPUT,
	PIPE,
};

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_token
{
	enum e_token_type	type;
	char				**args;
	struct s_token		*prev;
	struct s_token		*next;
}					t_token;

typedef struct s_quot
{
	int				i;
	int				start;
	char			*content;
	char			quot;
	int				i_q;
}					t_qout;

typedef struct s_utils
{
	int		fd_stdout;
	int		fd_stdin;
	int		save_in;
	int		save_out;
	int		pipes;
	int		exit;
	int		no_exec;
	pid_t	last;
}				t_utils;

typedef t_token *(*t_add)(t_token **t_lst, t_list **e, t_token **curr);

//GLOBAL
extern t_env	*g_env;

//TOKEN
void					ft_tkadd_back(t_token **lst, t_token *new);
t_token					*ft_tklast(t_token *lst);
t_token					*ft_token_new(enum e_token_type type, char **args);

//ENV
int						parse_env_3(t_qout *tmp, char *input, t_list **list);
int						parse_env_end(t_qout *tmp, char *input, t_list **list);
char					*get_value_from_env(char *key);
int						init_env(char **envp);
int						add_env(char *name, char *value);
int						question_env(t_qout *tmp);

//FREE
void					free_tmp(t_qout *tmp);
void					*free_all_env(void);
void					free_all_tokens(t_token *token_list);
void					free_symbols_strs(char **symbols_strs);
void					main_free(t_token *token_list, t_list *list,
							char *cmd_line, t_utils *utils);

//PARSER
t_list					*parse_input(char *cmd_line);
void					init_tmp(t_qout *tmp);
int						pass_letter(char *input, t_list **list, t_qout *tmp);
int						pass_space(char *input, t_qout *tmp);
t_token					*put_to_tokens(t_list **list);
int						parse_separator(char *input, int i, t_list **list);
int						find_type_separator(t_list *l);
void					push_content(char **content, t_list **list);
void					tmp_join_free(t_qout *tmp, char *key);

//QUOT
int						meet_quot(char *input, t_list **list, t_qout *tmp);
int						parse_quot(char *input, t_list **list, t_qout *tmp);
int						glue_aft_quot(char *input, t_list **list, t_qout *tmp);
int						close_quot(char *input, t_list **list, t_qout *tmp);
void					join_substr(char *input, t_qout *tmp);
void					new_quot(char *input, t_qout *tmp);
int						quot_condition_1(t_qout *tmp, char *input);
int						quotes_condition_2(char *input, t_qout *tmp);

//ARRAY
int						ft_arraylen(char *array[]);
char					**ft_arraypush(char *array[], const char *s);
void					ft_arrayfree(char **array);

//CHECK
int						check_quotes(char *q, char c);
int						ft_is_some(char c);
int						ft_isseparator(char c);
int						ft_isspace(char c);

//UTILS
int						ft_is_new_token(char c);
void					ft_error(char *arg, char *error_msg);

//ADD_COMANDS
t_token					*add_c_token(t_token **t, t_list **e, t_token **curr);
t_token					*add_r_tkn(t_token **t_lst, t_list **e, t_token **curr);
t_token					*add_pipe_tkn(t_token **t, t_list **e, t_token **curr);

//SIGNAL
void					handle_ctrl_c(int i);
char					*handle_ctrl_d(void);
void					main_signal(void);

//BUILTINS
int						ms_echo(char **args);
int						ms_cd(char *new_dir);
int						ms_pwd(void);
int						ms_export(char **args);
char					**split_export(char *env);
int						no_args(void);
int						ms_unset(char **args);
void					unset_env(char *name);
int						ms_env(void);
int						ms_exit(char **args, t_utils *utils);
void					change_env_value(char *name, char *value);

//EXEC
int						ms_exec(char **args);
void					redirect_input(t_token *token, t_utils *utils);
void					redirect_output(t_token *token, t_utils *utils);
void					ms_heredoc(char *delimiter);
void					redirect_doc(t_utils *utils);
void					tokens(t_token *token, t_utils *utils);
int						find_pipe(t_token *token);
void					pipe_exec(t_token *token, t_utils *utils);
int						execute_commands(char **args, t_utils *utils);
void					parent_process(t_utils *utils, int *fd);
void					close_fds(int *fd, int num_pipes);
t_token					*next_command(t_token *token);
void					dup_smth(int fildes, int fildes2);
void					rearrange_token(t_token **token, t_token *new);
int						pipes_num(t_token *token);
void					add_new_env(char *name, char *value);
char					*env_value(char *name);
int						exit_status(int code);
void					free_arr(char **arr);
char					**diff_split(char const *s, char c);
char					*lwr_s(char *str);
char					**list_to_array(void);
char					*find_bin(char **paths, char *bin);
void					open_heredoc(t_token *token, t_utils *utils);
void					command_signal(void);
void					heredoc_ctrl_c(int signo);
void					reset_fds(t_utils *utils);

#endif
