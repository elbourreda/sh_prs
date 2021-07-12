/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-bour <rel-bour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 13:25:09 by rel-bour          #+#    #+#             */
/*   Updated: 2021/07/12 20:03:04 by rel-bour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_H
#define HEAD_H

#include <stdio.h>

//read line 
#include <readline/readline.h>
#include <readline/history.h>

#include <stdbool.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>//for exit
#include <unistd.h> // for fork
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h> // for wait 

typedef struct s_filerdr
{
	char				*name;
	int					type;
	int					error;
	struct s_filerdr	*next;
}					t_filerdr;

typedef struct s_cmds
{
    char *command;//
    char *line;
    char **all;
    char *type;
    char **arguments;
    int option; 
    int multiple;
	t_filerdr			*filerdr;
    struct s_cmds	*next_p;
}   t_cmds;

typedef struct s_tmp{
	char	*s1;
	char	*s2;
	int		i;
	int		j;
	char	*ss;
	char	*rstr;
	int		k;
	char	*test;
	int		z;
	char	*s;
	int		lenp;
	char	*buff;
	char	*fsf;
	int		dl;
}					t_tmp;




typedef struct s_commandg
{
	char	*line;
	int		staus_code;
	int		ctrl_c;
	char	*ret;
	int		ctrl_quit;
	char	*type;
	char	*old_pwd;
	int		redir_fd_in;
	int		redir_fd;
	int		yesdup;
	int		pipe_err;
	int		option;
}					t_commandg;

t_commandg	*g_all;



typedef struct s_rdr
{
	int			i;
	int			start;
	int			k;
	int			b;
	char		*rdr_cmd;
	char		*str;
	char		*t;
	t_filerdr	*tmp;
}					t_rdr;


typedef struct s_env
{
	char		**my_env;
	char		*save;
	int			start;
	int			i;
	char		*buf;
	t_cmds		*tpp; 
	char		*ptr;
	char		*check_term;
	char		*test;
}					t_env;

typedef struct s_nor 
{
	int			lenp;
	char		*nameenv;
	int			j;
	int			i;
	int			len;
	char		*s;
	char		*v;
	int			t;
	int			tee;
	char		*te;
	char		*buff;
	char		*fsf;
	int			o;
	int			h;
	int			b;
	int			c;
	char		*varibale;
	char		*ef;
	int			fd;
	int			fd_check;
	char		*sh;
	char		*n_tmp;
	char		*newsh;
	int			lenarg;
	int			k;
	int			z;
	char		**tprr;
	int			fs;
	int			ck;
	char		**com_path;
	char		*path;
	int			saved_stdout;
	int			saved_input;
	int			fd_in;
	int			fd_o;
	char		*ptr2;
	int			g;
	int			fd_l;
	int			read_fd;
	int			fd_pipe[2];
	int			write_fd;
	int			file;
	int			fd_input;
	int			fd_out;
	int			pipe_ch;
	int			start;
	t_cmds	*tmp;
	char		*cmd;
	char		*cmd_tmp;
	t_env		*evp;
	char		*tmp33;
	int			ck2;
}		t_norm;

typedef struct s_libf
{
	long		x;
	int			n;
	int			i;
	char		*str;
	int			i2;
	int			j;
	char		**pm;
	size_t		i3;
	size_t		x3;
	size_t		j3;
	char		*p;
}	t_libftn;

void main_parsing();
t_cmds	*all_t(void);




///envp
void initsial_envs(t_env **evp, char **envs);
char	**edit_envp_old_pwd(char **envp_c);
char	**edit_envp_v(char **envp_c);
char	**half_v_edit(char **envp_c, t_norm norm);
char	**half(char **envp_c, t_norm norm);
char	**edit_envp_shlvl(char **envp_c);
char	**half_edit_envp(char **envp_c, t_norm norm);
int	ft_atoi(const char *str);
char	*search_in_env2(char *variable, char **envp);
char	*ft_itoa1(int nbr);
static int	numblen(long long number);
char	*half_search(char *variable, char **envp, t_norm norm);
char	*half_h_search(char **envp, t_norm norm);
int	my_strcmp(char *s1, char *s2);
char	*get_env_name(char *envp);
char	**copy_envp(char **envp_l);
int	len_of_args(char **args);
char	*ft_strdup(const char *s1);
char	*ft_strjoin1(char *s1, char *s2);
size_t	ft_strlen(char const *str);
int	get_commands(t_env *evp, t_cmds **cmm, char *cmds);
char	*my_substr(char *s, int start, int end);
char	*my_substr2(char *s, int start, int end);
t_cmds	*new_commands(void);
#endif