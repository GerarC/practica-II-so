#include "../include/execution.h"
#include "../include/builtin.h"
#include <bsd/string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>

void execute_command(Command* command){
        for (int i = 0; i < command->num_cmd; i++) {
            if(!command->argcs[i]) return;
            if (!strcmp(command->subcommands[i][0], "exit")){
                if (command->argcs[i] > 1) PRINT_ERROR();
                else exec_exit();
            }
            else if (!strcmp(command->subcommands[i][0], "cd")) {
                if (command->argcs[i] < 2) PRINT_ERROR();
                else change_directory(command->subcommands[i][1]);
            } else {
                if(command->is_redirected[i]) execute_and_redirect_subcommand(
                        command->subcommands[i],
                        command->argcs[i]);
                else execute_subcommand(command->subcommands[i]);
            }
        }
}

int execute_subcommand(char** subcommand){
    int fd = -1; 
    char **cmd_path = path;
    char command_path[PATH_SIZE];
    pid_t subprocess;


    for(int i = 0; i<path_len && (strcmp(*cmd_path, "") != 0) && fd != 0; i++) {
        strlcpy(command_path, *cmd_path++, PATH_SIZE);
        int len = strlen(command_path);
        if(command_path[len - 1] != '/') strlcat(command_path, "/", PATH_SIZE);
        strlcat(command_path, subcommand[0], PATH_SIZE);
        fd = access(command_path, X_OK);
    }

    if(fd == 0){
        subprocess = fork();
        if(subprocess == 0) execvp(command_path, subcommand);
        else if(subprocess < 0) PRINT_ERROR();
        else wait(NULL);
    }else PRINT_ERROR();

    return fd;
}

int execute_and_redirect_subcommand(char** subcommand, int argc){
    int valid_redirection = 0;
    for(int i = 0; i < argc; i++)
        if(!strcmp(subcommand[i], ">")) valid_redirection++;
        
    if(valid_redirection != 1 || argc < 3 || strcmp(subcommand[argc - 2], ">")) {
        PRINT_ERROR();
        return -1;
    }

    int fd = -1; 
    char** cmd_path = path;
    char** command_argvs;
    char command_path[PATH_SIZE];
    char* redirect_path;
    pid_t subprocess;


    for(int i = 0; i<path_len && (strcmp(*cmd_path, "") != 0) && fd != 0; i++) {
        strlcpy(command_path, *cmd_path++, PATH_SIZE);
        int len = strlen(command_path);
        if(command_path[len - 1] != '/') strlcat(command_path, "/", PATH_SIZE);
        strlcat(command_path, subcommand[0], PATH_SIZE);
        fd = access(command_path, X_OK);
    }

    redirect_path = expand_path(subcommand[argc - 1]);

    if(fd == 0){
        if(is_dir(redirect_path)){
            PRINT_ERROR();
            return -1;
        }
        command_argvs = (char**) malloc(argc - 2);
        for(int i = 0; i < argc - 2; i++) command_argvs[i] = subcommand[i];
        subprocess = fork();
        if(subprocess == 0){
            int outfile = open(redirect_path, O_RDWR | O_CREAT | O_APPEND, 0666);
            int saved_out = dup(fileno(stdout));
            if(outfile == -1 || dup2(outfile, fileno(stdout)) == -1){
                PRINT_ERROR();
                free(command_argvs);
                return -1;
            }
            execvp(command_path, command_argvs);

            fflush(stdout);
            close(outfile);
            dup2(saved_out, fileno(stdout));
            close(saved_out);
        }
        else if(subprocess < 0) PRINT_ERROR();
        else wait(NULL);
        free(command_argvs);
    }else PRINT_ERROR();

    free(redirect_path);
    return fd;
}
