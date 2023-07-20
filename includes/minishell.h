#ifndef MINISHELL_H 
# define MINISHELL_H 

//###############################################################
//DATA_STRUCTURES
//###############################################################

//Token enumerator - defines the possible types of tokens;
typedef enum e_token{
	PIPE_READ, //0
	PIPE_WRITE, //1 
	INFILE, //2
	OUTFILE, //3
	COMMAND, //4
	FLAG, //5
	PIPE, //6
	ENV_VAR, //7
	DELIMITER, //8
	APPENDER, //9
	REDIRECT_IN, //10
	REDIRECT_OUT, //11
	NONE, //12
	APPEND, //13
	STDIN_IN, //14
	STDOUT_OUT, //15
} t_token;

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
} t_builtin;

//Linked list node - each command is parsed into a t_lexer node for the executioner to be handled accordingly;
typedef struct lexerinfo {
	char				**content; 		//INFILE/OUTFILE/CMD + OPTIONAL FLAGS (file could also be absolute/relative path);
	char				*path;			//IF NULL -> NO PATH, ELSE -> PATH TO CMD;
	char				*file;			//IF THERE IS AN INFILE OR OUTFILE, ELSE NULL;
	int					input;			//ENUM_IO:PIPE_READ/FILE/STDIN/NONE
	int					output;			//ENUM_IO:PIPE_WRITE/FILE/STDOUT/NONE
	char				*delim;
	struct lexerinfo	*next;
}	t_lexer;

//Main struct - contains all the meta data about minishell such as environmental variables, access to the t_lexer list, status, builtin token and more.
typedef struct s_minishell {
	t_lexer				*cmd_lst;
	char				**env_cpy;
	int					status;
	int					builtin;
}	t_minishell;

//###############################################################
//		LEXER FUNCTIONS
//###############################################################

		//lexer.c
t_lexer	*lexing(char *line);
t_lexer	*which_case(t_lexer	*info_list, char **splitted_line, int *enum_array);
t_lexer	*parsing_array(t_lexer *info_list, char **splitted_line, int *enum_array);
int		*into_enum_array(char **splitted_line, int *enum_array, int index);
int		which_enum(char **splitted_line, int index);

		//lexer_utils.c
int		skip_spaces(char *line, int index);
int		ammount_of_words(char *line);
int 	get_env_end(char *line, int index);
int		get_max_array(char **array);
int		check_for_quotes(char *line);

		//lexer_eddit_line.c
char	*put_spaces_in_line(char *line);
char	*edit_line(char *old, char *new);
int		is_metacharachter(char c);

		//lexer_split_quotes.c
char	**split_with_quotes(char *line);

		//lexer_get_path.c
char	*get_path_of_command(char *command);
char	*find_path_loop(char **paths, char *command);
char	**put_slash_behind(char **paths);

		//lexer_data_org.c
t_lexer	*organizing_data(t_lexer *info_list, char **splitted_line, int *enum_array, int index);
t_lexer	*data_org_command(t_lexer *info_list, char **splitted_line, int *enum_array, int index);
t_lexer	*data_org_pipe(t_lexer *info_list);
t_lexer	*data_org_file(t_lexer *info_list, char **splitted_line, int *enum_array, int index);
t_lexer	*data_org_delim(t_lexer *info_list, char **splitted_line, int *enum_array, int index);
		
		//lexer_dataorg_utils.c
t_lexer *create_new_node(t_lexer *info_lexer);
char	**allocate_2d_arr(int size);
int		check_for_flags(char **splitted_line, int *enum_arr, int index);
int		check_for_outfile(char **splitted_line, int *enum_array, int index);

		//lexer_into_list.c
t_lexer	*one_word_lexer(t_lexer *info_list, char **splitted_line);
t_lexer	*two_word_lexer(t_lexer *info_list, char **splitted_line);
t_lexer	*into_linklist(t_lexer *info_list, char *word_var, int enum_var);

		//data_org_special.c
int		check_special_cases(char **splitted_line);
t_lexer *which_special_case(t_lexer *info_list, char **splitted_line, int *enum_array);
t_lexer	*special_case_echo(t_lexer *info_list, char **splitted_line, int *enum_array, int index);
t_lexer	*special_case_rm(t_lexer *info_list, char **splitted_line, int *enum_array);

		//parsing_grep.c
int		check_for_grep(t_lexer *info_list);
t_lexer *grep_parser(t_lexer *info_list, char **splitted_line);
t_lexer	*rm_quotes_grep(t_lexer *info_list);

		//parser_cat.c 
int		check_for_cat(t_lexer *info_list);
t_lexer *cat_parser(t_lexer *info_list, char **splitted_line);
t_lexer *check_content(t_lexer *info_list, char **splitted_line, int index);

		//lexer_data_envvar.c
char	**edit_arr_env(char **splitted_line, int *enum_array);
char	**new_2d_array(char **splitted_line);
char	*trim_envvar(char *line);
int		check_for_envvar(char **splitted_line, int *enum_array);

//###############################################################
//		ERROR AND FREE FUNCTIONS
//###############################################################

		//error.c
void	free_2d_array(char **array);
void	error_command_not_found(char *cmd);
void	error_export_invalid_identifier(char *input);
void	error_unset_too_few_args();

//###############################################################
//		EXECUTION FUNCTIONS
//###############################################################

//		execution_processes.c
int		execute_cmds(t_lexer *head, char *envp[]);

//		execution_utilities.c
char	*get_path(char *cmd);
int		arg_is_env(char *raw_input, char **value);
int		check_access(char *cmd);
int		var_exists(char	**env, char *var, int var_len);

//		utilities_double_arrays.c
char	**copy_double_array(char **array);
void	print_double_array(char **arr);
void	free_double_array(char **array);
char	**append_to_double_array(char **src, char *str);
char	**replace_str_in_array(char **src, char *str, int index);
char	**remove_str_from_array(char **src, int index);

//		execution_builtin_operations.c
void	execute_echo(char **raw_input, int *exit_status);
void	execute_cd(t_minishell *shell);
void	execute_pwd(int *exit_status);
void	execute_env(char *envp[]);
void	execute_export(t_minishell *shell);
void	execute_unset(t_minishell *shell);

//		interface_frontend.c
void	init_ascii_art(void);

//		execution_builtin.c
int		execute_builtin(t_minishell *shell);
int		is_builtin(t_minishell *data);

//		execution_heredoc.c
void	create_heredoc_tmp(char *delim);

//		signal_handling.c
void	catch_signals(void);

//		memory_management.c		
void	clean_up(t_minishell *shell);
void	free_ll(t_lexer **lst);

//###############################################################


#endif
