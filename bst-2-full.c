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

Node* pop();	//팝
void push(Node* aNode);		//푸쉬

#define MAX_QUEUE_SIZE 20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();	//큐앞에거제거
void enQueue(Node* aNode);		//큐하나추가


int initializeBST(Node** h);		//초기화

void recursiveInorder(Node* ptr);	  //재귀로 중위순회
void iterativeInorder(Node* ptr);     //재귀아닌걸로 중위순회
void levelOrder(Node* ptr);	          //레벨순서순회
int insert(Node* head, int key);      //노드삽입
int deleteNode(Node* head, int key);  //노드삭제
int freeBST(Node* head); //메모리해제

void printStack();	//스택출력



int main()
{
	char command;
	int key;
	Node* head = NULL;
	printf("[----- [곽민정] [2021041021] -----]\n");
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
	//머있으면 메모리해제
	if(*h != NULL)
		freeBST(*h);

	//헤드노드 생성
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	//루트
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr)
{
	if(ptr) {
		recursiveInorder(ptr->left);		//왼쪽으로 들어가기
		printf(" [%d] ", ptr->key);			//키출력
		recursiveInorder(ptr->right);		//오른쪽 들어가기
	}
}

void iterativeInorder(Node* node)
{
	for(;;)		//계속반복
	{
		for(; node; node = node->left)		//왼쪽을 계속 스택에 푸시
			push(node);
		node = pop();	//하나팝

		if(!node) break;	//노드가 널이면 빠져나옴
		printf(" [%d] ", node->key);	//키출력

		node = node->right;		//오른쪽으로 올라가
	}
}

void levelOrder(Node* ptr)
{
	if(!ptr) return; //아무것도 없음

	enQueue(ptr);	//큐에 ptr추가

	for(;;)
	{
		ptr = deQueue();	//맨앞거를 ptr에 담기
		if(ptr) {	//ptr에 머담겼으면
			printf(" [%d] ", ptr->key);		//키출력

			if(ptr->left)	//왼쪽에 머 있으면
				enQueue(ptr->left);		//왼쪽거를 큐에 추가
			if(ptr->right)				//오른쪽에 머 있으면
				enQueue(ptr->right);		//오른쪽거를 큐에 추가
		}
		else	//아무것도없으면 빠져나감
			break;

	}

}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));		//새노드에 넣기
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {	//처음이면 헤드왼쪽에 연결하고 리턴
		head->left = newNode;
		return 1;
	}

	Node* ptr = head->left;		//ptr로 탐색할거임

	Node* parentNode = NULL;	//부모노드
	while(ptr != NULL) {		//NULL아닐때까지

		if(ptr->key == key) return 1;		//같은키가 이미 있으면 리턴

		
		parentNode = ptr;	//부모에 ptr넣고

		if(ptr->key < key)		//부모키보다 크면 오른쪽으로
			ptr = ptr->right;
		else					//아니면 왼쪽으로 이동
			ptr = ptr->left;
	}

	if(parentNode->key > key)	//부모키보다 작으면 왼쪽에 연결
		parentNode->left = newNode;
	else						//아니면 오른쪽에 연결
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)
{
	if (head == NULL) {	//아무것도없음
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) {	//아무것도없음
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	Node* root = head->left;		//루트에 헤드왼쪽



	Node* parent = NULL;		//부모
	Node* ptr = root;		//ptr에 루트

	while((ptr != NULL)&&(ptr->key != key)) {		//노드가 있고, key를 찾을때까지
		if(ptr->key != key) {	//찾는키랑 다르면

			parent = ptr;	//부모에 ptr넣고

			if(ptr->key > key)		//키가 작으면 왼쪽으로
				ptr = ptr->left;
			else
				ptr = ptr->right;	//아니면 오른쪽으로
		}
	}

	if(ptr == NULL)		//찾는 키 없음
	{
		printf("No node for key [%d]\n ", key);
		return -1;
	}

	
	if(ptr->left == NULL && ptr->right == NULL)	//ptr의 왼쪽도 오른쪽도 비어있으면 (지울노드에 자식이 없으면)
	{
		if(parent != NULL) { //부모가 있으면
			if(parent->left == ptr)		//부모의 왼쪽이면 왼쪽 그냥 널넣고
				parent->left = NULL;
			else						//오른쪽이면 오른쪽에 널넣고
				parent->right = NULL;
		} else {
			//부모가 널이면 지울거가 맨 처음거니까 첫번째걸 널로
			head->left = NULL;

		}

		free(ptr);		//메모리해제하고 리턴
		return 1;
	}

	if ((ptr->left == NULL || ptr->right == NULL))		//지울노드가 하나의 자식을 갖고 있으면
	{
		Node* child;		//자식노드
		if (ptr->left != NULL)	//자식있는 곳의 자식을 child에 넣음
			child = ptr->left;
		else
			child = ptr->right;

		if(parent != NULL)		//부모가 있으면
		{
			if(parent->left == ptr)		//자식을 지울 노드위치로 연결
				parent->left = child;
			else
				parent->right = child;
		} else {//부모가 널이면 지울게 root고 자식이 root자리로
			root = child;
		}

		free(ptr);	//ptr메모리해제하고 리턴
		return 1;
	}

	
	//위에 두개 다아니면 지울노드가 자식을 두개 갖고 있는 경우
	Node* candidate;
	parent = ptr;	//부모에 ptr


	candidate = ptr->right;			//지울노드의 오른 쪽을 후보에 넣기

	while(candidate->left != NULL)		//후보왼쪽에 머가 있는동안
	{
		parent = candidate;		//부모에 후보
		candidate = candidate->left;		//후보엔 왼쪽걸 넣음
	}

	
	if (parent->right == candidate)	// 지울노드의 오른쪽이 candidate면
		parent->right = candidate->right;		//부모의 오른쪽에 후보의 오른쪽을 연결
	else
		parent->left = candidate->right;			//아니면 왼쪽에 오른쪽을 연결

	

	ptr->key = candidate->key;		//후보의 키를 ptr키에 넣고

	free(candidate);		//candidate 메모리해제하고 리턴
	return 1;
}


void freeNode(Node* ptr)
{
	if(ptr) {	//ptr에 머있으면
		freeNode(ptr->left);	//왼쪽을 보내
		freeNode(ptr->right);	//오른쪽을 보내
		free(ptr);		//ptr메모리해제
	}
}

int freeBST(Node* head)
{

	if(head->left == head)	//헤드만있으면 헤드메모리해제하고 리턴
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
	if (top < 0) return NULL;	//스택에아무것도없음
	return stack[top--];	//팝
}

void push(Node* aNode)
{
	stack[++top] = aNode;	//푸쉬
}


void printStack()
{
	int i = 0;
	printf("--- stack ---\n");
	while(i <= top)		//꼭대기까지 출력
	{
		printf("stack[%d] = %d\n", i, stack[i]->key);
	}
}


Node* deQueue()
{
	if (front == rear) { 	//front랑 rear랑 같으면 아무것도 큐에 없음
		return NULL;
	}

	front = (front + 1) % MAX_QUEUE_SIZE;	//front를 한칸뒤로옮김
	return queue[front];		//맨앞거 리턴

}

void enQueue(Node* aNode)
{
	rear = (rear + 1) % MAX_QUEUE_SIZE;	//rear한칸 뒤로
	if (front == rear) {	//아무것도없음
		return;
	}

	queue[rear] = aNode;	//뒤에 aNode 추가
}





