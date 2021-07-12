/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_pars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-bour <rel-bour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 18:08:59 by rel-bour          #+#    #+#             */
/*   Updated: 2021/07/12 19:30:49 by rel-bour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head.h"

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

char	*ft_itoa(int nbr)
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

int	spcle_chr(char c)
{
	if (c == 34 || c == 39 || c == '\\')
		return (1);
	return (0);
}

int	skip_double_coats(char *cmds, int *i)
{
	while (cmds[++(*i)])
	{
		if (cmds[*i] == '\\' && spcle_chr(cmds[(*i) + 1]))
			(*i)++;
		else if (cmds[*i] == 34)
			return (0);
	}
	return (1);
}

int	skip_single_coats(char *cmds, int *i)
{
	while (cmds[++(*i)])
		if (cmds[*i] == 39)
			return (0);
	return (1);
}

int	norm_g_cmd0(int *i, t_cmds *commands, char *cmds)
{
	if (cmds[++(*i)] == 34)
	{
		commands->multiple = skip_double_coats(cmds, i);
		if (commands->multiple)
			return (0);
	}
	else if (cmds[*i] == 39)
	{
		commands->multiple = skip_single_coats(cmds, i);
		if (commands->multiple)
			return (0);
	}
	return (1);
}

void	norm_deletespace(char *str, int *i, int *size, int *start)
{
	*i = -1;
	*size = ft_strlen(str);
	while (++(*i) < (*size))
	{
		if (str[*i] != ' ')
		{
			*start = *i;
			break ;
		}
	}
}

int	get_last_space(char *str, int i)
{
	while (1)
	{
		if (str[i] != '\\' || i == 0)
			break ;
		i--;
	}
	if (str[i] != '\\')
		i++;
	while (str[i])
	{
		if (str[i] == '\\')
			i++;
		else
			break ;
		i++;
	}
	return (--i);
}

char	*get_right_path(char *str, int start, int end)
{
	int		i;
	int		j;
	char	*path;

	path = malloc((sizeof(char) * (end - start)) + 2);
	if (!path)
		return (NULL);
	i = start - 1;
	j = 0;
	while (++i <= end)
	{
		path[j] = str[i];
		j++;
	}
	path[j] = '\0';
	free(str);
	return (path);
}

char	*deletespace(char *str)
{
	int	size;
	int	i;
	int	start;
	int	end;

	start = -1;
	end = -1;
	if (!str)
		return (NULL);
	norm_deletespace(str, &i, &size, &start);
	i = size;
	while (--i >= 0)
	{
		if (str[i] != ' ')
		{
			if (str[i] == '\\')
				end = get_last_space(str, i);
			else
				end = i;
			break ;
		}
	} 
	if (start == -1 || end == -1)
		return (ft_strdup(""));
	return (get_right_path(str, start, end));
}

t_norm	*new_norm2(t_env *evp, t_cmds *commands)
{
	t_norm	*n;

	n = malloc(sizeof(t_norm));
	n->start = 0;
	n->tmp = commands;
	n->evp = evp; 
	n->cmd = ft_strdup(commands->command);
	return (n);
} 

int	checkdbl_sngl_c(t_cmds *commands, char *cmd, int *i)
{
	if (cmd[++(*i)] == 34)
	{
		commands->multiple = skip_double_coats(cmd, &(*i));
		if (commands->multiple)
			return (0);
	}
	else if (cmd[(*i)] == 39)
	{
		commands->multiple = skip_single_coats(cmd, &(*i));
		if (commands->multiple)
			return (0);
	}
	return (1);
}

t_rdr	*newcmd_rdr(void)
{
	t_rdr	*r;

	r = malloc(sizeof(t_rdr));
	r->b = 0;
	r->k = 0;
	r->i = -1;
	r->start = 0;
	return (r);
}

int	norm_deleterdr(char *command, int *i, char *s, char **comd)
{
	if (command[++(*i)] == '\\')
	{
		s[0] = command[*i];
		*comd = ft_strjoin1(*comd, s);
		(*i)++;
		s[0] = command[*i];
		*comd = ft_strjoin1(*comd, s);
		return (1);
	}
	return (0);
}

int	skip_filename(char *cmds, int *i) 
{
	while (cmds[++(*i)])
		if (cmds[*i] != '>' && cmds[*i] != '<' && cmds[*i] != ' ')
			break ;
	while (*i < (int)ft_strlen(cmds))
	{
		if (cmds[*i] == 34)
			skip_double_coats(cmds, i);
		else if (cmds[*i] == 39)
			skip_single_coats(cmds, i);
		else if (cmds[*i] == '\\')
		{
			(*i) += 2;
			continue ;
		}
		if (cmds[*i] == '>' || cmds[*i] == '<'
			|| (cmds[*i] == ' ' && cmds[*i + 1] != ' '))
		{
			(*i)--;
			return (0);
		}
		(*i)++;
	}
	(*i)--;
	return (1);
}

char	*deleterdr(char *command)
{
	int		i;
	char	*comd;
	char	*s;

	s = ft_strdup(" ");
	comd = NULL;
	i = -1;
	while (1)
	{	
		if (norm_deleterdr(command, &i, s, &comd))
			continue ;
		else if (command[i] == '>' && command[i + 1] == '>')
			continue ;
		else if ((command[i] == '>' || command[i] == '<'))
			skip_filename(command, &i);
		else
		{
			s[0] = command[i];
			comd = ft_strjoin1(comd, s);
		}
		if (!command[i])
			break ;
	}
	free(s);
	return (comd);
}

void	half_convert(int *bl, t_tmp	**tmp)
{
	*bl = 0;
	*tmp = malloc(sizeof(t_tmp));
	(*tmp)->rstr = ft_strdup("");
	(*tmp)->i = -1;
	(*tmp)->dl = 0;
}
void	dbsg_norme(int *bl, char *cmds, t_tmp *tmp)
{
	if (tmp->dl == 0 && cmds[tmp->i] == '\"')
		tmp->dl = 2;
	else if (tmp->dl == 2 && cmds[tmp->i] == '\"')
		tmp->dl = 0;
	if (*bl == 0 && cmds[tmp->i] == '\'')
		*bl = 1;
	else if (*bl == 1 && cmds[tmp->i] == '\'')
		*bl = 0;
}

int	half_join_char(char *s, char c, char **str)
{
	if (s == NULL)
	{
		*str = (char *)malloc(2);
		if (*str == NULL)
			return (0);
		str[0][0] = c;
		str[0][1] = '\0';
		return (1);
	}
	return (-1);
}

char	*ft_strjoinchar(char *s, char c)
{
	int		i;
	char	*str;
	int		r;

	i = 0;
	r = half_join_char(s, c, &str);
	if (r == 1)
		return (str);
	else if (r == 0)
		return (NULL);
	while (s[i])
		i++;
	str = (char *)malloc(i + 2);
	if (str == NULL)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = c;
	str[i + 1] = '\0';
	free(s);
	return (str);
}

char	*n1_add_vrbs(int dl, char *str, t_tmp *tamp, char *typ)
{
	if (dl == 2 && (typ[tamp->k + 1] == 39 || typ[tamp->k + 1] == 34))
	{
		if (!str)
			return (ft_strdup("$"));
		else
		{
			tamp->test = ft_strdup("$");
			tamp->s = ft_strjoin1(str, tamp->test);
			free(tamp->test);
			return (tamp->s);
		}
	}
	if (typ[tamp->k + 1] == 39 || typ[tamp->k + 1] == 34)
	{
		if (!str)
			return (ft_strdup(""));
		else
		{
			tamp->test = ft_strdup("");
			tamp->s = ft_strjoin1(str, tamp->test);
			free(tamp->test);
			return (tamp->s);
		}
	}
	return (NULL);
}

char	*n2_add_vrbs(char *str, t_tmp *tamp, char *typ)
{
	if (typ[tamp->k + 1] == '\0' || typ[tamp->k + 1] == ' '
		|| typ[tamp->k + 1] == '\\')
	{
		if (!str)
		{
			return (ft_strdup("$"));
		}
		else
		{
			tamp->test = ft_strdup("$");
			tamp->s = ft_strjoin1(str, tamp->test);
			free(tamp->test);
			return (tamp->s);
		}
	}
	return (NULL);
}

char	*free_tmp2(t_tmp *tmp)
{
	char	*s;

	s = tmp->buff;
	free(tmp);
	return (s);
}
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	*ss;

	if (s1 == NULL || s2 == NULL)
		return (-1);
	s = (unsigned char *)s1;
	ss = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (s[i] != ss[i])
			return (s[i] - ss[i]);
		if (s[i] == '\0' || ss[i] == '\0')
			return (0);
		i++;
	}
	return (0);
}


t_tmp	*new_tmp_search(char **envp)
{
	t_tmp	*tmp;

	tmp = malloc(sizeof(t_tmp));
	tmp->i = -1;
	tmp->j = 0;
	tmp->lenp = len_of_args(envp);
	tmp->buff = ft_strdup("");
	tmp->fsf = ft_strdup(" ");
	return (tmp);
}

char	*norm_se_env(t_tmp *tmp, char **envp)
{
	tmp->j = 0;
	while (envp[tmp->i][tmp->j])
	{
		if (envp[tmp->i][tmp->j] == '=')
		{
			tmp->j += 1;
			while (envp[tmp->i][tmp->j])
			{
				tmp->fsf[0] = envp[tmp->i][tmp->j];
				tmp->buff = ft_strjoin1(tmp->buff, tmp->fsf);
				tmp->j++;
			}
			free(tmp->fsf);
			return (tmp->buff);
		}
		tmp->j++;
	}
	return (NULL);
}

char	*search_in_env(char *variable, char **envp)
{
	t_tmp	*tmp;

	tmp = new_tmp_search(envp);
	variable = ft_strjoin1(variable, "=");
	while (++tmp->i < tmp->lenp)
	{
		if (ft_strncmp(envp[tmp->i], variable, ft_strlen(variable)) == 0)
		{
			if (norm_se_env(tmp, envp))
			{
				free(variable);
				return (free_tmp2(tmp));
			}
		}
	}
	free(variable);
	free(tmp->fsf);
	free(tmp->buff);
	free(tmp);
	return (NULL);
}

void	norm_add_v(char **envp, t_tmp *tamp, t_tmp *tmp, char *typ)
{
	char	*tmmp;

	tamp->test = my_substr(typ, tamp->k + 1, tmp->i);
	tmmp = tamp->test;
	tamp->test = search_in_env(tamp->test, envp);
	--(tmp->i);
} 

int	ft_isdigit(int number)
{
	if (number >= '0' && number <= '9')
	{
		return (1);
	}
	else
		return (0);
}

int	ft_isalpha(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
	{
		return (1);
	}
	else
		return (0);
}


int	syntax(char ch, int i)
{
	if ((ft_isalpha(ch) == 1 && i == 0) || (ch == '_' && i == 0))
	{
		return (1);
	}
	else if ((ft_isalpha(ch) == 1 && i != 0) || (ft_isdigit(ch) == 1 && i != 0))
		return (1);
	return (0);
}

char	*add_vrbs_norm(char **envp, t_tmp *tamp, t_tmp *tmp, char *typ)
{
	tamp->z = -1;
	while (1)  
	{
		if (!syntax(typ[++(tmp->i)], ++(tamp->z)) && tamp->z == 0)
		{
			tamp->test = my_substr(typ, tamp->k + 1, tmp->i + 1);
			tamp->test = search_in_env(tamp->test, envp);
			break ;
		}
		else if (!syntax(typ[tmp->i], tamp->z))
		{
			norm_add_v(envp, tamp, tmp, typ);
			break ;
		}
	}
	if (tamp->test)
	{
		tamp->ss = ft_strjoin1(tamp->ss, tamp->test);
		free(tamp->test);
	}
	return (tamp->ss);
}

char	*add_vrbs(char **envp, char *str, t_tmp *tmp, char *typ)
{
	t_tmp	*tamp;
	char	*s;

	tamp = malloc(sizeof(t_tmp));
	tamp->k = tmp->i;
	tamp->s1 = n1_add_vrbs(tmp->dl, str, tamp, typ);
	if (tamp->s1)
	{
		s = tamp->s1;
		free(tamp);
		return (s);
	}
	tamp->s1 = n2_add_vrbs(str, tamp, typ);
	if (tamp->s1)
	{
		s = tamp->s1;
		free(tamp);
		return (s);
	}
	tamp->ss = str;
	str = add_vrbs_norm(envp, tamp, tmp, typ);
	free(tamp);
	return (str);
}

int	norm_cnvr_vbs(int *bl, char *cmds, t_env *evp, t_tmp *tmp)
{
	if (*bl == 0 && cmds[tmp->i] == '\\' && cmds[tmp->i + 1] == '$')
	{
		tmp->rstr = ft_strjoinchar(tmp->rstr, '\\');
		tmp->rstr = ft_strjoinchar(tmp->rstr, '$');
		tmp->i++;
		return (1);
	}
	if (*bl == 0 && cmds[tmp->i] == '$' && cmds[tmp->i + 1] == '?')
	{
		tmp->ss = ft_itoa(g_all->staus_code);
		tmp->rstr = ft_strjoin1(tmp->rstr, tmp->ss);
		free(tmp->ss);
		tmp->i++;
	}
	else if (*bl == 0 && cmds[tmp->i] == '$')
		tmp->rstr = add_vrbs(evp->my_env, tmp->rstr, tmp, cmds);
	else
		tmp->rstr = ft_strjoinchar(tmp->rstr, cmds[tmp->i]);
	return (0);
}

char	*convert_vrbs(char *cmds, t_env *evp)
{
	t_tmp	*tmp;
	int		bl;

	if (!cmds)
		return (NULL);
	half_convert(&bl, &tmp);
	while (cmds[++tmp->i])
	{
		if (cmds[tmp->i] == '\\')
		{
			tmp->rstr = ft_strjoinchar(tmp->rstr, '\\');
			tmp->rstr = ft_strjoinchar(tmp->rstr, cmds[tmp->i + 1]);
			(tmp->i)++;
			continue ;
		}
		dbsg_norme(&bl, cmds, tmp);
		if (norm_cnvr_vbs(&bl, cmds, evp, tmp) == 1)
			continue ;
	}
	free(cmds);
	cmds = tmp->rstr;
	free(tmp);
	return (cmds);
}
 

int	loop_s_c_r(t_env *evp, t_cmds *commands, t_rdr *cmd_r)
{
	cmd_r->rdr_cmd = deleterdr(commands->command);
	if (!cmd_r->rdr_cmd || ft_strlen(cmd_r->rdr_cmd) == 0)
	{
		free(cmd_r->rdr_cmd);
		free(cmd_r);
		return (1);
	}
	cmd_r->rdr_cmd = convert_vrbs(cmd_r->rdr_cmd, evp);
	cmd_r->rdr_cmd = deletespace(cmd_r->rdr_cmd);
	if (!cmd_r->rdr_cmd || ft_strlen(cmd_r->rdr_cmd) == 0)
	{
		free(cmd_r);
		return (1);
	}
	return (0);
}

int	check_cmd(char *cmnd)
{
	int	i;

	i = -1;
	if (!cmnd)
		return (0);
	while (cmnd[++i])
	{
		if (cmnd[i] != ' ')
			return (1);
	}
	return (0);
}

int	nbr_argts2(char *command)
{
	int	i;
	int	cpt;

	cpt = 0;
	i = -1;
	if (!check_cmd(command))
		return (0);
	while (1)
	{
		if (command[++i] == 34)
			skip_double_coats(command, &i);
		else if (command[i] == 39)
			skip_single_coats(command, &i);
		else if (command[i] == '\\')
		{
			i++;
			continue ;
		}
		if (command[i] == ' ' && command[i + 1] != ' ')
			cpt++;
		if (!command[i])
			break ;
	}
	cpt++;
	return (cpt);
}

void	add_null(t_cmds *cmd, int nbr)
{
	int	i;

	i = -1;
	while (++i < nbr)
	{
		cmd->all[i] = NULL; 
	}
	i = -1;
	while (++i < nbr - 1)
	{
		cmd->arguments[i] = NULL;
	}
}

int	skp_sng_db_c_n(t_rdr *cmd_r)
{
	if ((cmd_r->rdr_cmd[++(cmd_r->i)] == 34 && cmd_r->i == 0)
		|| (cmd_r->rdr_cmd[cmd_r->i] == 34
			&& cmd_r->rdr_cmd[cmd_r->i - 1] != '\\'))
	{
		skip_double_coats(cmd_r->rdr_cmd, &cmd_r->i);
		return (1);
	}
	else if ((cmd_r->rdr_cmd[cmd_r->i] == 39 && cmd_r->i == 0)
		|| (cmd_r->rdr_cmd[cmd_r->i] == 39
			&& cmd_r->rdr_cmd[cmd_r->i - 1] != '\\'))
	{
		skip_single_coats(cmd_r->rdr_cmd, &cmd_r->i);
		return (1);
	}
	return (0);
}
char	*free_ret(t_tmp	*tmp)
{
	char	*s;

	s = tmp->rstr;
	free(tmp->s1);
	free(tmp);
	return (s);
}

int	norm_getdbc(char **rstr, char *str, t_tmp *tmp)
{
	char	*ss;

	if (str[tmp->i] == '\\' && str[tmp->i + 1] == '$')
	{
		*rstr = ft_strjoinchar(*rstr, '$');
		tmp->i++;
		return (1);
	}
	if (str[tmp->i] == '$' && str[tmp->i + 1] == '?')
	{
		ss = ft_itoa(g_all->staus_code);
		*rstr = ft_strjoin1(*rstr, ss);
		free(ss);
		tmp->i++;
		return (1);
	}
	return (0);
}

char	*getdblcoat(char *rstr, char *str, t_tmp *tmp)
{
	if (str[tmp->i + 1] == 34)
	{
		tmp->i++;
		tmp->s1[0] = '\0';
		rstr = ft_strjoin1(rstr, tmp->s1);
		return (rstr);
	}
	while (str[++(tmp->i)])
	{
		if (norm_getdbc(&rstr, str, tmp))
			continue ;
		if (str[tmp->i] == '\\'
			&& (str[tmp->i + 1] == '\\' || str[tmp->i + 1] == 34))
		{
			tmp->s1[0] = str[tmp->i + 1];
			rstr = ft_strjoin1(rstr, tmp->s1);
			(tmp->i)++;
			continue ;
		}
		if (str[tmp->i] == 34)
			break ;
		tmp->s1[0] = str[tmp->i];
		rstr = ft_strjoin1(rstr, tmp->s1);
	}
	return (rstr);
}
 
char	*getsglcoat(char *rstr, char *str, t_tmp *tmp)
{
	if (str[tmp->i + 1] == 39)
	{
		tmp->i++;
		tmp->s1[0] = '\0';
		rstr = ft_strjoin1(rstr, tmp->s1);
		return (rstr);
	}
	while (str[++(tmp->i)])
	{
		if (str[tmp->i] == 39)
			break ;
		tmp->s1[0] = str[tmp->i];
		rstr = ft_strjoin1(rstr, tmp->s1);
	}
	return (rstr);
}


int	norm_deletcoats(char *str, t_tmp	*tmp)
{
	if (str[tmp->i] == '\\')
	{
		tmp->s1[0] = str[tmp->i + 1];
		tmp->rstr = ft_strjoin1(tmp->rstr, tmp->s1);
		(tmp->i)++;
		return (1);
	}
	if (str[tmp->i] == 34)
	{
		tmp->rstr = getdblcoat(tmp->rstr, str, tmp);
		return (1);
	}
	if (str[tmp->i] == 39)
	{
		tmp->rstr = getsglcoat(tmp->rstr, str, tmp);
		return (1);
	}
	return (0);
}
char	*deletecoats(char *str)
{
	t_tmp	*tmp;

	tmp = malloc(sizeof(t_tmp));
	tmp->s1 = malloc(2);
	tmp->s1[1] = '\0';
	tmp->i = -1;
	tmp->j = 0;
	tmp->rstr = NULL;
	while (str[++(tmp->i)])
	{
		if (norm_deletcoats(str, tmp))
			continue ;
		tmp->s1[0] = str[tmp->i];
		tmp->rstr = ft_strjoin1(tmp->rstr, tmp->s1);
		tmp->j++;
	}
	free(str);
	return (free_ret(tmp));
} 

int	check_echo_n(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (s[i] != '-')
		return (1);
	while (s[++i])
	{
		if (s[i] != 'n')
			return (1);
	}
	free(s);
	return (0);
}

void	nrm_rdr_args(t_rdr	*cmd_r, t_cmds *commands)
{
	cmd_r->str = my_substr(cmd_r->rdr_cmd, cmd_r->start, cmd_r->i + 1);
	cmd_r->str = deletespace(cmd_r->str);
	cmd_r->str = deletecoats(cmd_r->str); 
	if (cmd_r->str)
	{
		if (cmd_r->b == 1 || my_strcmp(commands->type, "echo") == 1
			|| (my_strcmp(commands->type, "echo") == 0
				&& check_echo_n(cmd_r->str) == 1))
		{
			commands->arguments[cmd_r->k] = cmd_r->str;
			cmd_r->k++;
			commands->all[cmd_r->k] = commands->arguments[cmd_r->k - 1];
			cmd_r->b = 1;
		}
		else if (cmd_r->b == 0)
			commands->option = 1;
	}
}
 
int	rdr_norm_cmd(t_rdr *cm_r, t_cmds *commands)
{
	if (cm_r->rdr_cmd && !skp_sng_db_c_n(cm_r) && cm_r->rdr_cmd[cm_r->i] == '\\')
	{
		(cm_r->i)++;
		return (1);
	}
	if ((cm_r->rdr_cmd[cm_r->i] == ' ' && cm_r->rdr_cmd[cm_r->i + 1] != ' ')
		|| cm_r->rdr_cmd[cm_r->i] == '\0')
	{
		if (!commands->type)
		{
			commands->type = my_substr(cm_r->rdr_cmd, cm_r->start, cm_r->i + 1);
			commands->type = deletespace(commands->type);
			commands->type = deletecoats(commands->type); 
			if (!commands->type)
				commands->type = ft_strdup("\0");
			commands->all[0] = commands->type;
		}
		else
			nrm_rdr_args(cm_r, commands);
		cm_r->start = cm_r->i + 1;
	}
	if (cm_r->rdr_cmd[cm_r->i] == '\0')
		return (2);
	return (0);
}

void	split_command_rdr(t_env *evp, t_cmds *commands, int nbr_args)
{
	t_rdr	*cmd_r;
	int		t;

	cmd_r = newcmd_rdr();
	if (loop_s_c_r(evp, commands, cmd_r))
		return ;
	nbr_args = nbr_argts2(cmd_r->rdr_cmd);
	commands->arguments = malloc(sizeof(char *) * (nbr_args)); 
	commands->all = malloc(sizeof(char *) * (nbr_args + 1));
	add_null(commands, nbr_args + 1); 
	while (1)
	{
		t = rdr_norm_cmd(cmd_r, commands);
		if (t == 1)
			continue ;
		else if (t == 2)
			break ;
	}
	free(cmd_r->rdr_cmd);
	free(cmd_r);
}

t_filerdr	*new_files_rdr(void)
{
	t_filerdr	*f;

	f = malloc(sizeof(t_filerdr));
	f->error = 0;
	f->name = NULL;
	f->type = -1;
	f->next = NULL;
	return (f);
}

int	get_type_rdr(char *command, int i)
{
	if (command[i] == '>' && command[i + 1] == '>')
		return (2);
	else if (command[i] == '>')
		return (1);
	else if (command[i] == '<')
		return (0);
	return (-1);
}

char	*get_rdr_file(char *command, int i)
{
	int		start;

	i--;
	start = 0;
	while (command[++i])
	{
		if (command[i] == '>' || command[i] == '<' || command[i] == ' ')
			continue ;
		break ;
	}
	start = i;
	while (i < (int)ft_strlen(command))
	{	
		if (command[i] == 34)
			skip_double_coats(command, &i);
		else if (command[i] == 39)
			skip_single_coats(command, &i);
		else if (command[i] == '\\')
			i++;
		else if (command[i] == '>' || command[i] == '<' || command[i] == ' ')
			break ;
		i++; 
	}
	return (deletecoats(deletespace(my_substr(command, start, i))));
}

void	norm_f_rdr(t_cmds *commands, t_rdr *t_cmd, int *i)
{
	if (commands->command[*i] == 34)
		skip_double_coats(commands->command, i);
	else if (commands->command[*i] == 39)
		skip_single_coats(commands->command, i);
	else if (commands->command[*i] == '\\')
	{
		(*i)++;
		return ;
	}
	else if (commands->command[*i] == '>' || commands->command[*i] == '<')
	{
		if (!commands->filerdr)
		{
			commands->filerdr = new_files_rdr();
			t_cmd->tmp = commands->filerdr;
		}
		else
		{
			commands->filerdr->next = new_files_rdr();
			commands->filerdr = commands->filerdr->next;
		}
		commands->filerdr->type = get_type_rdr(commands->command, *i);
		commands->filerdr->name = get_rdr_file(commands->command, *i);
		skip_filename(commands->command, i);
	}
}

int	files_rdr(t_env *envp, t_cmds *commands)
{
	int		i;
	t_rdr	*t_cmd;
	char	*st;

	i = -1;
	st = commands->command;
	commands->command = convert_vrbs(commands->command, envp);
	t_cmd = malloc(sizeof(t_rdr));
	t_cmd->tmp = NULL;
	while (++i < (int)ft_strlen(commands->command))
		norm_f_rdr(commands, t_cmd, &i);
	commands->filerdr = t_cmd->tmp; 
	free(t_cmd);
	return (0);
}


void	trait_command(t_env *evp, t_cmds *commands)
{
	int	i;
	int	nbr_args;

	i = -1;
	nbr_args = 0;
	split_command_rdr(evp, commands, nbr_args);
	files_rdr(evp, commands);
}

int	norm_pipe(t_norm *n, t_cmds **commands, int i)
{
	if (n->cmd[i] == 124)
	{
		if ((*commands)->command)
			free((*commands)->command);
		(*commands)->command = my_substr(n->cmd, n->start, i);
		(*commands)->command = deletespace((*commands)->command);
		trait_command(n->evp, *commands);
		(*commands)->next_p = new_commands(); 
		*commands = (*commands)->next_p;
		n->start = i + 1;
	}
	else if (n->cmd[i] == '\0')
	{
		if (n->start == i)
			return (1);
		if ((*commands)->command)
			free((*commands)->command);
		(*commands)->command = my_substr2(n->cmd, n->start, i); 
		(*commands)->command = deletespace((*commands)->command);
		trait_command(n->  evp, *commands);
		return (1);
	}
	return (0);
}

int	split_pipe(t_env *evp, t_cmds *commands)
{
	t_norm	*n;
	int		i;

	if (commands->command == NULL) 
		return (0);
	i = -1;
	n = new_norm2(evp, commands);
	while (1)
	{
		if (!checkdbl_sngl_c(commands, n->cmd, &i))
		{
			free(n);
			return (0);
		}
		else if (n->cmd[i] == '\\')
		{
			i++;
			continue ;
		}
		if (norm_pipe(n, &commands, i))
			break ;
	}
	commands = n->tmp;
	free(n);
	return (1);
}

t_cmds	*norm_commands2(char *cmds, t_env *evp, t_cmds *commands, int i)
{
	
	evp->ptr = getcwd(evp->buf, 1024);
	commands->command = my_substr(cmds, evp->start, i);
	commands->command = deletespace(commands->command);
	// fprintf(stderr, "[%s]\n", commands->command);
	

	split_pipe(evp, commands);

    // fprintf(stderr, "%s\n", commands->type);
    // fprintf(stderr, "%s\n", commands->next_p);
    // if (commands->next_p == NULL)
    //     fprintf(stderr, "null\n");
    // fprintf(stderr, "%s\n", commands->next_p->next_p->type);
    // fprintf(stderr, "%s\n", commands->next_p->next_p->next_p->type);
	// fprintf(stderr, "[%s]\n", commands->type);
	// t_cmds *tmp1 = commands;
	// while(tmp1)
	// {	
	// 	// fprintf(stderr, "[%s]\n", tmp1->command);
	// 	fprintf(stderr, "type = [%s]\n", tmp1->type);
	// 	fprintf(stderr, "apot = [%d]\n", tmp1->option);
	// 	fprintf(stderr, "cmd = [%s]\n", tmp1->command);
	// 	tmp1 = tmp1->next_p;
	// }
	
	// fprintf(stderr, "[%s] ", tmp1->command);
	// fprintf(stderr, "[%s] ", tmp1->type);
	// fprintf(stderr, "[%d] ", tmp1->option);
	// int h = 0;
	// while (tmp1->arguments[h])
	// {
	// 	fprintf(stderr, "[arg %d %s]",h, tmp1->arguments[h]);
	// 	h++;
	// }
	// fprintf(stderr, "\n");
	


	// if (commands->next_p == NULL)
	// 	ext_cmd_norm(evp, commands);
	// else if (commands->next_p != NULL)
	// {
	// 	evp->tpp = commands;
	// 	while (1)
	// 	{
	// 		check_this_command(commands, evp, 1);
	// 		if (!commands->next_p)
	// 			break ;
	// 		commands = commands->next_p;
	// 	}
	// 	commands = evp->tpp;
	// 	pipe_commmand_c(commands, evp->ptr, evp);
	// }
	free(evp->buf);
	free(evp->ptr);
	return (commands);
}


int	norm_g_cmd1(int *i, t_env *evp, t_cmds **commands, char *cmds)
{
	
    if (cmds[*i] == '\0')
	{
		
		if (evp->start == *i)
		{
			fprintf(stderr, "hreos\n");
			return (1);
		}
		*commands = norm_commands2(cmds, evp, *commands, *i);
		return (1);
	}
	return (0);
}

int	get_commands(t_env *evp, t_cmds **cmm, char *cmds)
{
	int			i;
	t_cmds	*tmp;    

	evp->buf = NULL;
	i = -1;
	evp->start = 0;
	tmp = *cmm;
	while (1)
	{
		
		if (!norm_g_cmd0(&i, *cmm, cmds))
		{
			
			return (0);
		}
			
		else if (cmds[i] == '\\')
		{
			i++;
			continue ;
		}
		if (norm_g_cmd1(&i, evp, cmm, cmds))
		{
			
			break ;
		}
			
	}
	*cmm = tmp;
	return (1);
}