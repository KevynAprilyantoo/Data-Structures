#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 9

int count;

struct hashNode{
	char name[20];
	int key;
} *table[SIZE];

hashNode *newNode(char *name, int key) {
	hashNode *temp = (hashNode*)malloc(sizeof(hashNode));
	strcpy(temp->name, name);
	temp->key = key;
	return temp;
}

int hashFunction(char name[]){
	int len = strlen(name), sum = 0;
	for(int i = 0; i < len; i++) {
		sum += name[i];
	}
	return (sum % SIZE);
}

void insert(hashNode *newNode) {
	if(count == SIZE) {
		puts("FULL KONTOL");
		return;
	} else {
		int key = hashFunction(newNode->name);
		for(int i = 0; i < SIZE; i++) {
			if(!table[key]) {
				break;
			} else {
//				Cara 1:
				key = (key + 1) % SIZE;
//				Cara 2:
//				key++;
//				if(key > SIZE) {
//					key = 0;
//				}
			}
		}
		table[key] = newNode;
		count++;
	}
}

void print() {
	if(!count) {
		puts("KOSONG KONTOL");
		return;
	} else {
		int memek = 0;
		for(int i = 0; i < SIZE; i++) {
			if(table[i]) {
				memek++;
				printf("%d. Name: %s, Key: %d\n", memek, table[i]->name, i);
			}
		}
	}
}

void search(char *searchName) {
	if(!count) {
		puts("KOSONG BANGSAT");
		return;
	} else {
		for(int i = 0; i < SIZE; i++) {
			if(table[i] && strcmp(searchName, table[i]->name) == 0) {
				puts("KETEMU ANJENG");
				return;
			}
		}
		puts("GA KETEMU ANJENG");
		return;
	}
}

void Delete(char *name) {
	if(!count) {
		puts("GA ADA BANGSAT");
		return;
	} else {
		for(int i = 0; i < SIZE; i++) {
			if(table[i] && strcmp(name, table[i]->name) == 0) {
				table[i] = NULL;
				free(table[i]);
				return;
			}
		}
		puts("GA KETEMU ANJENG");
		return;
	}
}

int main() {
	insert(newNode("Miyabi", hashFunction("Miyabi")));
	insert(newNode("yve", hashFunction("yve")));
	insert(newNode("estes", hashFunction("estes")));
//	insert(newNode("Miyabi", hashFunction("Miyabi")));
//	insert(newNode("Miyabi", hashFunction("Miyabi")));
//	insert(newNode("Miyabi", hashFunction("Miyabi")));
//	insert(newNode("Miyabi", hashFunction("Miyabi")));
//	insert(newNode("Miyabi", hashFunction("Miyabi")));
//	insert(newNode("Miyabi", hashFunction("Miyabi")));
	puts("BEFORE~~~~~~");
	print();
	
//	search("Nurhanan");
	
	puts("\nAFTER~~~~~~");
	Delete("Mia Khalifa");
	print();
	
	return 0;
}
