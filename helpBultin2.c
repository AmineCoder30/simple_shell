#include "shell.h"

void envirHelper(void);
void setEnvirHelper(void);
void unSetEnvirHelper(void);
void hstorHelper(void);

/**
 * envirHelper - this function display info.
 * amine mohamed
 */
void envirHelper(void)
{
	char *ourmsg = "env: env\n\tPrints the current environment.\n";

	write(STDOUT_FILENO, ourmsg, stringLen(ourmsg));
}

/**
 * setEnvirHelper - this function display and set info.
 * amine mohamed
 */
void setEnvirHelper(void)
{
	char *ourmsg = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a new";

	write(STDOUT_FILENO, ourmsg, stringLen(ourmsg));
	ourmsg = "envir var, or modifies an existing one.\n\n";
	write(STDOUT_FILENO, ourmsg, stringLen(ourmsg));
	ourmsg = "\tUpon fail, prints a message to stderror.\n";
	write(STDOUT_FILENO, ourmsg, stringLen(ourmsg));
}

/**
 * unSetEnvirHelper - this function unset envirenment
 * amine mohamed
 */
void unSetEnvirHelper(void)
{
	char *ourmsg = "unsetenv: unset envirenment [VARIABLE]\n\tRemoves an ";

	write(STDOUT_FILENO, ourmsg, stringLen(ourmsg));
	ourmsg = "envir var.\n\n\tUpon fail, prints a ";
	write(STDOUT_FILENO, ourmsg, stringLen(ourmsg));
	ourmsg = "message to stderr.\n";
	write(STDOUT_FILENO, ourmsg, stringLen(ourmsg));
}
