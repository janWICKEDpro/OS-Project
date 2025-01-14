


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "list.h"
#include "cpu.h"
#include "task.h"
#include "schedulers.h"

#define MIN_PRIORITY 1
#define MAX_PRIORITY 10

 struct node *list = NULL;
 struct node *scheduled = NULL;

 int *WT;
// add a task to the list 
static int id=0;
void add(char *name, int priority, int burst){
    Task *task;
    
    task = malloc(sizeof(Task));
    task->burst = burst;
    task->name =malloc(sizeof(char)*3);
    strcpy(task->name,name);
    task->priority = priority;
    task->tid = id++;
    insert(&list, task);
   // if(list!=NULL && list->next!=NULL)  printf("%s",list->next->task->name);
}



int length(){
  int count=0;
   struct node *temp=scheduled;
    while(temp  != NULL){
        count ++;
        temp = temp->next;
    }  
    return count;
}

void WaitingTime(){
    int i =1;
    float sum =0.0;
    struct node *temp = scheduled;
    int len = length();
    WT = malloc(sizeof(int)*len);
    WT[0]  = 0;

    while(temp!=NULL){
        WT[i] = temp->task->burst + WT[i-1];
        sum +=WT[i];
        temp = temp->next;
        i++;
    }
    printf("The average Waiting Time is %f", (float)(sum/len));
}

void turnAroundTime(){
    struct node * temp = scheduled;
    float sum=0.0;
    int i =0;

    while(temp!=NULL){
        sum += WT[i] + temp->task->burst;
        i++;
        temp=temp->next; 
    }

    printf("The average turn around time is %f", (float)(sum/length()));
}

//response time
float responseTime(){
    int sum =0;
    int len = length();
    for(int i=0; i<len; i++){
        sum+=WT[i];
    }
    return (float)(sum/len);
}

// invoke the scheduler
void schedule(){
  struct node *greatest = list;
    struct node *temp = list;
   // printf("%d", list->next->task->burst);
while(temp !=NULL){
    while(temp != NULL){
        if(temp->task->priority> greatest->task->priority){
            greatest = temp;
        }
        temp = temp->next;
    }
        run(greatest->task, greatest->task->burst);
        insert(&scheduled, greatest->task);
        delete(&list, greatest->task);
        temp = list;
        greatest = list;
   }
   WaitingTime();
}

