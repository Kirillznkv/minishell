/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 17:56:35 by kshanti           #+#    #+#             */
/*   Updated: 2021/05/17 22:05:18 by kshanti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_parser/parser.h"

void		check_single_quotes(char *str, int *i)
{
	if (str[*i] != '\'')
		return ;
	(*i)++;
	while (str[*i] && !(str[*i] == '\'' && str[*i - 1] != '\\'))
		(*i)++;
	if (!str[*i])
		error_control("Single quote not closed");
}

void		check_double_quotes(char *str, int *i)
{
	if (str[*i] != '\"')
		return ;
	(*i)++;
	while (str[*i] && !(str[*i] == '\"' && str[*i - 1] != '\\'))
		(*i)++;
	if (!str[*i])
		error_control("Double quote not closed");
}

void		preparser(char *commands_line)
{
	int		i;

	i = -1;
	if (commands_line[ft_strlen(commands_line) - 1] == '\\')
		error_control("Back slash at the end of the line");
	while (commands_line[++i])
	{
		check_single_quotes(commands_line, &i);
		check_double_quotes(commands_line, &i);
	}
}

void		skip_spases_tabs(char *str, int *i)
{
	while (str[*i] == ' ' || str[*i] == '\t')
		(*i)++;
}

void		delete_single_quotes(char **p_command_line, size_t beg_sin, size_t end_sin)
{
	char	*first_part;
	char	*second_part;
	char	*third_part;
	char	*save_to_free;

	first_part = ft_substr(*p_command_line, 0, beg_sin);
	second_part = ft_substr(*p_command_line, beg_sin + 1, end_sin - beg_sin);
	third_part = ft_substr(*p_command_line, end_sin + 1, -1);
	free(*p_command_line);
	*p_command_line = ft_strjoin(first_part, second_part);
	save_to_free = *p_command_line;
	*p_command_line = ft_strjoin(*p_command_line, third_part);
	free(first_part);
	free(second_part);
	free(third_part);
	free(save_to_free);
}

void		replace_single_quotes(char **p_command_line, size_t *begin_single)
{
	size_t	end_single;
	char	*command_line;

	command_line = *p_command_line;
	if (command_line[*begin_single] != '\'')
		return ;
	end_single = *begin_single + 1;
	while (command_line[end_single] != '\'')
		end_single++;
	delete_single_quotes(p_command_line, *begin_single, end_single);
	*begin_single = end_single - 1; // + 1(next) - 2(quotes)
}

int			replace_undefine_dollar(char **p_command_line, size_t *beg_dollar)
{
	size_t	i;
	char	*command_line;
	char	*first_part;
	char	*second_part;

	command_line = *p_command_line;
	i = *beg_dollar + 1;
	if (command_line[i] != '@' && command_line[i] != '*' &&
		command_line[i] != '$' && command_line[i] != '!' &&
		command_line[i] != '-' && command_line[i] != '_' &&
		command_line[i] != '#' && ft_isdigit(command_line[i]))
		return (0);
	first_part = ft_substr(*p_command_line, 0, *beg_dollar);
	second_part = ft_substr(*p_command_line, *beg_dollar + 2, -1);
	free(*p_command_line);
	*p_command_line = ft_strjoin(first_part, second_part);
	free(first_part);
	free(second_part);
	*beg_dollar = *beg_dollar - 1;
	return (1);
}

int			replace_only_one_dollar(char **p_command_line, size_t *beg_dollar)
{
	size_t	i;
	char	*command_line;

	command_line = *p_command_line;
	i = *beg_dollar + 1;
	if (ft_isalpha(command_line[i]))
		return (0);
	(*beg_dollar)++;
	return (1);
}

int			check_env_word(char *env_line, char *dollar_word)
{
	if (env_line[ft_strlen(dollar_word)] == '=')
		return (1);
	return (0);
}

char		*get_second_env_word(char *env_line)
{
	size_t	i;
	char	*second_env_word;

	i = 0;
	while (env_line[i] != '=')
		i++;
	second_env_word = ft_substr(env_line, i + 1, -1);
	return (second_env_word);
}

char		*get_new_dollar_word(char **env, char *dollar_word)
{
	char	*env_line;
	char	*new_dollar_word;

	env_line = *env;
	while (*env_line)
	{
		if (ft_strnstr(*env_line, dollar_word, -1) &&
			check_env_word(env_line, dollar_word))
		{
			new_dollar_word = get_second_env_word(env_line);
			return (new_dollar_word);
		}
		env_line++;
	}
	return (NULL);
}

void		replace_dollar_word(char **p_command_line, char *new_dollar_word, int beg_dollar, int end_dollar_word)
{
	char	*first_part;
	char	*last_part;
	char	*save_to_free;

	first_part = ft_substr(*p_command_line, 0, beg_dollar);
	last_part = ft_substr(*p_command_line, end_dollar_word + 1, -1);
	free(*p_command_line);
	*p_command_line = ft_strjoin(first_part, new_dollar_word);
	save_to_free = *p_command_line;
	*p_command_line = ft_strjoin(*p_command_line, last_part);
	free(save_to_free);
	free(first_part);
	free(last_part);
}

void		replace_dollar_from_env(char **p_command_line, char **env, size_t *beg_dollar)
{
	size_t	end_dollar_word;
	char	*command_line;
	char	*dollar_word;
	char	*new_dollar_word;

	command_line = *p_command_line;
	end_dollar_word = *beg_dollar + 1;
	while (command_line[end_dollar_word] == '_' || ft_isalpha(command_line[end_dollar_word]))
		end_dollar_word++;
	dollar_word = ft_substr(command_line, *beg_dollar + 1, end_dollar_word - *beg_dollar + 1);
	new_dollar_word = get_new_dollar_word(env, dollar_word);
	free(dollar_word);
	replace_dollar_word(p_command_line, new_dollar_word, *beg_dollar, end_dollar_word);
	free(new_dollar_word);
}

void		replace_dollar(char **p_command_line, char **env, size_t *begin_dollar) // need $?
{
	char	*command_line;

	command_line = *p_command_line;
	if (command_line[*begin_dollar] != '$')
		return ;
	if (replace_undefine_dollar(p_command_line, begin_dollar))
		return ;
	if (replace_only_one_dollar(p_command_line, begin_dollar))
		return ;
	replace_dollar_from_env(p_command_line, env, begin_dollar);
}

t_commands	*get_one_command(char **p_commands_line, char **env)
{
	size_t		i;
	t_commands	*command;
	char		*command_line;

	command = (t_commands*)malloc(sizeof(t_commands));
	command->args = NULL;
	command->next = NULL;
	command_line = *p_commands_line;
	i = 0;
	skip_spases_tabs(command_line, &i);
	while (command_line[i] && command_line[i] != '\n' && command_line[i] != ';')
	{
		replace_single_quotes(&command_line, &i);//       '
		replace_double_quotes(&command_line, env, &i);//  "
		replace_dollar(&command_line, env, &i);//         $
		replace_normal_char(&command_line, &i);//         word
		check_end_word(&command_line, &i, command);
	}
}

t_commands	*parser(char *commands_line, char **env)
{
	t_commands		*first;

	if (!commands_line)
		error_control("Commands line is NULL");
	preparser(commands_line);
	while (*commands_line)
	{
		ft_lstadd_back(&first, get_one_command(&commands_line, env));
	}
	return (NULL);
}