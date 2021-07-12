/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-bour <rel-bour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 13:26:07 by rel-bour          #+#    #+#             */
/*   Updated: 2021/07/12 19:22:01 by rel-bour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head.h"

t_cmds	*all_t(void)
{
	static t_cmds	all;
	return (&all);
}

void initil_strct()
{
	t_cmds *cmds;

    cmds = all_t();
	cmds->line = NULL;
	cmds->cmd = NULL;
	cmds->type = NULL;
	cmds->arguments = NULL;
	cmds->option = 0;
}
char	*ft_strjoin1(char *s1, char *s2)
{
	size_t	size;
	char	*str;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!s1)
		return ((str = ft_strdup(s2)));
	size = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * size + 1);
	if (!str)
		return (NULL);
	while (s1[++i] != '\0')
		str[i] = s1[i];
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

char	*my_substr(char *s, int start, int end)
{
	char	*str;
	int		j;
	int		i;

	if (!s)
		return (NULL);
	str = (char *)malloc(end - start + 1);
	if (!str)
		return (NULL);
	j = 0;
	i = start;
	while (s[i] != '\0' && i < end)
	{
		str[j] = s[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}
char	*my_substr2(char *s, int start, int end)
{
	char	*str;
	int		j;
	int		i;

	if (!s)
		return (NULL);
	str = (char *)malloc(end - start + 1);
	if (!str)
		return (NULL);
	j = 0;
	i = start;
	while (s[i] != '\0' && i < end)
	{
		str[j] = s[i];
		i++;
		j++;
	}
	str[j] = '\0';
	free(s);
	return (str);
}

char	*ft_strdup(const char *s1)
{
	char	*p;
	int		i;
	int		x;

	x = ft_strlen(s1);
	i = 0;
	p = (char *)malloc(x + 1 * sizeof(char));
	if (p == NULL)
		return (NULL);
	while (i < x)
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

size_t	ft_strlen(char const *str)
{
	size_t	x;

	x = 0;
	if (str == NULL)
		return (0);
	while (str[x] != '\0')
		x++;
	return (x);
}

t_cmds	*new_commands(void)
{
	// t_cmds	*commands;
	
	// commands = all_t();

	// commands->command = NULL;
	// commands->type = NULL;
	// commands->arguments = NULL; 
	// commands->all = NULL;
	// // commands->filerdr = NULL;
	// // commands->path = NULL;
	// // commands->next = NULL;
	// commands->next_p = NULL;
	// commands->option = 0;
	// return (commands);

	t_cmds	*commands;

	commands = malloc(sizeof(t_cmds));
	if (!commands)
		return (NULL);
	commands->command = NULL;
	commands->type = NULL;
	commands->arguments = NULL;
	commands->all = NULL;
	commands->filerdr = NULL;
	// commands->path = NULL;
	// commands->next = NULL;
	commands->next_p = NULL;
	commands->option = 0;
	return (commands);
}

void main_parsing(char **envs)
{
    t_cmds *cmds;
	t_env		*evp;
	
	evp = malloc(sizeof(t_env));
	initsial_envs(&evp, envs);
    // cmds = new_commands();
	cmds = new_commands();
	cmds->line = readline("minishell$> ");

	
    get_commands(evp, &cmds, cmds->line);	

	
	
	add_history(cmds->line);
	// free(cmds->line);
}
