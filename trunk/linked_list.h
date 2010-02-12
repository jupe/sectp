/**
   \file linked_list.h

    @section author Author and license
	Copyright (C) 2009-2010 Jussi Vatjus-Anttila (jussiva@gmail.com)
   
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
   
   
   \defgroup linkedList	linked list

*/
#ifndef LINKED_LIST_H_INCLUDED
#define LINKED_LIST_H_INCLUDED

/**
*	@ingroup linkedList
*	@struct LinkedList_t
*	Head structure
*/
typedef struct 
//__attribute__((__packed__))
{
	//!< @{
    node_t  *firstNode;	//!< First node of head
    node_t  *lastNode; 	//!<  Last node of head
    U32 size;
	//!< @}
}LinkedList_t;


/**
*	@ingroup linkedList
*	@struct node_t
*	Node structure
*	@{
*/
typedef struct 
//__attribute__((__packed__))
{
	void    *data  	//! data of this node
           ,*prev  	//! previous node
           ,*next;  //!< next node
} node_t;
//!< @}



/** ****************************************
 *  
 *	@ingroup linkedList
 *	\defgroup public_member_head	head functions
 *	Function for handle linked list head
 *  @{
 ***************************************** */

/**
*	allocate new linked list head
*	@return linked list structure
*/
LinkedList_t* new_linkedList 		( void );
/**
*	Clear linked list
*	@param list	linked list to be cleared
*/
void 		clear_linkedList		( LinkedList_t* list );
/**
*	free linked list and all childs
*	@param list	linked list to be fresh
*/
void        free_linkedList			( LinkedList_t* list );
/**
*	debug function to list all nodes
*	@param list	linked list
*/
void        linkedList_listAll		( LinkedList_t *list );
//!< @}	public_member_head


/** ****************************************
 *	@ingroup linkedList
 *	\defgroup public_member_data	node functions
 *	Function for handle linked list nodes
 *  @{
 ***************************************** */

/**
*	create new node to linked list end
*	@param list	linked list
*	@return new node
*/
node_t*     linkedList_push			( LinkedList_t *list );
/**
*	get pointer to base data
*	@param list	linked list
*	@return pointer to data
*/
void**      linkedList_baseData		( LinkedList_t *list );
/**
*	get pointer to top data
*	@param list	linked list
*	@return pointer to data
*/
void**      linkedList_topData		( LinkedList_t *list );
/**
*	Erase base node and data
*	@param list	linked list
*/
void        linkedList_eraseBase	( LinkedList_t *list );
/**
*	Create new node and push data to it
*	@param list	linked list
*	@param data	void type of data
*	@param size	size of void-data
*/
Bool        linkedList_addNewNode	( LinkedList_t *list, void *data, size_t size );

//! @}	//public_member_data

#endif // LINKED_LIST_H_INCLUDED
