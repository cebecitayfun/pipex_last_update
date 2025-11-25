/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcebeci <tcebeci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 15:09:39 by tcebeci           #+#    #+#             */
/*   Updated: 2025/11/25 15:09:56 by tcebeci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* ft_split.c                                         :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: tcebeci <tcebeci@student.42.fr>            +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2025/11/25 15:03:13 by tcebeci           #+#    #+#             */
/* Updated: 2025/11/25 15:10:00 by tcebeci          ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *str, char sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != sep)
		{
			count++;
			while (str[i] && str[i] != sep)
				i++;
		}
		else
			i++;
	}
	return (count);
}

static char	**free_list(char **list, int i)
{
	while (i > 0)
	{
		i--;
		free(list[i]);
	}
	free(list);
	return (NULL);
}

static char	*word_dup(char const *str, int start, int finish)
{
	char	*word;
	int		i;

	word = malloc((finish - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

static char	**fill_result(char **result, char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		idx;

	i = 0;
	idx = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			j = i;
			while (s[i] && s[i] != c)
				i++;
			result[idx] = word_dup(s, j, i);
			if (!result[idx])
				return (free_list(result, idx));
			idx++;
		}
		else
			i++;
	}
	result[idx] = 0;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;

	if (!s)
		return (NULL);
	result = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	return (fill_result(result, s, c));
}
