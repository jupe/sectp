/**
   linked_list.h

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
#ifndef LINKED_LIST_H_INCLUDED
#define LINKED_LIST_H_INCLUDED


typedef struct __attribute__((__packed__))
{
	void    *data,  //data of this node
            *prev,  //previous node
            *next;  //next node
} node_t; //node structure

typedef struct __attribute__((__packed__))
{
    node_t  *firstNode,
            *lastNode;
    U32 size;
}LinkedList_t;

LinkedList_t* new_linkedList 		( void );

void 		clear_linkedList		( LinkedList_t* list );
void        free_linkedList			( LinkedList_t* list );

node_t*     linkedList_push			( LinkedList_t *list );
void**      linkedList_baseData		( LinkedList_t *list );
void**      linkedList_topData		( LinkedList_t *list );
void        linkedList_eraseBase	( LinkedList_t *list );
Bool        linkedList_addNewNode	( LinkedList_t *list, void *data, size_t size );


void        linkedList_listAll		( LinkedList_t *list );


#endif // LINKED_LIST_H_INCLUDED
