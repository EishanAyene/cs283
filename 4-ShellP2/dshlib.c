#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "dshlib.h"

/*
 * Implement your exec_local_cmd_loop function by building a loop that prompts the 
 * user for input.  Use the SH_PROMPT constant from dshlib.h and then
 * use fgets to accept user input.
 * 
 *      while(1){
 *        printf("%s", SH_PROMPT);
 *        if (fgets(cmd_buff, ARG_MAX, stdin) == NULL){
 *           printf("\n");
 *           break;
 *        }
 *        //remove the trailing \n from cmd_buff
 *        cmd_buff[strcspn(cmd_buff,"\n")] = '\0';
 * 
 *        //IMPLEMENT THE REST OF THE REQUIREMENTS
 *      }
 * 
 *   Also, use the constants in the dshlib.h in this code.  
 *      SH_CMD_MAX              maximum buffer size for user input
 *      EXIT_CMD                constant that terminates the dsh program
 *      SH_PROMPT               the shell prompt
 *      OK                      the command was parsed properly
 *      WARN_NO_CMDS            the user command was empty
 *      ERR_TOO_MANY_COMMANDS   too many pipes used
 *      ERR_MEMORY              dynamic memory management failure
 * 
 *   errors returned
 *      OK                     No error
 *      ERR_MEMORY             Dynamic memory management failure
 *      WARN_NO_CMDS           No commands parsed
 *      ERR_TOO_MANY_COMMANDS  too many pipes used
 *   
 *   console messages
 *      CMD_WARN_NO_CMD        print on WARN_NO_CMDS
 *      CMD_ERR_PIPE_LIMIT     print on ERR_TOO_MANY_COMMANDS
 *      CMD_ERR_EXECUTE        print on execution failure of external command
 * 
 *  Standard Library Functions You Might Want To Consider Using (assignment 1+)
 *      malloc(), free(), strlen(), fgets(), strcspn(), printf()
 * 
 *  Standard Library Functions You Might Want To Consider Using (assignment 2+)
 *      fork(), execvp(), exit(), chdir()
 */

 int build_cmd_buff(char *cmd_line, cmd_buff_t *cmd)
 {
     memset(cmd, 0, sizeof(cmd_buff_t));
 
     if (strlen(cmd_line) == 0) {
         return WARN_NO_CMDS;
     }
 
     char *ptr = cmd_line;
     int argc = 0;
     bool in_quotes = false;
 
     while (*ptr) {
         while (*ptr == ' ' && !in_quotes) ptr++;  
         if (*ptr == '\0') break;
 
         if (*ptr == '"') {
             in_quotes = !in_quotes; 
             ptr++;  
             cmd->argv[argc++] = ptr;
         } else {
             cmd->argv[argc++] = ptr;
         }
 
         while (*ptr && (in_quotes || *ptr != ' ')) {
             if (*ptr == '"') {
                 in_quotes = !in_quotes;  
                 *ptr = '\0';  
             }
             ptr++;
         }
 
         if (*ptr == ' ') *ptr++ = '\0';  
 
         if (argc >= CMD_ARGV_MAX - 1) {
             return ERR_TOO_MANY_COMMANDS;
         }
     }
 
     cmd->argv[argc] = NULL;
     cmd->argc = argc;
     if (argc == 0) {
        return WARN_NO_CMDS;
    } else {
        return OK;
    }
 }
 

int exec_local_cmd_loop()
{
    char cmd_buff[SH_CMD_MAX];
    cmd_buff_t cmd;

    // TODO IMPLEMENT MAIN LOOP
    while (1) {
        printf("%s", SH_PROMPT);
        if (!fgets(cmd_buff, SH_CMD_MAX, stdin)) {
            printf("\n");
            break;
        }
        cmd_buff[strcspn(cmd_buff, "\n")] = '\0';


        // TODO IMPLEMENT parsing input to cmd_buff_t *cmd_buff
        if (strlen(cmd_buff) == 0) {
            printf(CMD_WARN_NO_CMD);
            continue;
        }

        int rc = build_cmd_buff(cmd_buff, &cmd);
        if (rc == WARN_NO_CMDS) {
            printf(CMD_WARN_NO_CMD);
            continue;
        } else if (rc == ERR_TOO_MANY_COMMANDS) {
            printf(CMD_ERR_PIPE_LIMIT, CMD_MAX);
            continue;
        }

       // TODO IMPLEMENT if built-in command, execute builtin logic for exit, cd (extra credit: dragon)
       // the cd command should chdir to the provided directory; if no directory is provided, do nothing
        Built_In_Cmds bi_cmd = match_command(cmd.argv[0]);
        if (bi_cmd == BI_CMD_EXIT) {
            break;
        } else if (bi_cmd == BI_CMD_CD) {
            if (cmd.argc > 1 && chdir(cmd.argv[1]) != 0) {
                perror("cd failed");
            }
        } else {
            // TODO IMPLEMENT if not built-in command, fork/exec as an external command
            // for example, if the user input is "ls -l", you would fork/exec the command "ls" with the arg "-l"
            pid_t pid = fork();
            if (pid == 0) {
                execvp(cmd.argv[0], cmd.argv);
                perror("Failed");
                exit(ERR_EXEC_CMD);
            } else if (pid < 0) {
                perror("fork failed");
            } else {
                int status;
                waitpid(pid, &status, 0);
            }
        }
    }
    return OK;

}

Built_In_Cmds match_command(const char *input) {
    if (strcmp(input, "exit") == 0) {
        return BI_CMD_EXIT;
    } else if (strcmp(input, "cd") == 0) {
        return BI_CMD_CD;
    }
    return BI_NOT_BI;

}
