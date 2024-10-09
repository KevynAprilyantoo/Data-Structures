#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Cust{
	char name[255];
	int prio;
	Cust* next;
	Cust* prev;
}*head, *tail;

Cust *newCust(char* name, int prio){
	Cust* temp = (Cust*)malloc(sizeof(Cust));
	strcpy(temp->name, name);
	temp->prio = prio;
	temp->next = temp->prev = NULL;
	return temp;
}

void waitingList(){
	puts("Waiting Line: ");
	if(!head){
		puts("Queue is empty");
	}else{
		Cust* curr = head;
		int number = 1;
		while(curr){
			printf("%d. %s\n",  number, curr->name);
			curr = curr->next ;
			number++;
		}
	}
	puts("");
}

void add(Cust* newCust){
	if(!head){
		head=tail=newCust;
		return;
	}else if(newCust->prio < head->prio ){
		newCust->next = head ;
		head->prev = newCust;
		head = newCust;
	}else if(newCust->prio > tail->prio ){
		tail->next = newCust;
		newCust->prev = tail;
		tail = newCust;
	}else{
		Cust* curr = head;
		while(curr && newCust->prio >= curr->prio ){
			curr= curr->next ;
		}
		newCust->next = curr;
		newCust->prev = curr->prev ;
		curr->prev->next = newCust;
		curr->prev = newCust;
	}
}

void serve(){
	if(!head){
		printf("Empty\n");
	}else{
		if(head->prio == 1){
			printf("Attention %s is being served at VVIP table.\n",head->name);
		}
		else if(head->prio == 2){
			printf("Attention %s is being served at VIP table.\n",head->name);
		}
		else if(head->prio == 3){
			printf("Attention %s is being served at regular table.\n",head->name);
		}else if(head->prio == 4){
			printf("Attention %s is being served at regular table",head->name);
		}
		Cust* temp = head;
		head = head->next;
		temp=NULL;
		free(temp);
	}
}

void dismiss(){
	if(!head){
		printf("Empty\n");
		return;
	}else{
		head = tail = NULL;
		printf("End of the day\n");
		printf("Press enter to continue\n");getchar();
		return;
	}
}

int main(){
	while(1){
		system("cls");
		puts("============================");
		puts("SUNIB Restaurant Reservation");
		puts("============================");
		
		waitingList();
		
		puts("1. Add Customer to Queue");
		puts("2. Serve One");
		puts("3. Serve All");
		puts("4. Dismiss Queue");
		puts("0. Exit");
		
		int menuNumber = -1;
		do{
			printf("Input Menu Number: ");
			scanf("%d",&menuNumber);
			getchar();
		}while(menuNumber < 0 || menuNumber > 4);
		
		if(menuNumber == 1){
			char status[255], name[255];
			scanf("%s %[^\n]", status, name);getchar();
			
			int prio;
			if(strcmp("VVIP",status)==0){
				prio = 1;
			}else if(strcmp("VIP",status)==0){
				prio = 2;
			}else if(strcmp("Member",status)==0){
				prio = 3;
			}else if(strcmp("Guest",status)==0){
				prio = 4;
			}
			add(newCust(name,prio));
		}else if(menuNumber == 2){
			serve();
			printf("\nPlease enter to continue...");
			getchar();
		}else if(menuNumber == 3){
			while(head){
			serve();
			}
			printf("\nPlease enter to continue...");
			getchar();
		}else if(menuNumber == 4){
			dismiss();
			getchar();
		}else if(menuNumber == 0){
			break;
		}
	}
	return 0;
}
