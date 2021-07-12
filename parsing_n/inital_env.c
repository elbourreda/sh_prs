/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inital_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-bour <rel-bour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 17:51:48 by rel-bour          #+#    #+#             */
/*   Updated: 2021/07/12 17:56:02 by rel-bour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head.h"

int	len_of_args(char **args)
{
	int		i;

	i = 0;
	while (args[i] != NULL)
		i++;
	return (i);
}

char	**copy_envp(char **envp_l)
{
	char	**tmpr;
	int		lenp;
	int		z;

	lenp = len_of_args(envp_l);
	tmpr = malloc(sizeof(char *) * (lenp + 1));
	tmpr[lenp] = NULL;
	z = -1;
	while (envp_l[++z])
	{
		tmpr[z] = ft_strdup(envp_l[z]);
	}
	return (tmpr);
}
char	*get_env_name(char *envp)
{
	int		b;
	int		c;
	char	*varibale;

	b = 0;
	c = 0;
	while (envp[b])
	{
		if (envp[b] == '=')
			break ;
		b++;
	}
	varibale = malloc(sizeof(char) * b + 1);
	while (c != b)
	{
		varibale[c] = envp[c];
		c++;
	}
	varibale[c] = '\0';
	return (varibale);
}

int	my_strcmp(char *s1, char *s2)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	if (!s1 || !s2)
		return (1);
	while (1)
	{
		if (s1[++i] != s2[++j])
			return (1);
		if (s1[i] == '\0' || s2[j] == '\0')
			break ;
	}
	return (0);
}

char	*half_h_search(char **envp, t_norm norm)
{
	norm.j += 1;
	while (envp[norm.i][norm.j])
	{
		norm.fsf[0] = envp[norm.i][norm.j];
		norm.buff = ft_strjoin1(norm.buff, norm.fsf);
		norm.j++;
	}
	return (norm.buff);
}

char	*half_search(char *variable, char **envp, t_norm norm)
{
	while (++norm.i < norm.lenp)
	{
		norm.tmp33 = get_env_name(envp[norm.i]);
		if (my_strcmp(norm.tmp33, variable) == 0)
		{
			norm.j = 0;
			while (envp[norm.i][norm.j])
			{
				if (envp[norm.i][norm.j] == '=')
				{
					norm.buff = half_h_search(envp, norm);
					free(norm.tmp33);
					return (norm.buff);
				}
				norm.j++;
			}
			free(norm.buff);
			norm.buff = ft_strdup("k");
			free(norm.tmp33);
			return (norm.buff);
		}
		free(norm.tmp33);
	}
	return (norm.buff);
}


static int	numblen(long long number)
{
	int			len;

	len = 0;
	if (number < 0)
	{
		number *= -1;
		len++;
	}
	if (number == 0)
	{
		len++;
	}
	while (number > 0)
	{
		number /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa1(int nbr)
{
	t_libftn	lib;

	lib.i = numblen(nbr);
	lib.n = 0;
	lib.x = nbr;
	lib.str = (char *)malloc(sizeof(char) * lib.i + 1);
	if (lib.str == NULL)
		return (NULL);
	lib.str[lib.i] = '\0';
	if (nbr < 0)
	{
		lib.str[0] = '-';
		lib.x = lib.x * -1;
		lib.n = 1;
	}
	lib.i--;
	while ((lib.i > 0 && lib.n == 1) || (lib.i >= 0 && lib.n == 0))
	{
		lib.str[lib.i] = lib.x % 10 + 48;
		lib.x /= 10;
		lib.i--;
	}
	return (lib.str);
}

char	*search_in_env2(char *variable, char **envp)
{
	t_norm	norm;

	norm.j = 0;
	norm.fsf = ft_strdup(" ");
	norm.buff = ft_strdup("");
	norm.lenp = len_of_args(envp);
	norm.i = -1;
	norm.buff = half_search(variable, envp, norm);
	free(norm.fsf);
	return (norm.buff);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	save;
	int	x;

	x = 1;
	i = 0;
	save = 0;
	while (str[i] == 32 || str[i] == 9 || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-' && str[i + 1] != '+')
	{
		x = -1;
		i++;
	}
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		save = save * 10 + (str[i] - 48);
		i++;
	}
	return (save * x);
}

char	**half_edit_envp(char **envp_c, t_norm norm)
{
	int	j;

	j = 0;
	while (envp_c[norm.i][j])
	{
		if (envp_c[norm.i][j] == '=')
		{
			j += 1;
			while (norm.tee != norm.t)
			{
				envp_c[norm.i][j] = norm.newsh[norm.tee];
				j++;
				norm.tee++;
			}
			envp_c[norm.i][j] = '\0';
			free(norm.n_tmp);
			return (envp_c);
		}
		j++;
	}
	return (envp_c);
}

char	**edit_envp_shlvl(char **envp_c)
{
	int		lenp;
	t_norm	norm;

	norm.sh = search_in_env2("SHLVL", envp_c);
	norm.newsh = ft_itoa1(ft_atoi(norm.sh) + 1);
	free(norm.sh);
	lenp = len_of_args(envp_c);
	norm.tee = 0;
	norm.t = ft_strlen(norm.newsh);
	norm.i = -1;
	while (++norm.i < lenp)
	{
		norm.n_tmp = get_env_name(envp_c[norm.i]);
		if (my_strcmp(norm.n_tmp, "SHLVL") == 0)
		{
			envp_c = half_edit_envp(envp_c, norm);
			free(norm.newsh);
			return (envp_c);
		}
		free(norm.n_tmp);
	}
	free(norm.newsh);
	return (envp_c);
}

char	**half(char **envp_c, t_norm norm)
{
	norm.j += 1;
	while (norm.tee != norm.t)
	{
		envp_c[norm.i][norm.j] = norm.v[norm.tee];
		norm.j++;
		norm.tee++;
	}
	envp_c[norm.i][norm.j] = '\0';
	free(norm.nameenv);
	return (envp_c);
}

char	**half_v_edit(char **envp_c, t_norm norm)
{
	while (++norm.i < norm.lenp)
	{
		norm.nameenv = get_env_name(envp_c[norm.i]);
		if (my_strcmp(norm.nameenv, "_") == 0)
		{
			norm.j = 0;
			while (envp_c[norm.i][norm.j])
			{
				if (envp_c[norm.i][norm.j] == '=')
				{
					envp_c = half(envp_c, norm);
					return (envp_c);
				}
				norm.j++;
			}
		}
		free(norm.nameenv);
	}
	return (envp_c);
}
char	**edit_envp_v(char **envp_c)
{
	t_norm	norm;

	norm.v = "./minishell";
	norm.lenp = len_of_args(envp_c);
	norm.t = ft_strlen(norm.v);
	norm.tee = 0;
	norm.i = -1;
	envp_c = half_v_edit(envp_c, norm);
	return (envp_c);
}

char	**edit_envp_old_pwd(char **envp_c)
{
	char	*nameenv;
	int		lenp;
	int		i;

	i = -1;
	lenp = len_of_args(envp_c);
	while (++i < lenp)
	{
		nameenv = get_env_name(envp_c[i]);
		if (my_strcmp(nameenv, "OLDPWD") == 0)
		{
			free(envp_c[i]);
			envp_c[i] = ft_strdup("OLDPWD");
			free(nameenv);
			break ;
		}
		free(nameenv);
	}
	return (envp_c);
}

void initsial_envs(t_env **evp, char **envs)
{
	(*evp)->my_env = copy_envp(envs);
	(*evp)->my_env = edit_envp_shlvl((*evp)->my_env);
	(*evp)->my_env = edit_envp_v((*evp)->my_env);
	(*evp)->my_env = edit_envp_old_pwd((*evp)->my_env);
	(*evp)->save = search_in_env2("HOME", (*evp)->my_env);
	(*evp)->check_term = getenv("TERM");
}