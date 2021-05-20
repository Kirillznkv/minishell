/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 17:56:35 by kshanti           #+#    #+#             */
/*   Updated: 2021/05/19 22:20:51 by kshanti          ###   ########.fr       */
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

void		skip_spases_tabs(char **p_command_line, size_t begin)
{
	size_t	end;
	char	*command_line;
	char	*first_part;
	char	*last_part;
	char	*save_to_free;

	command_line = *p_command_line;
	end = begin;
	//printf("|%s|\n", &command_line[begin]);
	while (command_line[end] == ' ' || command_line[end] == '\t')
		end++;
	if (end == begin)
		return ;
	//printf("1\n");
	save_to_free = *p_command_line;
	first_part = ft_substr(*p_command_line, 0, begin);
	last_part = ft_substr(*p_command_line, end, -1);
	*p_command_line = ft_strjoin(first_part, last_part);
	free(save_to_free);
	free(first_part);
	free(last_part);
}

void		replace_spases_tabs_whis_spase(char **p_command_line, size_t *begin)
{
	char	*command_line;
	char	*first_part;
	char	*last_part;
	char	*save_to_free;

	command_line = *p_command_line;
	if (command_line[*begin] != ' ' && command_line[*begin] != '\t')
		return ;
	skip_spases_tabs(p_command_line, *begin);
	command_line = *p_command_line;
	if (command_line[*begin] == '\0')
		return ;
	save_to_free = *p_command_line;
	first_part = ft_substr(*p_command_line, 0, *begin);
	last_part = ft_substr(*p_command_line, *begin, -1);
	*p_command_line = ft_strjoin(first_part, " ");
	free(save_to_free);
	save_to_free = *p_command_line;
	*p_command_line = ft_strjoin(*p_command_line, last_part);
	free(save_to_free);
	free(first_part);
	free(last_part);
	(*begin)++;
}

void		delete_quotes(char **p_command_line, size_t beg_quotes, size_t end_quotes)
{
	char	*first_part;
	char	*second_part;
	char	*third_part;
	char	*save_to_free;

	first_part = ft_substr(*p_command_line, 0, beg_quotes);
	second_part = ft_substr(*p_command_line, beg_quotes + 1, end_quotes - beg_quotes - 1);
	third_part = ft_substr(*p_command_line, end_quotes + 1, -1);
	free(*p_command_line);
	*p_command_line = ft_strjoin(first_part, second_part);
	save_to_free = *p_command_line;
	*p_command_line = ft_strjoin(*p_command_line, third_part);
	free(first_part);
	free(second_part);
	free(third_part);
	free(save_to_free);
}

void		replace_single_quotes(char **p_command_line, size_t *begin_quotes)
{
	size_t	end_quotes;
	char	*command_line;

	command_line = *p_command_line;
	if (command_line[*begin_quotes] != '\'')
		return ;
	end_quotes = *begin_quotes + 1;
	while (command_line[end_quotes] != '\'')
		end_quotes++;
	//printf("|%s| start=%zu end=%zu\n", command_line, *begin_quotes, end_quotes);
	delete_quotes(p_command_line, *begin_quotes, end_quotes);
	//printf("|%s| start=%zu end=%zu\n", command_line, *begin_quotes, end_quotes);
	*begin_quotes = end_quotes - 1; // + 1(next) - 2(quotes)
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
		command_line[i] != '#' && !ft_isdigit(command_line[i]))
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
		if (ft_strnstr(env_line, dollar_word, -1) &&
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

void		replace_normal_char(char **p_command_line, size_t *i)
{
	char	*command_line;

	command_line = *p_command_line;
	while (command_line[*i] != ' ' && command_line[*i] != '\"' &&
		command_line[*i] != '$' && command_line[*i] != '\'' &&
		/*command_line[*i] != '|' && */command_line[*i] != '\t' &&
		command_line[*i] != ';' && command_line[*i] != '\0' &&
		command_line[*i] != '\n')
		(*i)++;
}

void		delete_one_char(char **str, size_t i_delete)
{
	char	*save_to_delete;
	char	*first_part;
	char	*last_part;

	save_to_delete = *str;
	first_part = ft_substr(*str, 0, i_delete);
	last_part = ft_substr(*str, i_delete + 1, -1);
	*str = ft_strjoin(first_part, last_part);
	free(save_to_delete);
	free(first_part);
	free(last_part);
}

void		replace_double_quotes(char **p_command_line, char **env, size_t *begin_quotes)
{
	size_t	end_quotes;
	char	*command_line;

	end_quotes = *begin_quotes + 1;
	command_line = *p_command_line;
	if (command_line[*begin_quotes] != '\"')
		return ;
	while (command_line[end_quotes] != '\"')
	{
		if (command_line[end_quotes] == '\\' && command_line[end_quotes + 1] != '\"' &&
												command_line[end_quotes + 1] != '\\' &&
												command_line[end_quotes + 1] != '$')
			end_quotes++;
		else if (command_line[end_quotes] == '$')
			replace_double_quotes(p_command_line, env, &end_quotes);
		else if (command_line[end_quotes] == '\\')
			delete_one_char(p_command_line, end_quotes);
		command_line = *p_command_line;
		end_quotes++;
	}
	delete_quotes(p_command_line, *begin_quotes, end_quotes);
	*begin_quotes = end_quotes - 1;
}

void		check_end_word(char **p_command_line, size_t *i, t_commands *command)///////////////////////
{
	char	*command_line;
	char	*save_to_free;

	command_line = *p_command_line;
	// if (command_line[*i] != ' '/* && command_line[i] != '\0' */&&//////
	// 	/*command_line[i] != '|' && */command_line[*i] != '\t')////////
	// 	return ;
	//command->args = ft_substr(*p_command_line, 0, i);////////
	replace_spases_tabs_whis_spase(p_command_line, i);
}

t_commands	*get_one_command(char **p_commands_line, char **env)
{
	size_t		i;
	t_commands	*command;
	char		*command_line;

	command = (t_commands*)malloc(sizeof(t_commands));
	command->args = NULL;
	command->next = NULL;
	i = 0;
	skip_spases_tabs(p_commands_line, i);
	command_line = *p_commands_line;
	while (command_line[i] && command_line[i] != '\n' && command_line[i] != ';')
	{
		//printf("|%s|\n", command_line);
		replace_single_quotes(&command_line, &i);//       '
		//write(1, "###\n", 4);
		replace_double_quotes(&command_line, env, &i);//  "
		replace_dollar(&command_line, env, &i);//         $
		replace_normal_char(&command_line, &i);//         word
		check_end_word(&command_line, &i, command);//     add || < > >> 
	}
	command->args = ft_substr(command_line, 0, i);
	if (command_line[i])
		*p_commands_line = &command_line[i] + 1;
	else
		*p_commands_line = &command_line[i];
	return (command);
}

t_commands	*parser(char *commands_line, char **env)
{
	t_commands		*first;

	if (!commands_line)
		error_control("Commands line is NULL");
	preparser(commands_line);
	first = NULL;
	while (*commands_line)
	{
		ft_lstadd_back(&first, get_one_command(&commands_line, env));
		printf("|%s|\n", first->args);
	}
	return (NULL);
}