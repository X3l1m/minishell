/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ohearn <ohearn@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 17:43:14 by ohearn        #+#    #+#                 */
/*   Updated: 2023/09/01 10:00:06 by Owen          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*includes*/
# include "../libraries/libftprintf/libft.h"
# include "../libraries/cdl_list/include/cdl_list.h"
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <errno.h>
//# include <error.h>
# include <unistd.h>
# include <limits.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

# define HEREDOC_NAME	"/tmp/.minishell_heredoc_"
# define ERR_MALLOC		"Malloc call failed"
# define ERR_AR			"ambiguous redirect"
# define END_STR		" \t\r\n\v\f<>|"
# define DELIMS			" \t\r\n\v\f"
# define SUCCES			0
# define FAILURE		1

extern int		g_exit_code;

typedef enum e_token_type
{
	SPACES = 1,
	WORD,
	VAR,
	PIPE,
	INPUT,
	TRUNC,
	HEREDOC,//<<
	APPEND, //>> add to file
	END
}	t_token_type;

typedef enum e_status
{
	DEFAULT,
	S_QUOTES,
	D_QUOTES,
}	t_status;

typedef struct s_token
{
	t_token_type	type;
	char			*string;
	char			*string_cpy;
	bool			valid_var;
	bool			join;
	int				status;
	struct s_token	*next;
	struct s_token	*prev;
}		t_token;

typedef struct s_data_fd
{
	char	*infile;
	char	*outfile;
	int		fd_in;
	int		fd_out;
	char	*delim_hd;
	bool	*quotes_hd;
}	t_data_fd;

typedef struct s_commands
{
	char				*com;
	char				**args;
	int					fd_check;
	t_data_fd			*fd_data;
	bool				pipe;
	struct s_commands	*next;
	struct s_commands	*prev;
}		t_commands;

typedef struct s_data
{
	t_token		*token;
	t_dllist	*env;
	char		*user_input;
	t_commands	*cmd;
}		t_data;


// executiom
int		executor(t_commands *cmd, t_dllist *env);
char	*pathf(char *com, t_dlnode *env);
int		cd_com(t_commands *cmd);
int		echo_com(t_commands *cmd);
int		pwd_com(void);
int		builtin_com(t_commands *cmd, t_dllist *env);
void	err_msg(char *com, char *msg);

bool		init_data(t_data *data, char **env);
void		init_data_fd(t_commands *cmd);


int			mini_loop(t_data *data);

void		exit_ms(t_data *data, int num);

bool		init_data(t_data *data, char **env);

//free
void		free_pointer(void *pointer);
void		free_data_fd(t_data_fd *io);
void		free_data(t_data *data, bool clear_all);
void		free_str_arr(char **arr);
char		*join_str(char *str, char *add);
void		lst_clear_tkn(t_token **list, void (*del)(void *));
void		lst_delone_cmd(t_commands *list, void (*del)(void *));
void		lst_clear_cmd(t_commands **list, void (*del)(void *));
void		set_signals_interactive(void);
void		set_signals_noninteractive(void);
bool		parse_input_str(t_data *data);
int			tokenizer(t_data *data, char *str);
int			save_part(t_data *data, int *i, char *str, int start);
bool		check_for_var(t_token **t_list);

/*list functions*/
t_token		*new_token(char *str, char *str_cpy, int type, int status);
void		lst_add_back_tkn(t_token **lst, t_token *new);
void		lst_delone_tkn(t_token *lst, void (*del)(void *));
void		lst_clear_tkn(t_token **list, void (*del)(void *));

/*string*/
//char	*assign_string(char **str, t_token_type tkn);

bool		parse_input_str(t_data *data);
int			tokenizer(t_data *data, char *str);
int			save_part(t_data *data, int *i, char *str, int start);
bool		check_for_var(t_token **t_list);

/*list functions*/
t_token		*new_token(char *str, char *str_cpy, int type, int status);
void		lst_add_back_tkn(t_token **lst, t_token *new);
void		lst_delone_tkn(t_token *lst, void (*del)(void *));
void		lst_clear_tkn(t_token **list, void (*del)(void *));

//parsing
void		parse_data(t_data *data, t_token *token);
t_commands	*lst_new_command(bool pipe);
void		lst_add_back_cmd(t_commands **list, t_commands *new);
t_commands	*lst_last_cmd(t_commands *list);
bool		process_args(t_token **list, t_commands *cmd);
void		parse_heredoc(t_data *data, t_commands **last_cmd, t_token **list);
void		parse_word(t_commands **cmd, t_token **list);
void		parse_input(t_commands **cmd, t_token **list);
void		parse_trunc(t_commands **cmd, t_token **list);
void		parse_append(t_commands **cmd, t_token **list);
void		handle_pipe(t_commands **cmd, t_token **list);
bool		remove_old_ref(t_data_fd *io, bool infile);
int			add_args_ecmd(t_token **list, t_commands *cmd);
int			create_args_ecmd(t_token **list, t_commands *cmd);
char		*merge_vars(t_token **list);
void		remove_empty_vars(t_token **list);
int			count_e_args(t_token *list);
void		init_cmd(t_commands **cmd);

void		parse_heredoc(t_data *data, t_commands **last_cmd, t_token **list);
char		*get_heredoc_name(void);
char		*get_delim_hd(char *delim, bool	*quotes);
bool		check_line_hd(t_data *data, t_data_fd *io, char **input, bool *ret);
char		*reform_string(char **words);
bool		next_char_sep(char c);
bool		var_between_quotes(char *string, int i);
char		*replace_str_hd(char *string, char *var, int index);
char		*get_val(t_data *data, t_token *temp, char *string);
bool		remove_old_ref(t_data_fd *io, bool infile);
int			expand_var(t_data *data, t_token **list);
void		replace_var(t_token **list, char *var, int index);
int			var_length(char *string);
char		*get_new_string(char *old, char *var, int len, int index);
bool		handle_quotes(t_data *data);
bool		change_status(t_token **list, int i);
void		change_status_quote(t_token **list, int *i);
bool		change_status_default(t_token **list, int *i);
void		sort_strings(t_token **list, char *new);
char		*id_variable(char *string);
bool		valid_var(t_data *data, char *var);

/*Functions*/
void		error_mini(char *errmsg);
bool		print_error_msg(char *str);
int			cmd_err_msg(char *command, char *info, char *msg, int err);

t_dllist	*envcpy(char **envp);
int			envsearch(t_dllist *env, char *var);
char		*ft_getenv(t_dllist *env, char *var);
t_dlnode	*ft_getenvnode(t_dllist *env, char *var);

/*enviroment*/

/*env*/

#endif