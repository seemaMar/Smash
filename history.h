/*#ifndef __HISTORY_H
#define __HISTORY_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 4096
struct cmd{
  
  char *command; //Reference to the user's command string
  
};

 typedef struct cmd *cmdHistory;
 
 cmdHistory* init_history();
 
 //int add_history(cmdHistory* historyList, char* userArg[]);
 int add_history(cmdHistory* historyList, char* readLine[]);
 void clear_history(cmdHistory* historyList);
 
 void print_history(cmdHistory* historyList);
 
 #endif
*/

#ifndef __HISTORY_H
#define __HISTORY_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 4096

struct cmd {
 char* command;  //Reference to the user's command string
};

typedef struct cmd *cmdHistory;
cmdHistory * increaseCap(cmdHistory* historyList);
cmdHistory * init_history();
int add_history(cmdHistory* historyList, char* readLine[]);
void clear_history(cmdHistory* historyList);
void print_history(cmdHistory* historyList);

#endif