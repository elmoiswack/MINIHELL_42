/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_debugging.c                             :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:09:40 by dhussain          #+#    #+#             */
/*   Updated: 2023/11/01 13:34:26 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Global array - used to print out the enum strings.
// Must be deleted before handing in the project.
#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>

// static const char *g_enum[] = {
// [PIPE_READ] = "READ", //0
// [PIPE_WRITE] = "WRITE", //1
// [INFILE] = "INFILE", //2
// [OUTFILE] = "OUTFILE", //3
// [COMMAND] = "COMMAND", //4
// [FLAG] = "FLAG", //5
// [PIPE] = "PIPE", //6
// [ENV_VAR] = "ENV_VAR", //7
// [DELIMITER] = "DELIMITER",//8
// [APPENDER] = "APPENDER", //9
// [REDIRECT_IN] = "REDIRECT_IN", //10
// [REDIRECT_OUT] = "REDIRECT_OUT", //11
// [NONE] = "NONE", //12
// [APPEND] = "APPEND", //13
// [STDIN_IN] = "STDIN", //14
// [STDOUT_OUT] = "STDOUT", //15
// [HEREDOC] = "HEREDOC", //16
// };
//
// static const char *g_builtin[] = {
// 	[ECHO] = "ECHO",
// 	[CD] = "CD",
// 	[PWD] = "PWD",
// 	[ENV] = "ENV",
// 	[EXIT] = "EXIT",
// 	[EXPORT] = "EXPORT",
// 	[UNSET] = "UNSET",
// 	[NO_BUILTIN] = "NO",
// };
//
// void	print_cmd_lst(t_lexer *head)
// {
// 	t_lexer	*current;
// 	int		n;
// 	t_builtin builtin;
// 	int i = 0;
//
// 	current = head;
// 	n = 0;
// 	fprintf(stderr, "\n\033[0;36m--------EXECUTIONER--------\n");
// 	fprintf(stderr, "# CMD\tIN\tOUT\tINFILE(S)\tOUTFILE(S)\n");
// 	while (current)
// 	{
// 		builtin = is_builtin(current);
// 		fprintf(stderr, "%d", n);
// 		if (builtin == NO_BUILTIN && current->content)
// 			fprintf(stderr, " %s", current->content[0]);
// 		else
// 			fprintf(stderr, " %s", g_builtin[builtin]);
// 		fprintf(stderr, "\t%s", g_enum[current->input]);
// 		fprintf(stderr, "\t%s", g_enum[current->output]);
// 		if (current->infile)
// 		{
// 			i = 0;
// 			while (current->infile[i])
// 				i++;
// 			fprintf(stderr, "\t%d", i);
// 		}
// 		else {
// 				fprintf(stderr, "\t0");
// 		}
// 		if (current->outfile)
// 		{
// 			i = 0;
// 			while (current->outfile[i])
// 				i++;
// 			fprintf(stderr, "\t\t%d", i);
// 		}
// 		else {
// 				fprintf(stderr, "\t\t0");
// 		}
// 		fprintf(stderr, "\n");
// 		n++;
// 		current = current->next;
// 	}
// 	fprintf(stderr, "---------------------------\033[0m\n");
// }
//
// void	printing_lexer(t_lexer *info_lexer)
// {
// 	int	index;
//
// 	if (!info_lexer)
// 		return ;
// 	fprintf(stderr, "\033[0;36m----------PARSER-----------\n");
// 	while(info_lexer)
// 	{
// 		index = 0;
// 		if (info_lexer->content)
// 		{
// 			while (info_lexer->content[index])
// 			{
// 				fprintf(stderr, "content[%d] = %s\n", 
//               index, info_lexer->content[index]);
// 				index++;
// 			}
// 		}
// 		fprintf(stderr, "path = %s\n", info_lexer->path);
// 		int i = 0;
// 		if (info_lexer->infile)
// 		{
// 			while (info_lexer->infile[i])
// 			{
// 				fprintf(stderr, "infile[%i] = %s\n", i, info_lexer->infile[i]);
// 				i++;
// 			}
// 		}
// 		i = 0;
// 		if (info_lexer->outfile)
// 		{
// 			while (info_lexer->outfile[i])
// 			{
// 				fprintf(stderr, "outfile[%i] = %s\n", i,
//                 info_lexer->outfile[i]);
// 				i++;
// 			}
// 		}
// 		fprintf(stderr, "input = %s\n", g_enum[info_lexer->input]);
// 		fprintf(stderr, "output = %s\n", g_enum[info_lexer->output]);
// 		if (info_lexer->delim)
// 		{
// 			while (info_lexer->delim[i])
// 			{
// 				fprintf(stderr, "delim[%i] = %s\n", i, info_lexer->delim[i]);
// 				i++;
// 			}
// 		}
// 		fprintf(stderr, "---------------------------\n");
// 		info_lexer = info_lexer->next;
// 	}
// 	fprintf(stderr, "\033[0m");
// 	return ;
// }
//
// void	print_debug_info(t_lexer *head)
// {
// 	printing_lexer(head);
// 	print_cmd_lst(head);
// }

void	print_double_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i++])
	{
		if (arr[i])
		{
			ft_putstr_fd(arr[i], STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
	}
}
