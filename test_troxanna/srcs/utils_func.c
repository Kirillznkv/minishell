#include "../includes/minishell.h"


char	*ft_strnstr(const char *s, const char *find, size_t slen)
{
	size_t i;
	size_t j;

	i = 0;
	if (find[i] == '\0')
		return ((char *)s);
	while (i < slen && s[i])
	{
		j = 0;
		while (find[j] && s[i + j] == find[j] && s[i + j] && (i + j) < slen)
			j++;
		if (find[j] == '\0')
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}


int		ft_isalpha(int ch)
{
	if ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122))
		return (1);
	else
		return (0);
}

int					ft_strcmp(const char *str1, const char *str2)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	p1 = (unsigned char *)str1;
	p2 = (unsigned char *)str2;
	i = 0;
	while (p1[i] && p2[i] && p1[i] == p2[i])
		i++;
	return (p1[i] - p2[i]);
}

void		ft_putchar(char c)
{
	write(1, &c, sizeof(c));
}

int			ft_strlen(char *s)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void		ft_putstr(char *s)
{
	write(1, s, ft_strlen(s));
}

void		ft_error(int n)
{
	if (n == 1)
		printf("Недостаточное количество аргументов\n");
	else if (n == 2)
		printf("Команда не существует\n");
	else if (n == 2)
		printf("Ошибка выделения памяти\n");
	exit(EXIT_FAILURE);
}

char		*ft_strdup(char *str)
{
	char	*ptr;
	int		i;

	ptr = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	i = 0;
	if (ptr)
	{
		while (str[i] != '\0')
		{
			ptr[i] = str[i];
			i++;
		}
		ptr[i] = '\0';
		return (ptr);
	}
	else
		return (NULL);
}

void				ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*tmp;

	tmp = s;
	i = 0;
	while (i < n)
	{
		tmp[i] = '\0';
		i++;
	}
	s = tmp;
}
