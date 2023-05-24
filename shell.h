#ifndef _MY_SHELL_H_
#define _MY_SHELL_H_

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

/* Read/Write buffer sizes */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* Command chaining types */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* Number conversion options */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* Flag to indicate the usage of system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HISTORY_FILE	".my_shell_history"
#define HISTORY_MAX	4096

extern char **environ;

/**
 * struct linked_list - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct linked_list
{
	int num;
	char *str;
	struct linked_list *next;
} list_t;

/**
 * struct shell_info - contains pseudo-arguments to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguments
 * @argv: an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environment variables
 * @environ: custom modified copy of environment from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last executed command
 * @cmd_buf: address of pointer to cmd ; chain buffer, for memory management
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct shell_info
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

	char **cmd_buf; /* Pointer to cmd ; chain buffer, for memory management */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} shell_info_t;

#define SHELL_INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin_command - contains a builtin command string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin_command
{
	char *type;
	int (*func)(shell_info_t *);
} builtin_command_t;

/* Function declarations */

int my_shell(shell_info_t *, char **);
int find_builtin_command(shell_info_t *);
void find_command(shell_info_t *);
void fork_command(shell_info_t *);

int is_command(shell_info_t *, char *);
char *duplicate_chars(char *, int, int);
char *find_command_path(shell_info_t *, char *, char *);

int my_shell_loop(char **);

void print_error_message(char *);
int print_error_character(char);
int print_to_file_descriptor(char c, int fd);
int print_string_to_file_descriptor(char *str, int fd);
2B
int string_length(char *);
int string_compare(char *, char *);
char *starts_with_string(const char *, const char *);
char *concatenate_strings(char *, char *);

char *copy_string(char *, char *);
char *duplicate_string(const char *);
void print_string(char *);
int print_character(char);

char *copy_string_n(char *, char *, int);
char *concatenate_string_n(char *, char *, int);
char *find_character(char *, char);

char **split_string(char *, char *);
char **split_string2(char *, char);

char *set_memory(char *, char, unsigned int);
void free_string_array(char **);
void *reallocate_memory(void *, unsigned int, unsigned int);

int free_block(void **);

int convert_string_to_integer(shell_info_t *);
int is_delimiter(char, char *);
int is_alpha(int);
int convert_to_integer(char *);

int convert_error_to_integer(char *);
void print_error_message(shell_info_t *, char *);
int print_decimal(int, int);
char *convert_number_to_string(long int, int, int);
void remove_comments_from_string(char *);

int exit_builtin(shell_info_t *);
int change_directory_builtin(shell_info_t *);
int help_builtin(shell_info_t *);

int history_builtin(shell_info_t *);
int alias_builtin(shell_info_t *);

ssize_t get_input_line(shell_info_t *);
int get_line(shell_info_t *, char **, size_t *);
void signal_interrupt_handler(int);

void clear_shell_info(shell_info_t *);
void set_shell_info(shell_info_t *, char **);
void free_shell_info(shell_info_t *, int);

char *_get_environment_variable(shell_info_t *, const char *);
int environment_builtin(shell_info_t *);
int set_environment_variable_builtin(shell_info_t *);
int unset_environment_variable_builtin(shell_info_t *);
int populate_environment_list(shell_info_t *);

char **get_environment(shell_info_t *);
int unset_environment_variable(shell_info_t *, char *);
int set_environment_variable(shell_info_t *, char *, char *);

char *get_history_file_path(shell_info_t *);
int write_history_file(shell_info_t *);
int read_history_file(shell_info_t *);
int build_history_list(shell_info_t *, char *buffer, int line_count);
int renumber_history_list(shell_info_t *);

list_t *add_node_to_list(list_t **, const char *, int);
list_t *add_node_to_list_end(list_t **, const char *, int);
size_t print_string_list(const list_t *);
int delete_node_at_index_from_list(list_t **, unsigned int);
void free_list_nodes(list_t **);

size_t get_list_length(const list_t *);
char **convert_list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *find_node_starting_with_string(list_t *, char *, char);
ssize_t get_node_index_in_list(list_t *, list_t *);

int is_command_chain(shell_info_t *, char *, size_t *);
void check_command_chain(shell_info_t *, char *, size_t *, size_t, size_t);
int replace_alias_in_command(shell_info_t *);
int replace_variables_in_command(shell_info_t *);
int replace_substring(char **, char *);

#endif
