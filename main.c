#include "shell.h"

void sig_handler(int sngl);
int func_exc(char **amgt, char **ourfront);

/**
 * sig_handler - function to print "$"&new line.
 * @sngl: sing var.
 * amine mohamed and boukhriss
 */
void sig_handler(int sngl)
{
	char *newPrmpt = "\n$ ";

	(void)sngl;
	signal(SIGINT, sig_handler);
	write(STDIN_FILENO, newPrmpt, 3);
}

/**
 * func_exc - function to execute pid.
 * @amgt: array of amgt.
 * @ourfront: double ptr.
 * Return: return an integer.
 */
int func_exc(char **amgt, char **ourfront)
{
	pid_t child_pid;
	int status, flag = 0, ret = 0;
	char *command = amgt[0];

	if (command[0] != '/' && command[0] != '.')
	{
		flag = 1;
		command = locate_funct(command);
	}

	if (!command || (access(command, F_OK) == -1))
	{
		if (errno == EACCES)
			ret = (func_createErr(amgt, 126));
		else
			ret = (func_createErr(amgt, 127));
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			if (flag)
				free(command);
			perror("Error child:");
			return (1);
		}
		if (child_pid == 0)
		{
			execve(command, amgt, environ);
			if (errno == EACCES)
				ret = (func_createErr(amgt, 126));
			fn_to_free_envir();
			fn_to_free_arg(amgt, ourfront);
			func_free_alsList(aliases);
			_exit(ret);
		}
		else
		{
			wait(&status);
			ret = WEXITSTATUS(status);
		}
	}
	if (flag)
		free(command);
	return (ret);
}

/**
 * main - function to excute cmd.
 * @argc: num of amgt.
 * @argv: array of amgt.
 * Return: return an integer.
 */
int main(int argc, char *argv[])
{
	int ret = 0, retn;
	int *exeRet = &retn;
	char *prompt = "$ ", *new_line = "\n";

	name = argv[0];
	hist = 1;
	aliases = NULL;
	signal(SIGINT, sig_handler);

	*exeRet = 0;
	environ = envir_fn_cp();
	if (!environ)
		exit(-100);

	if (argc != 1)
	{
		ret = prFileCmd(argv[1], exeRet);
		fn_to_free_envir();
		func_free_alsList(aliases);
		return (*exeRet);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (ret != END_OF_FILE && ret != EXIT)
			ret = arg_handler(exeRet);
		fn_to_free_envir();
		func_free_alsList(aliases);
		return (*exeRet);
	}

	while (1)
	{
		write(STDOUT_FILENO, prompt, 2);
		ret = arg_handler(exeRet);
		if (ret == END_OF_FILE || ret == EXIT)
		{
			if (ret == END_OF_FILE)
				write(STDOUT_FILENO, new_line, 1);
			fn_to_free_envir();
			func_free_alsList(aliases);
			exit(*exeRet);
		}
	}

	fn_to_free_envir();
	func_free_alsList(aliases);
	return (*exeRet);
}
