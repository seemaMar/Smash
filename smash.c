#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "history.h"

#define MAXLINE 4096

char cwd[1024];

void getOut(void);

void changeDir(char* token, int pathExists) {
 
  int path = chdir(token);                                      //trying to chage directories
		pathExists = 0;
		if(path < 0)                                               //chdir failed
			fprintf(stdout, "error: %s does not exist\n", token);
		else if(getcwd(cwd, sizeof(cwd)) != NULL) {               //getcwd returns the name of the directory you're currently in	
				fprintf(stdout, "%s\n", cwd);
			} else {
			    pathExists = 0;
			}
}

int main(void) {
	char readLine[MAXLINE];
	cmdHistory* historyList;	
	historyList = init_history();
  int c = 1;
  char* pointerLine[MAXLINE];
	char command[MAXLINE];
  int status;
  pid_t pid;
  int capFlag = 1;
  //const char* PATH = getenv("PATH");
  
	fprintf(stderr, "$");
  while(fgets(readLine, MAXLINE, stdin) != NULL) {                 //reads in line
		readLine[strlen(readLine) - 1] = '\0';
		char * token = strtok(readLine, " ");
		int pathExists = 0;
    int i = 0;
    pointerLine[0] = token;          
    add_history(historyList, pointerLine);
				while(token != NULL) {
          pointerLine[c] = token;                                  //creating pointerLine to better suit addHistory's parameters
          c++;
      
      if(capFlag == 0) {
        historyList = increaseCap(historyList);
        add_history(historyList, pointerLine);
        capFlag = 1;
      }
     	if(pathExists) {
				changeDir(token, pathExists);
        pathExists = 0;
			} else {
				if(strcmp(token, "exit") == 0) {
          clear_history(historyList);                              //clear command history if user exits
				  getOut();
        } else if(strcmp(token, "cd") == 0) {
					pathExists = 1;                                                //throw it up to the first if statement
	} else if(strcmp(token, "history") == 0) {
          print_history(historyList);                              //prints user's history when prompted
        }
        else {
           //printf("ogElse");
           printf("[%d] %s\n", i++, token);  
         
          strncpy(command, pointerLine[0],MAXLINE);
          
          
          if((pid = fork()) < 0) {
             printf("else1");
            fprintf(stderr,"An error occured while trying to fork\n");
          } else if(pid == 0) {
            execvp(command, pointerLine);
            fprintf(stderr, "command not found");
            return 1;
          } 
          if((pid = waitpid(pid, &status, 0)) < 0) {
            fprintf(stderr, "waitpid error");
          }
        }
        
			}
		token = strtok(NULL, " ");
		}
    fprintf(stderr, "$");
	}
  clear_history(historyList);                                    //clears command history at the end
	return 0;
}

/*
  Exits system when called
*/
void getOut(void) {
  exit(0);
}