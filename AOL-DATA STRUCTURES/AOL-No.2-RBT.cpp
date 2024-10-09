#include <Stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
	int key;
	int height;
	Node *left;
	Node *right;
}*root = NULL;

Node *createNode(int key){
	Node *temp = (Node*) malloc(sizeof(Node));
	temp->key = key;
	temp->height = 1;
	temp->left = temp->right = NULL;
	return temp;
}

int getMax(int a, int b){
	return a > b ? a : b;
}

int getHeight(Node *curr){
	if(!curr) return 0;
	return 1+getMax(getHeight(curr->left), getHeight(curr->right));
}

int getBalance(Node* curr){
	if(!curr) return 0;
	return getHeight(curr->left)-getHeight(curr->right);
}

Node *rightRotate(Node *data){
	Node *temp = data->left;
	Node *subTemp = temp->right;
	
	temp->right = data;
	data->left = subTemp;
	
	temp->height = getHeight(temp);
	data->height = getHeight(data);
	
	return temp;
}

Node *leftRotate(Node *data){
	Node *temp = data->right;
	Node *subTemp = temp->left;
	
	temp->left = data;
	data->right = subTemp;
	
	temp->height = getHeight(temp);
	data->height = getHeight(data);
	
	return temp;
}

Node *rebalancing(Node *root){
	root->height = getHeight(root);
	int balance = getBalance(root);
	
	if(balance > 1 && getBalance(root->left)>=0){
		return rightRotate(root);
	}else if(balance > 1 && getBalance(root->left)<0){
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}else if(balance < -1 && getBalance(root->right)<=0){
		return leftRotate(root);
	}else if( balance < -1 && getBalance(root->right)>0){
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}
	return root;	
}

Node *insert(Node *root, int key){
	if(!root){
		return createNode(key);
	}else if(root->key < key){
		root->right = insert(root->right, key);
	}else if(root->key > key){
		root->left = insert(root->left, key);
	}
	return rebalancing(root);
}

Node *del(Node *root, int key){
	if(!root){
		puts ("Data not found"); return root;
	}else if(key < root->key ){
		root->left = del(root->left, key);
	}else if(key > root->key){
		root->right = del(root->right, key);
	}else{
			if(!root->left || !root->right ){
			Node *temp = root->left ? root->left : root->right;
			if(!temp){
				temp = root;
				root = NULL;
			}else {
				*root = *temp;
			}
			free(temp);
		}
		else {
			Node *temp = root->right;
			while(temp->left) temp = temp->left;
			root->key = temp->key;
			root->right = del(root->right, temp->key);	
		}
		puts("Data Found");
		printf("Value %d was deleted\n", key);
	}
	if(!root) return NULL;
	return rebalancing(root);
}

void inOrder (Node * root){
	if(root){
		inOrder(root->left);
		printf("%d ", root->key);
		inOrder(root->right);
	}
}

void preOrder (Node * root){
	if(root){
		printf("%d ", root->key);
		preOrder(root->left);
		preOrder(root->right);
	}
}

void postOrder (Node * root){
	if(root){
		postOrder(root->left);
		postOrder(root->right);
		printf("%d ", root->key);
	}
}



int main(){
	int num,Del,input = 0;
	
	while(1){
		printf("1. Insertion\n");
		printf("2. Deletion\n");
		printf("3. Traversal\n");
		printf("4. Exit\n");
		
		do{	
		printf("Choose : ");
		scanf("%d", &input);getchar();
		}while(input < 1 || input > 4);
				
		switch(input){
			case 1:{
				printf("Insert : ");
				scanf("%d", &num);
				root = insert(root, num);
				break;
			}
			case 2:{
				int Del;
				printf("Delete : ");
				scanf("%d", &Del);getchar();
				root = del(root, Del);
				break;
			}
			case 3:{
				printf("Preorder : ");
				preOrder(root);
				printf("\n");
				printf("Inorder : ");
				inOrder(root);
				printf("\n");
				printf("Postorder : ");
				postOrder(root);
				printf("\n");
				break;
			}
			case 4:{
				printf("Thank you\n");
				exit(0);
				break;
			}
		}
	}
	return 0;
}


