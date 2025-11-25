#include "libft.h"

static char	*ft_simple_join(char const *s1, char const *s2)
{
	char	*res;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		res[i++] = s1[j++];
	j = 0;
	while (s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	return (res);
}

char	*ft_strjoin_with_slash(char const *s1, char const *s2)
{
	char	*tmp;
	char	*result;

	tmp = ft_simple_join(s1, "/");
	if (!tmp)
		return (NULL);
	result = ft_simple_join(tmp, s2);
	free(tmp);
	return (result);
}