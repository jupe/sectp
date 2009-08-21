/**
   protocol.h

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
#ifndef PROTOCOL_H_INCLUDED
#define PROTOCOL_H_INCLUDED

#include "compiler.h"
#include "linked_list.h"
#include "message_enumerations.h"

# define MALLOC(p,s,n)		(p=(s*)malloc(n*sizeof(s)))
# define PROTOCOL_MALLOC(p,s,n)	MALLOC(p,s,n)
# define PROTOCOL_FREE(p)		free(p)

#define PROTOCOL_TEST_PATTERN		"\x0\x0\x0\x5\x1\x1\x0TESTIQUERY"
#define PROTOCOL_TEST_PATTERN_LEN	18

#define PROTOCOL_MIN_LENGTH			7
#define PROTOCOL_MAX_LENGTH			64

typedef unsigned char U8


/**
*   protocol message structure
*/
typedef struct __attribute__((__packed__))
{
    MESSAGE_GROUP           group;
    MESSAGE_TYPE            type;
    MESSAGE_TYPE_EXTENSION  type_extension;
    U8                      data_size;
    U8*                     data;
}message_t;

/**
*   raw protocol message struct
*/
typedef struct __attribute__((__packed__))
{
    U8* data;
    U8  size;
}raw_message_t;

/**
*   receive and trasfer protocol message structure
*/
typedef struct __attribute__((__packed__))
{
    LinkedList_t *rx;
    LinkedList_t *tx;
} message_buffer_t;


/**
*   Allocate memory area for protocol buffers
*   @param none
*   @return message_buffer_t* allocated memory area for messagebuffer structure
*/
extern message_buffer_t*    protocol_allocate( void );

/**
*   relase all memory from protocol buffers
*   @param buffers pointer to buffers
*   @return none
*/
extern void                 protocol_free( message_buffer_t** buffers );

/**
*   push protocol message to linked list
*   @param list     protocol buffer to be push
*   @param message  message to be push
*   @return TRUE if succesfull, else FALSE
*/
extern Bool                 protocol_push(  LinkedList_t *list,
                                            message_t *message);
/**
*   create protocol message
*   @param group                message group
*   @param type                 message type
*   @param type_extension       specified for type
*   @param type_extension       specified for type
*   @param data                 data to be adde message
*   @param data_size            data size
*   @return message_t*          allocated memoryare for message
*/
extern message_t*          protocol_create_message(    MESSAGE_GROUP group,
                                                       MESSAGE_TYPE type,
                                                       MESSAGE_TYPE_EXTENSION type_extension,
                                                       U8 *data,
                                                       int data_size);
/**
*   pop oldest message from list
*   @param list                 linked list structure
*   @return message_t*          pointer for oldest message
*/
extern message_t*           protocol_pop( LinkedList_t *list);

/**
*   delete oldest value from linkedlist
*   @param list                 linked list structure
*   @return none
*/
extern void                 protocol_pop_delete(   LinkedList_t *list);

/**
*   parse raw hex format to message
*   @param raw_message_data         hex format message
*   @return message_t*              parsed allocated message
*/
extern message_t*           protocol_parse_raw_message(char* raw_message_data, int data_size);

/**
*   create raw hex message
*   @param message_t                pointer to message
*   @return raw_message_t*          raw message structure
*/
extern raw_message_t*       protocol_create_raw_message(message_t* message);

extern void					protocol_message_free(message_t **message);
extern void 				protocol_raw_message_free(raw_message_t **message);
#endif // PROTOCOL_H_INCLUDED
