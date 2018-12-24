
#include <stdio.h>
#include <stdlib.h>
#include "history.h"

 int CAPACITY = 25;
 int currPos = 0;

cmdHistory* init_history() {
  cmdHistory *historyArray = malloc(CAPACITY * sizeof(cmdHistory));
  historyArray[0] = NULL;
  int j = 0;
  for(j = 0; j < CAPACITY; j++) {
      historyArray[j] = NULL;
  }
  return historyArray;
}

 cmdHistory* increaseCap(cmdHistory* historyList) {
   cmdHistory *historyArray = (cmdHistory *) realloc(historyList, (CAPACITY * 2) * sizeof(cmdHistory));
   CAPACITY = CAPACITY * 2;;
   return historyArray;
 }

 int add_history(cmdHistory* historyList, char *readLine[]) {
    struct cmd *current = (struct cmd *)malloc(sizeof(struct cmd));
    historyList[currPos] = current;
    
    char allCommands[MAXSIZE];
    int x = 0;
    while(readLine[x] != NULL) {
      strcat(allCommands, readLine[x]);
      strcat(allCommands, " ");
      x++;
    }
    current->command = malloc(strlen(allCommands) + 1);
    strcpy(current->command, allCommands);
    allCommands[0] = '\0';
    currPos++;
    return 1;
 }

void clear_history(cmdHistory* historyList) {
  int k;
  
  for(k = 0; k < currPos; k++) {
    free(historyList[k]->command);
    free(historyList[k]);
  }
  free(historyList);
}

void print_history(cmdHistory* historyList) {
  int l;

  for(l = 0; l < currPos; l++) {
    printf("%d  %s\n", l, historyList[l]->command);
  }
}