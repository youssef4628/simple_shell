#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* for number_convert() */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd; chain buffer, memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} inf_t;

#define INFO_INIT                                        \
	{                                                                           \
		NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
			0, 0, 0                                                             \
	}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(inf_t *);
} builtin_table;

/* sh_atoi.c */
int interact(inf_t *);
int delim_check(char, char *);
int _alpha_check(int);
int _atoi(char *);

/* sh_builtin.c */
int exitProgram(inf_t *);
int _mcd(inf_t *);
int _help(inf_t *);

/* sh_builtin1.c */
int _mhistory(inf_t *);
int _myalias(inf_t *);

/* sh_environ.c */
char *_get_env(inf_t *, const char *);
int _my_env(inf_t *);
int _my_set_env(inf_t *);
int _my_unset_env(inf_t *);
int Popenvlist(inf_t *);

/* sh_errors.c */
void _inputs(char *);
int _stdputchar(char);
int _put_fd(char c, int fd);
int _puts_fd(char *str, int fd);

/* sh_errors1.c */
int _erroratoi(char *);
void error_print(inf_t *, char *);
int decimal_print(int, int);
char *number_convert(long int, int, int);
void comment_remove(char *);

/* sh_exits.c */
char *_stringcpy(char *, char *, int);
char *_stringcat(char *, char *, int);
char *_stringchr(char *, char);

/* sh_getenv.c */
char **get_env(inf_t *);
int _unset_enviro(inf_t *, char *);
int _set_enviro(inf_t *, char *, char *);

/* sh_getinfo.c */
void info_clear(inf_t *);
void info_set(inf_t *, char **);
void info_free(inf_t *, int);

/* sh_getline.c */
ssize_t input_get(inf_t *);
int _getline(inf_t *, char **, size_t *);
void sigin_handel(int);

/* sh_history.c */
char *getHistoryFile(inf_t *info);
int history_write(inf_t *info);
int historyRead(inf_t *info);
int list_buildHistory(inf_t *info, char *buf, int linecount);
int history_renumber(inf_t *info);

/* sh_lists.c */
list_t *append_node(list_t **, const char *, int);
list_t *append_node_end(list_t **, const char *, int);
size_t write_list_str(const list_t *);
int remove_node_at_index(list_t **, unsigned int);
void free_li(list_t **);

/* sh_lists1.c */
size_t len_of_list(const list_t *);
char **convert_list_to_strings(list_t *);
size_t write_list(const list_t *);
list_t *node_begins_with(list_t *, char *, char);
ssize_t obtain_node_index(list_t *, list_t *);

/* sh_memory.c */
int bfree(void **);

/* sh_parser.c */
int cmd_checker(inf_t *, char *);
char *duplicates_chars(char *, int, int);
char *path_finder(inf_t *, char *, char *);

/* sh_realloc.c */
char *_mem_setting(char *, char, unsigned int);
void f_free(char **);
void *reallocates(void *, unsigned int, unsigned int);

/* shell_loop.c */
int hshell(inf_t *, char **);
int builtin_finder(inf_t *);
void cmd_finder(inf_t *);
void fork_the_cmd(inf_t *);

/* sh_string.c */
int str_length(char *);
int str_comparison(char *, char *);
char *begin_with(const char *, const char *);
char *str_chain(char *, char *);

/* sh_string1.c */
char *str_cp(char *, char *);
char *str_duplicate(const char *);
void _strout(char *);
int _putchar(char);

/* sh_tokenizer.c */
char **str_to_words(char *, char *);
char **str_to_words_2(char *, char);

/* sh_vars.c */
int is_it_chain(inf_t *, char *, size_t *);
void detect_chain(inf_t *, char *, size_t *, size_t, size_t);
int exchange_alias(inf_t *);
int exchange_vars(inf_t *);
int exchange_string(char **, char *);

#endif
