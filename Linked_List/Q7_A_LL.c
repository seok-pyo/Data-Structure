//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 7 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode; // You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList; // You should not change the definition of LinkedList

//////////////////////// function prototypes /////////////////////////////////////

// You should not change the prototype of this function
void RecursiveReverse(ListNode **ptrHead);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;
	// Initialize the linked list 1 as an empty linked list
	// head 변수는 포인터 변수인건가? 그냥 바로 .으로 접근할 수 있는 건가?
	ll.head = NULL; // Null 포인터
	ll.size = 0;

	printf("1: Insert an integer to the linked list:\n");
	printf("2: Reversed the linked list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			// 입력값을 받아서 링크드 리스트에 노드 추가
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			// ll.head는 포인터?
			RecursiveReverse(&(ll.head)); // You need to code this function // ll.head는 *head를 의미하는 건가? 그럼 ll.head 값이 들어있는 주소를 말하는 건가?
			printf("The resulting linked list after reversed the given linked list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

////////////////////////////////////////////////////////////////////////

void RecursiveReverse(ListNode **ptrHead) // **ptrHead가 들어간 이유? *head의 주소값을 가져오기 위해서?
{
	/*
		1. head 포인터와 next 포인터의 방향을 바꿔서 방향을 바꾼다.
		2. 재귀로 구현해 본다.
		(1,2,3,4,5) -> (5,4,3,2,1)
	*/

	// 1. printf("%p", ptrHead); -> 0x16b0e2ca0
	// 2. printf("%p", *ptrHead); -> 0x133704080 -> 1번과 2번의 차이점은?
	// 3. printf("%p", **ptrHead); warning: format specifies type 'void * but the argument has type 'ListNode' (aka 'struct_listnode)'
	// 이중포인터?
	// lvalue / rvalue
	// &(ll.head)

	ListNode *cur = *ptrHead;
	if (cur->next == NULL || cur == NULL)
		return;

	ListNode *nxt = cur->next;

	RecursiveReverse(&nxt);

	cur->next->next = cur;
	cur->next = NULL;

	*ptrHead = nxt;
}

//////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll)
{

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}

ListNode *findNode(LinkedList *ll, int index) // 포인터를 반환하는 함수?
{

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head; // head 노드에서부터 선형적으로 탐색?
	// index는 head 노드에서부터 떨어진 거리?

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0) // index가 0이 되면, 원하는 포지션을 찾으면
	{
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value)
{

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0)
	{
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode)); // malloc 함수를 사용하는 이유? -> 리스트 노드의 크기를 특정할 수 없기 때문에.
		ll->head->item = value;
		ll->head->next = cur; // head와 next가 모두 cur이 되는 건가?
		ll->size++;
		return 0;
	}

	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL)
	{
		cur = pre->next;
		// malloc으로 새로운 노드 생성
		pre->next = malloc(sizeof(ListNode)); // malloc 함수를 사용하는 이유? -> 입력값으로 받아야 하기 때문에? 런타임 시점에 동적으로 생성해야 하기 때문에?
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}

int removeNode(LinkedList *ll, int index)
{

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0)
	{
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL)
	{

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}

void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL)
	{
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}
