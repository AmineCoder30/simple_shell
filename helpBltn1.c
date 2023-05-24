#include "shell.h"

void allHelper(void);
void alsHelper(void);
void chdirHelper(void);
void extHelper(void);
void hpHelper(void);

/**
 * allHelper - this function display commands possible.
 */
void allHelper(void)
{
	char *ourmsg = "Shellby\nThese shell commands are defined internally.\n";

	write(STDOUT_FILENO, ourmsg, stringLen(ourmsg));
	ourmsg = "Type 'help' to see this list.\nType 'help name' to find ";
	write(STDOUT_FILENO, ourmsg, stringLen(ourmsg));
	ourmsg = "out more about the function 'name'.\n\n  alias   \t";
	write(STDOUT_FILENO, ourmsg, stringLen(ourmsg));
	ourmsg = "alias [NAME[='VALUE'] ...]\n  cd    \tcd   ";
	write(STDOUT_FILENO, ourmsg, stringLen(ourmsg));
	ourmsg = "[DIRECTORY]\n  exit    \texit [STATUS]\n  env     \tenv";
	write(STDOUT_FILENO, ourmsg, stringLen(ourmsg));
	ourmsg = "\n  setenv  \tsetenv [VARIABLE] [VALUE]\n  unsetenv\t";
	write(STDOUT_FILENO, ourmsg, stringLen(ourmsg));
	ourmsg = "unsetenv [VARIABLE]\n";
	write(STDOUT_FILENO, ourmsg, stringLen(ourmsg));
}

/**
 * alsHelper - this function display info about command.
 * amine mohamed
 */
void alsHelper(void)
{
	char *ourmsg = "alias: alias [NAME[='VALUE'] ...]\n\tHandles aliases.\n";

	write(STDOUT_FILENO, ourmsg, stringLen(ourmsg));
	ourmsg = "\n\talias: Prints a list of all aliases, one per line, in ";
	write(STDOUT_FILENO, ourmsg, stringLen(ourmsg));
	ourmsg = "the format NAME='VALUE'.\n\talias name [name2 ...]:prints";
	write(STDOUT_FILENO, ourmsg, stringLen(ourmsg));
	ourmsg = " the aliases name, name2, etc. one per line, in the ";
	write(STDOUT_FILENO, ourmsg, stringLen(ourmsg));
	ourmsg = "form NAME='VALUE'.\n\talias NAME='VALUE' [...]: Defines";
	write(STDOUT_FILENO, ourmsg, stringLen(ourmsg));
	ourmsg = " an alias for each NAME whose VALUE is given. If NAME ";
	write(STDOUT_FILENO, ourmsg, stringLen(ourmsg));
	ourmsg = "is already an alias, replace its value with VALUE.\n";
	write(STDOUT_FILENO, ourmsg, stringLen(ourmsg));
}

/**
 * chdirHelper - this function display info about cd command.
 * amine mohamed
 */
void chdirHelper(void)
{
	char *ourmsg = "cd: cd [DIRECTORY]\n\tChanges the current directory of the";

	write(STDOUT_FILENO, ourmsg, stringLen(ourmsg));
	ourmsg = " process to DIRECTORY.\n\n\tIf no argument is given, the ";
	write(STDOUT_FILENO, ourmsg, stringLen(ourmsg));
	ourmsg = "command is interpreted as cd $HOME. If the argument '-' is";
	write(STDOUT_FILENO, ourmsg, stringLen(ourmsg));
	ourmsg = " given, the command is interpreted as cd $OLDPWD.\n\n";
	write(STDOUT_FILENO, ourmsg, stringLen(ourmsg));
	ourmsg = "\tThe environment variables PWD and OLDPWD are updated ";
	write(STDOUT_FILENO, ourmsg, stringLen(ourmsg));
	ourmsg = "after a change of directory.\n";
	write(STDOUT_FILENO, ourmsg, stringLen(ourmsg));
}

/**
 * extHelper - this function display info about exit command.
 * by amine mohamed and boukhriss.
 */
void extHelper(void)
{
	char *ourmsg = "exit: exit [STATUS]\n\tExits the shell.\n\n\tThe ";

	write(STDOUT_FILENO, ourmsg, stringLen(ourmsg));
	ourmsg = "STATUS argument is the integer used to exit the shell.";
	write(STDOUT_FILENO, ourmsg, stringLen(ourmsg));
	ourmsg = " If no argument is given, the command is interpreted as";
	write(STDOUT_FILENO, ourmsg, stringLen(ourmsg));
	ourmsg = " exit 0.\n";
	write(STDOUT_FILENO, ourmsg, stringLen(ourmsg));
}

/**
 * hpHelper - this function display info about help command.
 */
void hpHelper(void)
{
	char *ourmsg = "help: help\n\tSee all possible Shellby builtin commands.\n";

	write(STDOUT_FILENO, ourmsg, stringLen(ourmsg));
	ourmsg = "\n      help [BUILTIN NAME]\n\tSee specific information on each ";
	write(STDOUT_FILENO, ourmsg, stringLen(ourmsg));
	ourmsg = "builtin command.\n";
	write(STDOUT_FILENO, ourmsg, stringLen(ourmsg));
}
