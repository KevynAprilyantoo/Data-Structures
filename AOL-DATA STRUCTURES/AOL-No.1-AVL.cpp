#include <stdio.h>
#include <stdlib.h>
#define RED 0
#define BLACK 1

struct Node{
	int key;
	int color;
	struct Node *left;
	struct Node* right;
	struct Node *parent;
}*root;

Node *createNode(int key){
	Node *newNode = (Node*) malloc(sizeof(Node));
	newNode->key = key;
	newNode->color = RED;
	newNode->left = newNode->right = newNode->parent = NULL;
	return newNode;
}

void leftRotate(Node *node){
	Node *rightChild = node->right;
	node->right = rightChild->left;
	
	if(rightChild->left != NULL){
		rightChild->left->parent = node;
	}
	rightChild->parent = node->parent;
	if (node->parent == NULL) {
        root = rightChild;
    } else if (node == node->parent->left) {
        node->parent->left = rightChild;
    } else {
        node->parent->right = rightChild;
    }
    rightChild->left = node;
    node->parent = rightChild;
}

void rightRotate(Node *node) {
    Node *leftChild = node->left;
    node->left = leftChild->right;
    
    if (leftChild->right != NULL) {
        leftChild->right->parent = node;
    }
    leftChild->parent = node->parent;
    if (node->parent == NULL) {
        root = leftChild;
    } else if (node == node->parent->left) {
        node->parent->left = leftChild;
    } else {
        node->parent->right = leftChild;
    }
    leftChild->right = node;
    node->parent = leftChild;
}

void inOrder (Node *node){
	if(node){
		inOrder(node->left);
		printf("%d ", node->key);
		inOrder(node->right);
	}
}

void fixInsert(Node* node) {
    while (node->parent != NULL && node->parent->color == RED) {
        if (node->parent == node->parent->parent->left) {
            struct Node* grand = node->parent->parent->right;
            if (grand != NULL && grand->color == RED) {
                node->parent->color = BLACK;
                grand->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    node = node->parent;
                    leftRotate(node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rightRotate(node->parent->parent);
            }
        } else {
            struct Node* grand = node->parent->parent->left;
            if (grand != NULL && grand->color == RED) {
                node->parent->color = BLACK;
                grand->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    rightRotate(node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                leftRotate(node->parent->parent);
            }
        }
    }
    node->color = BLACK;
}

void insert(Node** root, int key) {
    Node* z = createNode(key);
    Node* curr = NULL;
    Node* x = *root;
    while (x != NULL) {
        curr = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = curr;
    if (curr == NULL)
        *root = z;
    else if (z->key < curr->key)
        curr->left = z;
    else
        curr->right = z;
    fixInsert(z);
}

int main(){
	insert(&root, 5);
    insert(&root, 3);
    insert(&root, 21);
    insert(&root, 18);
    insert(&root, 29);
    insert(&root, 22);
    insert(&root, 45);
    insert(&root, 41);
    insert(&root, 48);
    insert(&root, 51);
    
    printf("Inorder Traversal of Created Tree: \n");
    inOrder(root);
    printf("\n");

    return 0;
}
