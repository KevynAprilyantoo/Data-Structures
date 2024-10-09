#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 50

struct node
{
	char str[11];
	int times;
	node *next;
}*hashTable[SIZE] = {NULL};

node *createNode(char str[])
{
	node *tmp = (node *)malloc(sizeof(node));
	strcpy(tmp->str, str);
	tmp->next = NULL;
	tmp->times = 1;
}
int hashFunc(char str[])
{
	int sum = 0;
	for(int i = 0; str[i] != '\0'; i++)
	{
		if(str[i] >= 'A' && str[i] <= 'Z')
		{
			sum += (str[i] - 'A');
		}
		else if(str[i] >= '0' && str[i] <= '9')
		{
			sum += (str[i] - '0');
		}
	}
	return sum % SIZE;
}
node *insertRec(node *curr, char str[])
{
	if(!curr) return createNode(str);
	else if(strcmp(curr->str, str) == 0)
	{
		curr->times += 1;
		return curr;
	}
	curr->next = insertRec(curr->next, str);
}
int insert(char str[])
{
	int hash = hashFunc(str);
	hashTable[hash] = insertRec(hashTable[hash], str);
	return 0;
}
int retrieveRec(node *curr, char str[])
{
	if(!curr->next) return 1;
	else if(strcmp(curr->next->str, str) == 0)
	{
		if(curr->next->times > 1)
		{
			curr->next->times -= 1;
			return 0;
		}
		else
		{
			node *tmp = curr->next;
			curr->next = tmp->next;
			free(tmp);
			return 0;
		}
	}
	return retrieveRec(curr->next, str);
}
int retrieve(char str[])
{
	int hash = hashFunc(str);
	if(!hashTable[hash]) return 1;
	else if(strcmp(hashTable[hash]->str, str) == 0)
	{
		if(hashTable[hash]->times > 1)
		{
			hashTable[hash]->times -= 1;
			return 0;
		}
		else if(!hashTable[hash]->next)
		{
			free(hashTable[hash]);
			hashTable[hash] = NULL;
			return 0;
		}
		else if(hashTable[hash]->next)
		{
			node *tmp = hashTable[hash];
			hashTable[hash] = hashTable[hash]->next;
			free(tmp);
			return 0;
		}
	}
	return retrieveRec(hashTable[hash], str);
}
void printTable()
{
	int j = 1;
	printf("%-5s | %-15s | %-5s | %s\n", "No", "ID", "Key","Jumlah");
	for(int i = 0; i < SIZE; i++)
	{
		node *curr = hashTable[i];
		{
			while(curr != NULL)
			{
				printf("%-5d | %-15s | %-5d | %d\n", j , curr->str, i, curr->times);
				curr = curr->next;
				j++;
			}
		}
	}
}

int main()
{
	int menu, check;
	char inp[11];
	while(1)
	{
		puts("1.Insert");	
		puts("2.Print");	
		puts("3.Retrieve");
		puts("4.Exit");
		scanf("%d", &menu);
		switch(menu)
		{
			case 1:
				puts("Masukan ID");
				scanf("%s", &inp);
				check = insert(inp);
				if(check == 0) puts("Barang berhasil dimasukkan");
				else puts("Barang tidak berhasil dimasukkan");
				break;
			case 2:
				printTable();
				break;
			case 3:
				puts("Masukan ID");
				scanf("%s", &inp);
				check = retrieve(inp);
				if(check == 0) puts("Barang berhasil diambil");
				else puts("Barang tidak berhasil diambil");
				break;
			case 4:
				return 0;
			default:
				puts("Wrong Input");
				break;
		}
	}
			
	
}
