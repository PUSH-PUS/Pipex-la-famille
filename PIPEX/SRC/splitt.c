/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:00:00 by user              #+#    #+#             */
/*   Updated: 2025/02/01 14:56:26 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	count_args(const char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		i = skip_whitespace(str, i);
		if (str[i])
		{
			count++;
			i = skip_arg(str, i);
		}
	}
	return (count);
}

static void	clean_quotes(char *str)
{
	int	i;
	int	j;
	int	in_quote;

	i = 0;
	j = 0;
	in_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			in_quote = !in_quote;
			i++;
		}
		str[j++] = str[i++];
	}
	str[j] = '\0';
}

static int	add_arg(t_arg_data *data, int idx)
{
	data->args[idx] = ft_substr(data->str, data->start, data->end
			- data->start);
	if (!data->args[idx])
		return (0);
	clean_quotes(data->args[idx]);
	return (1);
}

static int	process_argument(char **args, const char *str, int pos[3])
{
	t_arg_data	arg_data;

	arg_data.args = args;
	arg_data.str = str;
	arg_data.start = pos[2];
	arg_data.end = pos[0];
	return (add_arg(&arg_data, pos[1]++));
}

char	**split_command(const char *str)
{
	char	**args;
	int		pos[3];
	int		count;

	initialize_positions_forsplitdemesc(pos);
	count = count_args(str);
	args = ft_calloc(count + 1, sizeof(char *));
	if (!args)
		return (NULL);
	while (str[pos[0]] && pos[1] < count)
	{
		pos[0] = skip_whitespace(str, pos[0]);
		pos[2] = pos[0];
		pos[0] = skip_arg(str, pos[0]);
		if (pos[0] > pos[2] && !process_argument(args, str, pos))
		{
			ft_free_split(args);
			return (NULL);
		}
	}
	return (args);
}
