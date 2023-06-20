/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 09:37:16 by anaraujo          #+#    #+#             */
/*   Updated: 2023/06/13 19:07:26 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"

//readline function
# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

# include <signal.h>
//tcsetattr
# include <termios.h>
# include <time.h>

# include <sys/types.h>
# include <sys/wait.h>

typedef enum s_lex_type
{
	PIPE,
	OUT,
	IN,
	DOUBLE_OUT,
	DOUBLE_IN,
	T_FILE,
	S_Q,
	D_Q,
	TEXT
}		t_lex_type;

typedef struct s_token
{
	char			*token;
	t_lex_type		type;
	struct s_token	*next;
	struct s_token	*prev;
}		t_token;

typedef struct s_env
{
	char			*n;
	char			*t;
	struct s_env	*next;
}		t_env;

typedef struct s_ast
{
	int				i;
	t_lex_type		type;
	int				n_tk;
	bool			here_doc_done;
	t_token			*cmd;
	struct s_ast	*right;
	struct s_ast	*left;
	struct s_ast	*prev;
	int				fdin;
	int				fdout;
	int				is_null;
}		t_ast;

typedef struct s_aux
{
	t_ast			*ast;
	t_token			*cmd;
	t_token			*tk;
	int				i;
	int				p;
	int				p2;
}		t_aux;

typedef struct s_aux2
{
	int				aa;
	int				j;
	int				k;
	int				n;
	char			c;
	char			*s;
}		t_aux2;

typedef struct s_mini
{
	char			*line_read;
	char			*prompt;
	t_token			*cmd;
	t_token			*full_cmd;
	t_env			*env;
	t_env			*exp;
	int				n_exp;
	t_ast			*ast;
	int				no_ast;
	int				ast_active;
	int				pid;
	int				fdin;
	int				fdout;
	int				isbuilt;
	int				n_pipes;
	int				*pipes;
	int				n_tk;
	int				fd_hd;
	int				i_exec;
	int				fill_fds;
}		t_mini;

//Initialize
int			init_lst_env(t_mini *mini, char **envp, int i);
t_env		*ft_env_new(char *str1, char *str2);

//Print 2
char		ft_type(t_lex_type type);
void		ft_astprintrev(t_mini *mini);

//Print
void		ft_lstprint(t_token *lst);
void		astprint_aux(t_ast *ta);
void		astprint_aux2(t_ast *ta);
void		ft_astprint(t_ast *ast, int n_tk);
void		ft_envprint(t_env *env);

//Signals
void		not_finish(int sig_num);
void		not_finish_1(int sig_num);

//------------------------------- AST -----------------------------------
//AST Utils
t_ast		*new_node(t_lex_type type, int i, int in);
void		add_node_to_ast(t_mini *mini, t_ast *node);
int			is_ftype(t_lex_type type);
int			build_ast_base(t_mini *mini);

//AST Utils 2
t_token		*ft_tokendup(t_token *tk);
void		build_ast_aux5(t_aux *a, t_mini *mini);
void		fill_ast_file_aux(t_mini *mini, t_token *tmp);
int			fill_ast_file(t_mini *mini);
void		build_ast_aux(t_mini *mini, t_aux *a);

//AST Utils 3
int			ft_check_pipes_red(t_token *cmd);
int			ft_check_type(t_token *cmd, t_lex_type type);
void		build_1_ast(t_mini *mini);
void		check_nulls_aux(t_mini *mini, int i, int p, int f);
void		check_nulls(t_mini *mini, int i, int p, int f);

//AST Utils 4
int			is_type(t_lex_type a_type, t_lex_type type);
int			ft_n_pipes(t_token *cmd);
int			is_q_text(t_lex_type type);
void		checking_next_node(t_ast **ast);

//AST
void		build_ast_aux6(t_mini *mini, t_aux *a);
void		build_ast_aux2(t_mini *mini, t_aux *a);
void		build_ast_aux3(t_aux *a);
void		build_ast_aux4(t_aux *a);
int			build_ast(t_mini *mini);

//Call AST
void		call_ast(t_mini *mini);

//Expand Utils
int			ft_check_dollar(char *str);
int			ft_count_dollar(char *str);
char		*get_substr(char *str, t_mini *mini);
//Expand
void		expand_var(char **s, t_mini *mini, int i, char *exp);
int			ft_check_dollar(char *str);
int			ft_sl3(char *str);
void		ft_expand(t_mini *mini);

//------------------------------- BUITLINS -------------------------------
//Cd
void		mod_env(char *str, char *str1, t_env *env);
int			ft_cd(t_token *t, t_env *env);
int			ft_cd(t_token *t, t_env *env);

//Echo
void		ft_without_newline(t_token **t, int *i, int *newline, int *f);
int			ft_echo(t_token *t, t_mini *mini);

//Env
int			ft_env(t_env *lst, t_mini *mini);
char		*get_env(char *str, t_env *env);
t_env		*ft_envlast(t_env *env);
void		ft_envadd_b(t_env **lst, t_env *enew);
void		set_env(t_env *envp, char *name, char *text);

//Exit
int			ft_hasdigit(char *str);
int			ft_exit(t_mini *m, t_token *t);

//Export Utils 5
void		ft_export_aux_1_aux(t_mini *mini, t_token *tmp, int *len, int *t);

//Export Utils 4
int			ft_atoi_export2(char *str);
void		ft_export_aux1_aux(char **tmp1, char **tmp2);
int			ft_isequal(char *str);
void		ft_set_new_value_env(t_env	*env, t_token *token);
void		ft_export_aux_1(t_mini *mini, t_token *tmp, int *len, int *t);

//Export Utils 3
int			ft_export_aux_5(t_mini *mini, t_token *tmp, int *len, int *t);
void		ft_export_aux_2(t_mini *mini, t_token *tmp, int *len, int *t);
int			ft_find_red(char *str);
int			ft_check_env(t_env	*env, t_token *token, char c);
void		ft_export_print(t_env *lst, t_mini *mini, t_env *exp);

//Export Utils 2
void		ampersand(t_mini *mini, t_token *lst);
void		ft_env_new2_aux(t_env **e, char *str1, char *str2);
t_env		*ft_env_new2(char *str1, char *str2, t_mini *mini);
int			check_env(t_env *env, char *tk);
void		ft_envadd_b2(t_env **lst, t_env *enew, int n);

//Export Utils
int			check_cardinal_ampers(t_token *lst);
void		ft_set_new_value_env2(t_env	*env, t_token *token);
int			ft_check_env2(t_env	*env, t_token *token);
void		ft_export_aux_3(t_mini *mini, t_token *tmp, int *len, int *t);
void		ft_export_aux_4(t_mini *mini, t_token *tmp, int *len, int *t);

//Export
int			ft_atoi_export_aux(char *str, int i, int a);
int			ft_atoi_export(char *str, t_lex_type type);
int			valid_value(char *s, t_lex_type type);
void		ft_export2(t_mini *mini, t_token *tmp, int *len, int *t);
int			ft_export(t_mini *mini, t_token *tk);

//Pwd
int			ft_pwd(t_mini *mini);

//Unset Utils 2
int			ft_unset_aux4(t_token *tk, t_env *curr, t_env *tmp, int l);

//Unset Utils
void		ft_unset_aux(t_token *tk, int l, t_mini *mini);
void		ft_unset_aux2(t_token *tk, t_env *curr, t_env *tmp, int l);
void		ft_unset_aux3(t_token *tk, t_token *c, t_token *t, int l);
void		free_env(t_env **t);
void		ft_unset_aux5(int *i, t_env **curr, t_env **tmp);

//Unset
int			ft_exp_len(t_env *exp);
void		free_env_2(t_env **t, t_env **tmp);
void		ft_unset_exp(t_mini *mini, t_token *tk, int l);
int			check_unset(char *s);
int			ft_unset(t_mini *mini, int l);

//------------------------------- ERROR -------------------------------
//Error
int			error_handler1(int code, char *str, t_mini *mini);
int			error_handler2(int code, char *str1, char *str2, int as);
int			error_handler3(int code, char *str);
int			error_handler4(int code, t_mini *mini);
int			error_handler5(t_mini *mini, int code, char *str, int n);

//Error 2
int			error_handler(char *str, t_mini *mini, int code);
int			error_handler6(int code, t_mini *mini);
int			error_handler7(t_mini *mini, int code, char *str, int n);

//Free all
void		ft_astclear_prev(t_ast *ast);
void		ft_astclear_next(t_ast *ast);
void		ft_astclear_ast(t_ast **ast, t_mini *mini);
void		ft_astclear_1ast(t_ast **ast);
void		ft_astclear(t_ast **ast, t_mini *mini);

//Free all aux
void		ft_tokenclear(t_token **lst);
void		ft_envclear(t_env **env);
void		free_array(char **array, int lst);
void		free_cycle(t_mini *mini);
void		free_everything(t_mini *mini, int i);

//------------------------------- EXEC -------------------------------
//Exec Builtins
int			is_builtin(char *cmd);
void		exec_builtin2(t_mini *mini);
void		exec_builtin(t_mini *mini, int pipes);

//Ft exec Utils 2
void		free_aux(char **path, char ***token, char ***tmp, int f);

//Ft exec Utils
char		*find_path(char *cmd, t_env *env);
int			ft_envsize(t_env *env);
char		**list_to_array(t_env *env);
int			ft_tokensize(t_token *token);
char		**token_to_array(t_token *token);

//Ft exec
int			do_command(t_mini *mini);
int			simple_commands(t_mini *m);
void		ending_cleaning(t_ast **tree);
int			checking_processes(t_mini *mini);
void		go_minishell(t_mini *mini);

//------------------------------- LEXER -------------------------------
//Lexer Utils
t_token		*ft_tnew(char *str, t_lex_type type);
t_token		*ft_tnew_2(char *str, t_lex_type type);
t_token		*ft_tokenlast(t_token *lst);
void		ft_tadd_b(t_token **lst, t_token *tnew);
int			ft_sl(char *str, char c);

//Lexer Utils 2
void		ft_tk_red_2(t_mini *mini, int full_cmd);
void		ft_tk_red(t_mini *mini, int full_cmd);
int			ft_lexer_aux_1(t_token *t, char *cmds, int is_tadd);
int			ft_n_aspas(char *str, int *i, int n);
void		ft_quotes_tk_aux(char **tk, int n, char *str2, int is_malloc);

//Lexer Utils 3
int			check_red_tokens(t_mini *mini);
int			ft_sl2(char *str);
int			check_unfinished_pipes(t_mini *mini);
int			check_syntax(t_mini	*mini);
int			ft_lexer_aux_3(t_token *t, char *cmds, int is_tadd);

//Lexer Utils 4
int			lexer_aux(t_mini *mini);
int			check_redirect(char *str);
void		ft_quotes_tk_aux2(int k, char c, char **tk);
void		ft_init_a(t_aux2 **a, char *str, int *i);
void		ft_quotes_tk_aux3(t_aux2 **a, int i, char **tk);

//Lexer Utils 5
void		ft_quotes_tk(char **tk, char *str, int *i);
int			ft_lexer_aux_2(t_token **t, char *cmds, int is_tadd);
int			ft_lexer_aux_4(t_token **t, char *cmds);

//Lexer
int			lexer(t_mini *mini, int i, int token_len);
int			call_lexer(t_mini *mini);

//------------------------------- PIPES -------------------------------
//Pipes Utils 3
void		first_pipes_aux2(int f, t_mini *m);
void		final_pipe_aux(t_mini *m);

//Pipes Utils 2
int			get_input(t_mini *mini, int i, int max);
int			get_output(t_mini *mini, int i, int max);
int			checking_redirects_pipes(t_mini *mini, int i);
void		deleting_tempfiles(t_ast *t);
void		first_pipes_aux(int i, t_mini *m);

//Pipes Utils
int			creating_pipes(t_mini *m);
int			child_in(t_mini *mini);
int			child_out(t_mini *mini);
void		close_fd(t_mini *mini, int *pipes);
void		first_pipes_2(t_mini *m, int i);

//Pipes Fill Fds
void		fill_fds_aux(t_ast **a);
void		fill_fds(t_ast *ast, int n_tk);
int			count_red(t_token *tk);

//Pipes
void		close_fds(t_mini *m);
void		first_pipes(t_mini *m, int i, int f);
void		final_pipe(t_mini *m, pid_t *pid, int i);
void		init_varpipes(t_mini *mini, int *i, pid_t *pid);
int			doing_pipes(t_mini *mini);

//------------------------------- PROMPT -------------------------------
//Prompt
char		*get_pwd_str(void);
char		*ft_strjoin_2(char *s1, char *s2);
char		*get_host_str(t_mini *mini);
char		*get_home_str(void);
char		*create_prompt(t_mini *mini);

//Prompt Line
void		readline_prep(t_mini *mini);

//------------------------------- REDIRECTS -------------------------------
//Redirects
void		heredoc(t_mini *mini);
int			input(t_mini *mini);
int			output(t_mini *mini);
int			checking_redirects(t_mini *mini);

#endif
