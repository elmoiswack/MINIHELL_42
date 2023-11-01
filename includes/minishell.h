/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                       :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:09:51 by dhussain          #+#    #+#             */
/*   Updated: 2023/11/01 13:54:31 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H 
# define MINISHELL_H 
# include <stdbool.h>
# include <unistd.h>

//###############################################################
//DATA_STRUCTURES
//###############################################################

// Black		= "\001\033[0;30m\002"		# Black
// Red			= "\001\033[0;31m\002"		# Red
// Green		= "\001\033[0;32m\002"		# Green
// Yellow		= "\001\033[0;33m\002"		# Yellow
// Blue			= "\001\033[0;34m\002"		# Blue
// Purple		= "\001\033[0;35m\002"		# Purple
// Cyan			= "\001\033[0;36m\002"		# Cyan
// White		= "\001\033[0;37m\002"		# White
// Text_Off		= "\001\033[0m\002"			# Text Style Off
// Bold			= "\001\033[1m\002"			# Text Style Bold

# define CURSED "\001\033[0;31m\002 \
\001\033[1m\002 Ç̈ͮ̾ͫ̆ͯ̏U̷͂̎Rͩ̀S̶̽ͮ̑̋̉ͩ̃Ë̷́̓̾͆ͫḐ͒̆̚̚_ > \
\001\033[0m\002"

# define NON_CURSED "\001\033[1m\002 \
Z_SHELL_ > \001\033[0m\002"

# define Z_THEME "LS_COLORS=rs=0:di=01;31:ln=01;36:\
mh=00:pi=40;33:ex=1;37:" 

//Token enumerator - defines the possible types of tokens;
typedef enum e_token{
	PIPE_READ,
	PIPE_WRITE,
	INFILE,
	OUTFILE,
	COMMAND,
	FLAG,
	PIPE,
	ENV_VAR,
	DELIMITER,
	APPENDER,
	REDIRECT_IN,
	REDIRECT_OUT,
	NONE,
	APPEND,
	STDIN_IN,
	STDOUT_OUT,
	HEREDOC,
}	t_token;

//Error enumerator - defines error mssg;
typedef enum e_error {
	E_NONE,
	E_ALLOC,
	E_INPUT,
	E_IDENT,
	E_CMDNFND,
	E_FORK,
	E_EXIT,
	E_ERR,
}	t_error;

//Builtin enumerator - defines the different types of possible builtins;
typedef enum e_builtin {
	ECHO,
	CD,
	PWD,
	ENV,
	EXIT,
	EXPORT,
	UNSET,
	NO_BUILTIN,
}	t_builtin;

typedef enum e_sig_profile {
	PARENT,
	CHILD,
	HD,
	WAITING,
}	t_sig_profile;

//Linked list node - each command is parsed into a t_lexer node 
//	for the executioner to be handled accordingly;
typedef struct lexerinfo {
	int					cmd_id;
	char				**content;
	char				*path;
	char				**infile;
	int					index_inf;
	char				**outfile;
	int					index_outf;
	int					input;
	int					output;
	char				**delim;
	int					index_delim;
	int					check_free;
	char				**env_copy;
	int					error_code;
	const char			*error_str;
	struct lexerinfo	*next;
}	t_lexer;

//ERROR CODES:
//1 = COSTUM MESSAGE
//2 = SYNTAX_ERROR
//3 = MALLOC_ERROR

//Main struct - contains all the meta data about minishell such as 
//environmental variables, 
//access to the t_lexer list, status, builtin token and more.
typedef struct s_minishell {
	t_lexer				*cmd_lst;
	char				**env_cpy;
	int					status;
	int					builtin;
	t_sig_profile		profile;
}	t_minishell;

//###############################################################
//		LEXER FUNCTIONS
//###############################################################

		//lexer.c
t_lexer	*lexing(char *line, char **env_cpy);
t_lexer	*set_variables(t_lexer *info_list, char *line);
t_lexer	*which_case(t_lexer	*info_list, char **splitted_line, int *enum_array);
int		info_list_checker(t_lexer *info_list, \
	char **splitted_line, int *enum_array);
t_lexer	*parsing_array(t_lexer *info_list, \
	char **splitted_line, int *enum_array);

		//line_checker.c
int		input_line_check(char *line, t_lexer *info_list);
int		inputline_other_checks(char *line, t_lexer *info_list, int index);
int		inputline_other_checks(char *line, t_lexer *info_list, int index);

		//linechecker_checks.c
int		check_outredirect(char *line, int index, t_lexer *info_list);
int		check_inredirect(char *line, int index, t_lexer *info_list);
int		check_pipe(char *line, int index, t_lexer *info_list);
int		check_the_quotes(char *line);

		//enum_arrayfts.c
int		*into_enum_array(char **splitted_line, int *enum_array, int index);
int		which_enum(char **splitted_line, int index);

		//lexer_utils.c
int		skip_spaces(char *line, int index);
int		ammount_of_words(char *line);
int		get_max_array(char **array);
int		check_for_quotes(char *line);
int		check_spaces_in_quotes(char *line);

		//eddit_line.c
char	*put_spaces_in_line(char *line, t_lexer *info_list);
char	*edit_line(char *old, char *new);
int		is_metacharachter(char c);

		//split_quotes.c
char	**split_with_quotes(char *line, t_lexer *info_list);
char	**split_intoarray(char *line, t_lexer *info_list, char **temp_quotes);
char	**replace_quotes_array(char **split_array, char	**temp_quotes);

		//splitquo_quotefts.c
char	*remove_spaces_quotes_line(char *line, \
	char *new_line, int index_n, int index_l);
char	**store_all_quote_data(char *line, char **temp);
char	*quote_data_inarray(char *line, char **temp, \
	int index_temp, int index_l);

		//split_quotes_utils.c
int		how_many_quotes(char *line);
int		get_end_quote(char *line, int end, int which);
char	*strcpy_splitquo(char *line, int begin, int end);
int		how_many_spaces_quotes(char *line, int index_l);

		//get_path.c
char	*get_path_of_command(char *command, char **env_cpy);
char	*find_path_loop(char **paths, char *command);
char	**put_slash_behind(char **paths);

		//data_org.c
t_lexer	*organizing_data(t_lexer *info_list, \
	char **splitted_line, int *enum_array, int index);
t_lexer	*organizing_data_checks(t_lexer *info_list, char **splitted_line, \
	int *enum_array, int index);

		//dataorg_cases.c
t_lexer	*data_org_pipe(t_lexer *info_list);
t_lexer	*data_org_file(t_lexer *info_list, char **splitted_line, \
	int *enum_array, int index);
t_lexer	*data_org_delim(t_lexer *info_list, char **splitted_line, \
	int *enum_array, int index);
t_lexer	*data_org_appender(t_lexer *info_list, \
	char **splitted_line, int index);

		//dataorg_command.c
t_lexer	*data_org_command(t_lexer *info_list, char **splitted_line, \
	int *enum_array, int index);
char	*rm_dash_flag(char *word_var);
t_lexer	*into_linklist_flag(t_lexer *info_list, \
	char **splitted_line, int *enum_array, int index);

		//dataorg_utils.c
t_lexer	*create_new_node(t_lexer *info_lexer);
char	**allocate_2d_arr(int size, t_lexer *info_list);
int		check_for_flags(char **splitted_line, int *enum_arr, int index);
int		check_for_outfile(char **splitted_line, int *enum_array, int index);

		//dataorg_special_cases.c
int		check_special_cases(char **splitted_line, int *enum_array);
t_lexer	*which_special_case(t_lexer *info_list, \
	char **splitted_line, int *enum_array, int index);
t_lexer	*other_special_case(t_lexer	*info_list, char **splitted_line, \
	int *enum_array, int index);
t_lexer	*special_case_files(t_lexer *info_list, char **splitted_line);

		//into_list.c
t_lexer	*one_two_word_lexer(t_lexer *info_list, char **splitted_line);
t_lexer	*into_linklist(t_lexer *info_list, char *word_var, int enum_var);

		//into_list_cases.c
t_lexer	*into_linklist_delim(t_lexer *info_list, char *word_var);
t_lexer	*into_linklist_command(t_lexer *info_list, char *word_var);
t_lexer	*into_linklist_infile(t_lexer *info_list, char *word_var);
t_lexer	*into_linklist_outfile(t_lexer *info_list, char *word_var);

		//intolist_special.c
t_lexer	*intolist_commands(t_lexer *info_list, \
	char **splitted_line, int *enum_array);

		//parsing_grep.c
int		check_for_grep(t_lexer *info_list);
t_lexer	*grep_parser(t_lexer *info_list, char **splitted_line);
t_lexer	*add_flag_grep(t_lexer *info_list, char **splitted_line);
t_lexer	*rm_quotes_grep(t_lexer *info_list);
char	*rm_guotes_loop(t_lexer *info_list, char *temp);

		//parser_cat.c 
int		check_for_cat(t_lexer *info_list);
t_lexer	*cat_parser(t_lexer *info_list, char **splitted_line);
t_lexer	*check_content(t_lexer *info_list, char **splitted_line, int index);

		//parsing_echo.c
t_lexer	*special_case_echo(t_lexer *info_list, char **splitted_line);
t_lexer	*spca_echo_intolist(t_lexer *info_list, \
	char **splitted_line, int index);
t_lexer	*echo_with_meta(t_lexer *info_list, \
	char **splitted_line, int *enum_array);
t_lexer	*echo_meta_intolist(t_lexer *info_list, \
	char **splitted_line, int *enum_array, int index);
t_lexer	*default_echo_data(t_lexer *info_list, char **splitted_line);

		//variable_expander.c
char	**replace_var_expander(t_lexer *info_list, \
	char **splitted_line, char **env_cpy, int *enum_array);
char	*env_expander_loop(char **splitted_line, int index, char **env_cpy);
char	*get_env_var(char *line, char **env_cpy, int ammount_env);

		//varexp_teplacevars.c
char	*replace_variables(char *line, char **env_temp);
char	*replace_vars_loop(char *line, char *new_line, \
	char **env_temp, int index);
void	rplc_vars_loop_cpy(char *line, \
	char *new_line, int *index_new, int *index);

		//varexp_arrayft.c
char	**expand_env_variables(char **env_temp, char **env_cpy);
char	*expand_variable(char *line, char **env_cpy);
char	**fill_array_env(char *line, int ammount_env, \
	char **env_temp, int index);
char	**check_quotes_env(char **splitted_line);
char	*remove_quotes_string_env(char **splitted_line, int index);

		//varexp_lineft.c
char	*get_variable(char *line, int begin, int end);
char	*remove_quotes_string(char **splitted_line, int index);
char	*rm_quote_string_loop(char **splitted_line, int index, char *new_line);
char	*remove_dollar_sign(char *line);
char	*put_env_in_line(char *new_line, int index_l, \
	char **env_temp, int index_env);

		//varexp_utils.c
int		how_many_env_var(char *line);
int		get_env_end(char *line, int index);
int		get_size_strings(char *line, char **env_temp);
int		check_for_envvar(char **splitted_line);

		//file_delim_func.c
int		get_number_delim(int *enum_array);
t_lexer	*allocate_files(t_lexer *info_list, int *enum_array);

		//list_check.s
t_lexer	*check_quotes_list(t_lexer *info_list);

//###############################################################
//		ERROR AND FREE FUNCTIONS
//###############################################################

		//error.c
void	error_lex(t_lexer *info_list, int error_code, const char *str);

//		err_log.c
int		err_log(t_error err, char *input);

		//free.c
void	free_lexing_content_struct(t_lexer *list);
void	free_lexing_struct(t_lexer *list);
void	free_double_array(char **array);
void	error_lexing_message(t_lexer *list);

//###############################################################
//		EXECUTION FUNCTIONS
//###############################################################

//		execution_absolute_path.c
bool	is_absolute_path(t_lexer *node);
bool	cmd_exists(char *cmd, char *env_cpy[]);
void	parse_node_absolute_path(t_lexer *node);

//		execution_processes.c
int		execute_cmds(t_minishell *shell, t_lexer *head, char *env_cpy[]);

//		execution_utilities.c
char	*get_path(const char *cmd);
int		arg_is_env(char *raw_input, char **value, char *envp[]);
int		var_exists(char	**env, char *var);
char	*ft_getenv(char *var_name, char **env);

//		utilities_debugging.c
void	print_cmd_lst(t_lexer *head);
void	printing_lexer(t_lexer *info_lexer);
void	print_double_array(char **arr);
void	print_debug_info(t_lexer *head);

//		utilities_misc.c
void	add_cmd_id(t_lexer *head);
int		cmd_amount(t_lexer *head);
pid_t	*allocate_pid_array(int n);
int		wait_on_child_processes(t_lexer *head, pid_t *pid, int status);
pid_t	create_child_process(void);

//		execution_cd.c
int		execute_cd(t_minishell *shell, t_lexer *node, int err);
//		execution_echo.c
int		execute_echo(char **raw_input, char *envp[], int status);
//		execution_env.c
int		execute_env(char *envp[], t_lexer *node);
//		execution_export.c
int		execute_export(t_minishell *shell, t_lexer *node);
int		export_content(char *content, t_minishell *shell, bool append);
//		execution_pwd.c
int		execute_pwd(char *env_cpy[]);
//		execution_unset.c
int		execute_unset(t_minishell *shell);
//		execution_exit.c
int		execute_exit(t_lexer *node);
//		execution_utilities.c
bool	is_relative_path(char *content);

//		interface_frontend.c
void	init_ascii_art(void);
void	remove_ctl_echo(void);
void	init_history(void);
void	add_to_history_file(char *line);
char	**colorize_cmd(char *content[]);

//		execution_builtin.c
int		execute_builtin(t_minishell *shell, t_builtin builtin, t_lexer *node);
int		is_builtin(t_lexer *cmd_lst);

//		execution_heredoc.c
int		create_heredoc_loop(t_lexer *head, char *env_cpy[]);

//		execution_heredoc_utilities.c
void	change_permission_heredoc_tmp(void);
void	clean_tmp_files(t_lexer *head, char *envp[]);
int		fetch_exit_status_hd(pid_t pid);

//		execution_heredoc_expansion.c
char	*expand_heredoc_line(char *heredoc_line, char *env_cpy[]);

//		execution_routing.c
void	route_output(int out, t_lexer *node);
void	route_input(int in, t_lexer *node);

//		signal_handling.c
// void	catch_signals_parent(void);
// void	catch_signals_child(void);
void	change_signal_profile(t_sig_profile profile);	

//		memory_management.c		
void	clean_up(t_minishell *shell);
void	free_ll(t_lexer **lst);
char	**rev_free_arr(char **strings_array, int i);

//###############################################################
#endif
