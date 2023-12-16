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


#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3


#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2


#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096


/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1


extern char **environ;


/**
 * struct liststr - singly linked list
 *
 * @num: number field
 * @str: string
 * @next: points to the next node
 *
 */

typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;


/**
 * struct passinfo - this contains pseudo-arguements that are passed into
 * a function, allowing uniform prototype for function pointer struct
 *
 * @path: string path for the current command
 * @arg: string generated from getline containing arguements
 * @argv: array of strings generated from arg
 * @argc: argument count
 * @line_count: error count
 * @err_num: error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: history node
 * @histcount: history line number count
 * @alias: alias node
 * @env_changed: on if environ was changed
 * @status: return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: fd from which to read line input
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

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct builtin - contains a built-in string and related function
 *
 * @func: the function
 * @type: the built-in command flag
 */

typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;




int is_command(info_t *, char *);
char *dup_characters(char *, int, int);
char *locate_path(info_t *, char *, char *);


int hsh(info_t *, char **);
int locate_builtin(info_t *);
void locate_command(info_t *);
void fork_command(info_t *);


int loophsh(char **);


void custom_puts(char *);
int buffered_putchar(char);
int write_fd(char c, int fd);
int writeto_fd(char *str, int fd);


int str_len(char *);
int str_compare(char *, char *);
char *str_starts_with(const char *, const char *);
char *str_concat(char *, char *);


char *str_copy(char *, char *);
char *str_duplicate(const char *);
void str_print(char *);
int str_printsingle(char);


char *str_ncopy(char *, char *, int);
char *str_nconcat(char *, char *, int);
char *str_findchar(char *, char);


char **str_split1(char *, char *);
char **str_split2(char *, char);


char *mem_filler(char *, char, unsigned int);
void str_free(char **);
void *blockmem_realloc(void *, unsigned int, unsigned int);


int pointer_free(void **);


int is_interactive(info_t *);
int char_isdelim(char, char *);
int char_isalpha(int);
int str_toint(char *);


int errstr_toint(char *);
void errmsg_tostderr(info_t *, char *);
int printdec_tofd(int, int);
char *number_converter(long int, int, int);
void comment_remover(char *);


int exit_shell(info_t *);
int cd1_shell(info_t *);
int cd2_shell(info_t *);


int show_history(info_t *);
int alias_mimic(info_t *);


void info_clear(info_t *);
void info_set(info_t *, char **);
void info_free(info_t *, int);


char *env_varvalue(info_t *, const char *);
int env_variables(info_t *);
int env_set(info_t *);
int env_unset(info_t *);
int envlist_populate(info_t *);


ssize_t line_nonline(info_t *);
int get_nextline(info_t *, char **, size_t *);
void ctrlc_blocker(int);


char *history_filepath(info_t *shell_info);
int writecmd_history(info_t *shell_info);
int readcmd_history(info_t *shell_info);
int addcmd_history(info_t *shell_info, char *buf, int linecount);
int history_numrenew(info_t *shell_info);


char **environ_copy(info_t *);
int environ_unset(info_t *, char *);
int environ_set(info_t *, char *, char *);


list_t *newnode_liststart(list_t **, const char *, int);
list_t *addnode_listend(list_t **, const char *, int);
size_t print_liststr(const list_t *);
int remove_indexnodes(list_t **, unsigned int);
void free_listnodes(list_t **);


size_t llist_len(const list_t *);
char **llistto_strings(list_t *);
size_t print_llistelements(const list_t *);
list_t *node_nodeprefix(list_t *, char *, char);
ssize_t get_nodeindex(list_t *, list_t *);


int isbufchar_chain(info_t *, char *, size_t *);
void chain_checker(info_t *, char *, size_t *, size_t, size_t);
int replace_tstringalias(info_t *);
int replace_tstringvars(info_t *);
int replace_string(char **, char *);

#endif
