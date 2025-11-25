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

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**result;

	if (!s)
		return (NULL);
	result = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	index = 0;
	while (i < ft_strlen(s))
	{
		if (s[i] != c)
		{
			j = i;
			while (s[i] && s[i] != c)
				i++;
			result[index] = word_dup(s, j, i);
			if (!result[index++])
				return (free_list(result, index - 1));
		}
		else // Norminette için else bloğu ekledik, i artsın diye.
			i++;
	}
	result[index] = 0;
	return (result);
}