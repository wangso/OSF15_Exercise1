#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "command.h"

#define MAX_CMD_COUNT 50
#define MAX_CMD_LEN 25


	//TODO FUNCTION COMMENT
/* 
 * PURPOSE: To parse a user input string and returns the tokenized commands to a pointer
 * INPUTS:
 *	input input command string
 * 	cmd pointer to the Command_t structure containing the tokenized commands and the number of commands
 * RETURN:
 *  If no errors occurred during parsing then true
 *  else false for an error in the process.
 *
 **/

bool parse_user_input (const char* input, Commands_t** cmd) {
	
	//TODO ERROR CHECK INCOMING PARAMETERS
	if (!input) {
		return false;
	}
	if (!cmd) {
		return false;	
	}

	char *string = strdup(input);
	
	*cmd = calloc (1,sizeof(Commands_t));
	(*cmd)->cmds = calloc(MAX_CMD_COUNT,sizeof(char*));

	unsigned int i = 0;
	char *token;
	token = strtok(string, " \n");
	for (; token != NULL && i < MAX_CMD_COUNT; ++i) {
		(*cmd)->cmds[i] = calloc(MAX_CMD_LEN,sizeof(char));
		if (!(*cmd)->cmds[i]) {
			perror("Allocation Error\n");
			return false;
		}	
		strncpy((*cmd)->cmds[i],token, strlen(token) + 1);
		(*cmd)->num_cmds++;
		token = strtok(NULL, " \n");
	}
	free(string);
	return true;
}

	//TODO FUNCTION COMMENT
/* 
 * PURPOSE: To clear the memory allocation for the variable
 * INPUTS:
 * 	name of the pointer to the Command_t structure containing commands 
 * RETURN:
 *  If no errors occurred the memory allocated to cmd is cleared
 *  else return nothing.
 *
 **/

void destroy_commands(Commands_t** cmd) {

	//TODO ERROR CHECK INCOMING PARAMETERS
	if (!cmd) {
		return;	
	}
	
	for (int i = 0; i < (*cmd)->num_cmds; ++i) {
		free((*cmd)->cmds[i]);
	}
	free((*cmd)->cmds);
	free((*cmd));
	*cmd = NULL;
}

