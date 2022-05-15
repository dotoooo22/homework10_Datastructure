#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

#define MAX_STACK_SIZE 20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();	//��
void push(Node* aNode);		//Ǫ��

#define MAX_QUEUE_SIZE 20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();	//ť�տ�������
void enQueue(Node* aNode);		//ť�ϳ��߰�


int initializeBST(Node** h);		//�ʱ�ȭ

void recursiveInorder(Node* ptr);	  //��ͷ� ������ȸ
void iterativeInorder(Node* ptr);     //��;ƴѰɷ� ������ȸ
void levelOrder(Node* ptr);	          //����������ȸ
int insert(Node* head, int key);      //������
int deleteNode(Node* head, int key);  //������
int freeBST(Node* head); //�޸�����

void printStack();	//�������



int main()
{
	char command;
	int key;
	Node* head = NULL;
	printf("[----- [������] [2021041021] -----]\n");
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		case 'p': case 'P':
			printStack();
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {
	//�������� �޸�����
	if(*h != NULL)
		freeBST(*h);

	//����� ����
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	//��Ʈ
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr)
{
	if(ptr) {
		recursiveInorder(ptr->left);		//�������� ����
		printf(" [%d] ", ptr->key);			//Ű���
		recursiveInorder(ptr->right);		//������ ����
	}
}

void iterativeInorder(Node* node)
{
	for(;;)		//��ӹݺ�
	{
		for(; node; node = node->left)		//������ ��� ���ÿ� Ǫ��
			push(node);
		node = pop();	//�ϳ���

		if(!node) break;	//��尡 ���̸� ��������
		printf(" [%d] ", node->key);	//Ű���

		node = node->right;		//���������� �ö�
	}
}

void levelOrder(Node* ptr)
{
	if(!ptr) return; //�ƹ��͵� ����

	enQueue(ptr);	//ť�� ptr�߰�

	for(;;)
	{
		ptr = deQueue();	//�ǾհŸ� ptr�� ���
		if(ptr) {	//ptr�� �Ӵ������
			printf(" [%d] ", ptr->key);		//Ű���

			if(ptr->left)	//���ʿ� �� ������
				enQueue(ptr->left);		//���ʰŸ� ť�� �߰�
			if(ptr->right)				//�����ʿ� �� ������
				enQueue(ptr->right);		//�����ʰŸ� ť�� �߰�
		}
		else	//�ƹ��͵������� ��������
			break;

	}

}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));		//����忡 �ֱ�
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {	//ó���̸� �����ʿ� �����ϰ� ����
		head->left = newNode;
		return 1;
	}

	Node* ptr = head->left;		//ptr�� Ž���Ұ���

	Node* parentNode = NULL;	//�θ���
	while(ptr != NULL) {		//NULL�ƴҶ�����

		if(ptr->key == key) return 1;		//����Ű�� �̹� ������ ����

		
		parentNode = ptr;	//�θ� ptr�ְ�

		if(ptr->key < key)		//�θ�Ű���� ũ�� ����������
			ptr = ptr->right;
		else					//�ƴϸ� �������� �̵�
			ptr = ptr->left;
	}

	if(parentNode->key > key)	//�θ�Ű���� ������ ���ʿ� ����
		parentNode->left = newNode;
	else						//�ƴϸ� �����ʿ� ����
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)
{
	if (head == NULL) {	//�ƹ��͵�����
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) {	//�ƹ��͵�����
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	Node* root = head->left;		//��Ʈ�� ������



	Node* parent = NULL;		//�θ�
	Node* ptr = root;		//ptr�� ��Ʈ

	while((ptr != NULL)&&(ptr->key != key)) {		//��尡 �ְ�, key�� ã��������
		if(ptr->key != key) {	//ã��Ű�� �ٸ���

			parent = ptr;	//�θ� ptr�ְ�

			if(ptr->key > key)		//Ű�� ������ ��������
				ptr = ptr->left;
			else
				ptr = ptr->right;	//�ƴϸ� ����������
		}
	}

	if(ptr == NULL)		//ã�� Ű ����
	{
		printf("No node for key [%d]\n ", key);
		return -1;
	}

	
	if(ptr->left == NULL && ptr->right == NULL)	//ptr�� ���ʵ� �����ʵ� ��������� (�����忡 �ڽ��� ������)
	{
		if(parent != NULL) { //�θ� ������
			if(parent->left == ptr)		//�θ��� �����̸� ���� �׳� �γְ�
				parent->left = NULL;
			else						//�������̸� �����ʿ� �γְ�
				parent->right = NULL;
		} else {
			//�θ� ���̸� ����Ű� �� ó���Ŵϱ� ù��°�� �η�
			head->left = NULL;

		}

		free(ptr);		//�޸������ϰ� ����
		return 1;
	}

	if ((ptr->left == NULL || ptr->right == NULL))		//�����尡 �ϳ��� �ڽ��� ���� ������
	{
		Node* child;		//�ڽĳ��
		if (ptr->left != NULL)	//�ڽ��ִ� ���� �ڽ��� child�� ����
			child = ptr->left;
		else
			child = ptr->right;

		if(parent != NULL)		//�θ� ������
		{
			if(parent->left == ptr)		//�ڽ��� ���� �����ġ�� ����
				parent->left = child;
			else
				parent->right = child;
		} else {//�θ� ���̸� ����� root�� �ڽ��� root�ڸ���
			root = child;
		}

		free(ptr);	//ptr�޸������ϰ� ����
		return 1;
	}

	
	//���� �ΰ� �پƴϸ� �����尡 �ڽ��� �ΰ� ���� �ִ� ���
	Node* candidate;
	parent = ptr;	//�θ� ptr


	candidate = ptr->right;			//�������� ���� ���� �ĺ��� �ֱ�

	while(candidate->left != NULL)		//�ĺ����ʿ� �Ӱ� �ִµ���
	{
		parent = candidate;		//�θ� �ĺ�
		candidate = candidate->left;		//�ĺ��� ���ʰ� ����
	}

	
	if (parent->right == candidate)	// �������� �������� candidate��
		parent->right = candidate->right;		//�θ��� �����ʿ� �ĺ��� �������� ����
	else
		parent->left = candidate->right;			//�ƴϸ� ���ʿ� �������� ����

	

	ptr->key = candidate->key;		//�ĺ��� Ű�� ptrŰ�� �ְ�

	free(candidate);		//candidate �޸������ϰ� ����
	return 1;
}


void freeNode(Node* ptr)
{
	if(ptr) {	//ptr�� ��������
		freeNode(ptr->left);	//������ ����
		freeNode(ptr->right);	//�������� ����
		free(ptr);		//ptr�޸�����
	}
}

int freeBST(Node* head)
{

	if(head->left == head)	//��常������ ���޸������ϰ� ����
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}



Node* pop()
{
	if (top < 0) return NULL;	//���ÿ��ƹ��͵�����
	return stack[top--];	//��
}

void push(Node* aNode)
{
	stack[++top] = aNode;	//Ǫ��
}


void printStack()
{
	int i = 0;
	printf("--- stack ---\n");
	while(i <= top)		//�������� ���
	{
		printf("stack[%d] = %d\n", i, stack[i]->key);
	}
}


Node* deQueue()
{
	if (front == rear) { 	//front�� rear�� ������ �ƹ��͵� ť�� ����
		return NULL;
	}

	front = (front + 1) % MAX_QUEUE_SIZE;	//front�� ��ĭ�ڷοű�
	return queue[front];		//�Ǿհ� ����

}

void enQueue(Node* aNode)
{
	rear = (rear + 1) % MAX_QUEUE_SIZE;	//rear��ĭ �ڷ�
	if (front == rear) {	//�ƹ��͵�����
		return;
	}

	queue[rear] = aNode;	//�ڿ� aNode �߰�
}





