#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 11
#define MEMORY 1000

struct node{
	int keys;
}*table[SIZE];

int count = 0;

node* create(int keys){
	node* temp = (node*)malloc(sizeof(node));
	temp->keys = keys;
	return temp;
}

int hashFolding(int keys){
	int sum;
	for(int i=0; i<(keys-2); (i+3)){
		if(!keys){
			sum+=((keys-'0')*100);
		}
		if(!keys+1){
			sum+=((keys+1- '0')*10); 
		}
		if(!keys+2){
			sum+=((keys+2-'0'));
		}
	}
	return (sum%MEMORY);
}

void insert(int keys){
	node* temp = create(keys);
	int key = hashFolding(keys);
	
	if(count==SIZE){
		puts("full");
		return;
	}else{
		for(int i=0; i<SIZE; i++){
			if(!table[key]){
				break;
			}else{
				key = (key+1)%SIZE;
			}
		}
		table[key]=temp;
		count++;
	}
}

void print(){
	if(!count){
		puts("kosong\n");
		return;
	}else{
		for(int i=0; i<SIZE; i++){
			printf("%d. ", i);
			if(table[i]!=NULL){
				printf("%d\n",table[i]->keys);
			}else{
				printf("NULL\n");
			}
		}
	}
}

int main(){
	insert(1921678);
	print();
}
