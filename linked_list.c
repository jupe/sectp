/**
 * buffer_handler_usart.c
 *
   Copyright (C) 2009-2010 Jussi Vatjus-Anttila
   
   This source code is provided 'as-is', without any express or implied
   warranty. In no event will the author be held liable for any damages
   arising from the use of this software.

   Permission is granted to anyone to use this software for any purpose,
   including commercial applications, and to alter it and redistribute it
   freely, subject to the following restrictions:

   1. The origin of this source code must not be misrepresented; you must not
      claim that you wrote the original source code. If you use this source code
      in a product, an acknowledgment in the product documentation would be
      appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and must not be
      misrepresented as being the original source code.

   3. This notice may not be removed or altered from any source distribution.

   Jussi Vatjus-Anttila 	jussiva@gmail.com
*/
#include <string.h>
#include <stdlib.h>

#include "linked_list.h"

#define LINKED_MALLOC(x)	malloc(x)
#define LINKED_FREE(x)		free(x)

static void insertAfter(LinkedList_t *list, node_t *node, node_t *newNode);
static void insertBefore(LinkedList_t *list, node_t *node, node_t *newNode);
static void insertBeginning(LinkedList_t *list, node_t *newNode);
static void insertEnd(LinkedList_t *list, node_t *newNode);
static void eraseNode(LinkedList_t *list, node_t *node);

static void insertAfter(LinkedList_t *list, node_t *node, node_t *newNode)
{
    newNode->prev = node;
    newNode->next = node->next;
    if(node->next == NULL)
        list->lastNode = newNode;
    else
        ((node_t*)node->next)->prev = newNode;
    node->next = newNode;
}
static void insertBefore(LinkedList_t *list, node_t *node, node_t *newNode)
{
    newNode->prev = node->prev;
    newNode->next = node;
    if ( node->prev == NULL )
        list->firstNode = newNode;
    else
        ((node_t*)node->prev)->next = newNode;

    node->prev    = newNode;
}
static void insertBeginning(LinkedList_t *list, node_t *newNode)
{
     if( list->firstNode == NULL) {
         list->firstNode = newNode;
         list->lastNode  = newNode;
         newNode->prev = NULL;
         newNode->next = NULL;
     }
     else
         insertBefore(list, list->firstNode, newNode);
}
static void insertEnd(LinkedList_t *list, node_t *newNode)
{
     if (list->lastNode == NULL)
         insertBeginning(list, newNode);
     else
         insertAfter(list, list->lastNode, newNode);
}
static void  eraseNode(LinkedList_t *list, node_t *node)
{
    node_t *nodeToErase = node;

    if(node == NULL)return;
    if(list->firstNode == NULL)return;

    if (node->prev == NULL){
        list->firstNode = node->next;
        if(list->firstNode != NULL){
            list->firstNode->prev = NULL;
        }
    }
    else
       ((node_t*)node->prev)->next = node->next;

    if (node->next == NULL)
       list->lastNode = node->prev;
    else
       ((node_t*)node->next)->prev = node->prev;

    //free memory from node data
    if(nodeToErase->data)
    {
    	LINKED_FREE(nodeToErase->data);
        nodeToErase->data = NULL;
    }
    LINKED_FREE(nodeToErase);
    list->size--;
}

LinkedList_t* new_linkedList(void)
{
	LinkedList_t *list = LINKED_MALLOC(sizeof(LinkedList_t));
    list->firstNode = NULL;
    list->lastNode = NULL;
    list->size = 0;
    return list;
}
void clear_linkedList(LinkedList_t* list)
{
	node_t  *node=list->firstNode,
			*next;
	while(node != NULL)
	{
		next = node->next;
		if(node->data)LINKED_FREE(node->data);
		if(node)LINKED_FREE(node);
		list->size--;
		node = next;
	}
}
void  free_linkedList(LinkedList_t* list)
{
	clear_linkedList(list);
    LINKED_FREE(list);
}
node_t* linkedList_push(LinkedList_t *list)
{
    //allocate memory for new node
    node_t *node_new = LINKED_MALLOC(sizeof(node_t));
    if(node_new == NULL)return NULL;

    //insert new node to list
    insertEnd(list, node_new);
    list->size++;

    //return data pointer just added
    return node_new;


}
void** linkedList_baseData(LinkedList_t *list)
{
    //get data from base of list
	if( (list == NULL) || (list->firstNode == NULL) )return NULL;
	if(list->firstNode->data == NULL)return NULL;
    return (void**)(&list->firstNode->data);
}
void** linkedList_topData(LinkedList_t *list)
{
    //return data from top of list
    return (void**)(&list->lastNode->data);
}
void linkedList_eraseBase(LinkedList_t *list)
{
    //erase base node from list
    eraseNode(list, list->firstNode);
}

Bool linkedList_addNewNode(LinkedList_t *list, void *data, size_t size)
{
	node_t *node;
	if(size==0)return FALSE;
	node = linkedList_push(list);
	if(node ==NULL) return FALSE;

    //if wan't to save char type data.
    node->data = LINKED_MALLOC(size);
    if(node->data == NULL)return FALSE;

    memcpy(node->data, data, size);

    return TRUE;
}



void linkedList_listAll(LinkedList_t *list) // list all nodes function
{
    node_t *node;
    
	if( list->firstNode == NULL )
    {
		//
    	return;

    }
    else
    {
        //prints table titles
        node = list->firstNode;
        do
        {
            //do something
        }
        while( ( node = node->next ) != NULL );
    }
}
