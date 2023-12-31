/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: seyildir <seyildir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/30 15:49:51 by seyildir      #+#    #+#                 */
/*   Updated: 2023/04/06 10:03:51 by seyildir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	ft_free2m(char	**data, size_t word)
{
	size_t	i;

	i = 0;
	while (i <= word)
	{
		if (data[i])
			free(data[i]);
		i++;
	}
	free(data);
}

static int	word_count(char const *s, char c)
{
	int	rtn;

	rtn = 0;
	while (*s)
	{
		if (*s != c && (*(s + 1) == c || !*(s + 1)))
			rtn++;
		s++;
	}
	return (rtn);
}

static int	word_len(char const *s, char c)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (*s == c)
		s++;
	while (*s != c && *s)
	{
		i++;
		s++;
	}
	return (i);
}

static int	word_fill(char const *s, char c, char **d, size_t w_amount)
{
	size_t	i;
	size_t	word;
	size_t	s_size;
	size_t	s_sub;

	i = 0;
	word = 0;
	s_size = ft_strlen(s);
	while (word < w_amount)
	{
		while (s[i] == c && i < s_size)
			i++;
		s_sub = word_len(&s[i], c);
		d[word] = ft_substr(s, i, s_sub);
		if (d[word] == 0)
		{
			ft_free2m(d, w_amount);
			return (-1);
		}
		word++;
		i += s_sub;
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**rtn;
	int		w_amount;

	if (!s)
		return (0);
	w_amount = word_count(s, c);
	rtn = (char **)ft_calloc(w_amount + 1, sizeof(char *));
	if (!rtn)
		return (0);
	if (word_fill((char *)s, c, rtn, w_amount) == -1)
		return (0);
	return (rtn);
}
