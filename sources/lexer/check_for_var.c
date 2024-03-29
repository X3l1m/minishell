/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_for_var.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: seyildir <seyildir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/04 13:03:08 by seyildir      #+#    #+#                 */
/*   Updated: 2024/03/04 13:03:10 by seyildir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	var_check(t_token **node)
{
	int	i;

	i = 0;
	while ((*node)->string[i])
	{
		if ((*node)->string[i] == '$')
		{
			if ((*node)->prev && (*node)->prev->type == HEREDOC)
				break ;
			(*node)->type = VAR;
			return ;
		}
		i++;
	}
}

static bool	consecutives(t_token *node)
{
	if (node->prev)
	{
		if (node->type == PIPE && node->prev->type == PIPE)
			return (true);
		if (node->type > PIPE && node->prev->type > PIPE)
			return (true);
		if (node->type == END && node->prev->type >= PIPE)
			return (true);
	}
	return (false);
}

bool	check_for_consecutives(t_token **list)
{
	t_token	*temp;

	temp = *list;
	while (temp)
	{
		if (consecutives(temp) == true)
		{
			if (temp->type == END && temp->prev && temp->prev->type > PIPE)
				print_error_msg("newline");
			else if (temp->type == END && temp->prev)
				print_error_msg(temp->prev->string);
			else
				print_error_msg(temp->string);
			return (true);
		}
		temp = temp->next;
	}
	return (false);
}

bool	check_for_var(t_token **t_list)
{
	t_token	*temp;

	temp = *t_list;
	if (temp->type == PIPE)
	{
		print_error_msg(temp->string);
		return (false);
	}
	while (temp)
	{
		var_check(&temp);
		if (check_for_consecutives(&temp) == true)
			return (false);
		temp = temp->next;
	}
	return (true);
}
