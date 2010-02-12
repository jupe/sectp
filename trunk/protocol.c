
#include <string.h>
#include <stdlib.h>

#include "compiler.h"
#include "sdramc.h"
#include "memory.h"
#include "sdram.h"

#include <string.h>

//#include "leak_detector_c.h"
#include "exception_handler.h"


#include "linked_list.h"
#include "protocol.h"

static U32 proto_U8x4toU32(U8* in);

message_buffer_t*    protocol_allocate( void )
{
    message_buffer_t* buffers = (message_buffer_t*)malloc(sizeof(message_buffer_t));
    if(buffers == NULL){
    	exception_handler(EXCEPTION_MEMORY_MALLOC, (void*)LINEAT);
    	return NULL;
    }

    buffers->rx = new_linkedList();
    buffers->tx = new_linkedList();

    return buffers;
}
void protocol_free( message_buffer_t** buffers )
{
    free_linkedList((*buffers)->rx);
    free_linkedList((*buffers)->tx);
    PROTOCOL_FREE(*buffers);
}
Bool protocol_push(  LinkedList_t *list, message_t *message)
{
    node_t *node;
    if(message==NULL || list==NULL)return FALSE;
    node = linkedList_push(list);
    if(node ==  NULL) return FALSE;
    node->data = (void*)message;
    return TRUE;
}
message_t*  protocol_create_message(    MESSAGE_GROUP group,
                                        MESSAGE_TYPE type,
                                        MESSAGE_TYPE_EXTENSION type_extension,
                                        U8 *data,
                                        int data_size)
{
    message_t* new_message;

    if(PROTOCOL_MALLOC(new_message, message_t, 1) ){
    	exception_handler(EXCEPTION_MEMORY_MALLOC, (void*)LINEAT);
		return NULL;
    }

    new_message->group = group;
    new_message->type = type;
    new_message->type_extension = type_extension;

    new_message->data_size = data_size;

    if(PROTOCOL_MALLOC(new_message->data, U8, new_message->data_size))
    {
    	exception_handler(EXCEPTION_MEMORY_MALLOC, (void*)LINEAT);
    	PROTOCOL_FREE(new_message);
        return NULL;
    }
    //memcpy(new_message->data, data, data_size);
    my_memcpy(new_message->data, data, data_size);


    return new_message;

}

message_t* protocol_pop( LinkedList_t *list )
{
    if( list == NULL ) return NULL;
	if(list->firstNode==NULL) return NULL;
	message_t **ptr = (message_t**)linkedList_baseData(list);
    if(ptr == NULL) return NULL;
    return *ptr;
}
void protocol_pop_delete( LinkedList_t *list )
{
	if(list == NULL)return;

	message_t** message = (message_t**)linkedList_baseData(list);

    if(message == NULL )return;
    if(*message == NULL)return;

    PROTOCOL_FREE((*message)->data);
    PROTOCOL_FREE(*message);
    linkedList_eraseBase( list );

}




/**
*  PROTOCOL MESSAGE FORM
*
*   byte_count [4B] | message_group [1B] | message_type [2B] | data
*/
message_t* protocol_parse_raw_message( char* raw_message_data, int message_size )
{
	U32 data_size;
	message_t *message;

    if( (message_size < PROTOCOL_MIN_LENGTH) ||
    	(message_size > PROTOCOL_MAX_LENGTH) ) 		return NULL;
    if( PROTOCOL_MALLOC(message, message_t, 1) ) 	return NULL;
    data_size = message_size - PROTOCOL_MIN_LENGTH;

    message->data_size = U8x4toU32((U8*)raw_message_data);
    message->data_size -= PROTOCOL_MIN_LENGTH;


    if(data_size != message->data_size){
    	//sizes are different!? some error
    	exception_handler(EXCEPTION_PROTOCOL_MESSAGE, (void*)LINEAT);
    	PROTOCOL_FREE(message);
    	return NULL;
    }

    message->group = (MESSAGE_GROUP)raw_message_data[4];
    message->type = (MESSAGE_TYPE)raw_message_data[5];
    message->type_extension = raw_message_data[6];
    message->data = NULL;

    if(message->data_size > 0){
		if( PROTOCOL_MALLOC(message->data, U8, message->data_size) )
		{
			exception_handler(EXCEPTION_MEMORY_MALLOC, (void*)LINEAT);
			PROTOCOL_FREE(message);
			return NULL;
		}
		/// @bug don't know why memcpy doesn't work here!? protocol crash quickly
		//memcpy(message->data, raw_message_data+PROTOCOL_MIN_LENGTH, message->data_size);
		my_memcpy(message->data, raw_message_data+PROTOCOL_MIN_LENGTH, message->data_size);
		//for(i=0;i<message->data_size;i++)
		//	message->data[i] = raw_message_data[PROTOCOL_MIN_LENGTH+i];

    }


    return message;
}
raw_message_t* protocol_create_raw_message(message_t* message)
{
    raw_message_t* raw_message;

    if(message == NULL) return NULL;

    U32 message_size = message->data_size + PROTOCOL_MIN_LENGTH;

    if( PROTOCOL_MALLOC(raw_message, raw_message_t, 1) )
    {
    	exception_handler(EXCEPTION_MEMORY_MALLOC, (void*)LINEAT);
    	return NULL;
    }

    if( PROTOCOL_MALLOC(raw_message->data, U8, message_size) )
    {
    	exception_handler(EXCEPTION_MEMORY_MALLOC, (void*)LINEAT);
    	PROTOCOL_FREE(raw_message);
    	return NULL;
    }


    raw_message->size = message_size;

    U32toU8x4(message_size, raw_message->data);

    raw_message->data[4] = message->group;
    raw_message->data[5] = message->type;
    raw_message->data[6] = message->type_extension;

    /// @bug don't know why memcpy doesn't work here!? protocol crash quickly
    //memcpy(raw_message->data+PROTOCOL_MIN_LENGTH, message->data, message->data_size);
    my_memcpy(raw_message->data+PROTOCOL_MIN_LENGTH, message->data, message->data_size);
    /*
     * for(i=0;i<message->data_size;i++)
    	raw_message->data[PROTOCOL_MIN_LENGTH+i] =  message->data[i];
    */


    return raw_message;
}
void protocol_message_free(message_t **message)
{
	PROTOCOL_FREE((*message)->data);
	PROTOCOL_FREE(*message);
}
void protocol_raw_message_free(raw_message_t **message)
{
	PROTOCOL_FREE((*message)->data);
	PROTOCOL_FREE(*message);
}
static U32 proto_U8x4toU32(U8* in)
{
	U32 u= U8x4toU32(in);
    if(u > 64){
    	HANDLE_EXCEPTION(EXCEPTION_PROTOCOL_MESSAGE, (void*)LINEAT);
    }
    return u;
}
S16 calcrc(U8 *ptr, S16 count)
{
	S16 crc;
    U8 i;

    crc = 0;
    while (--count >= 0)
    {
        crc = crc ^ (S16) *ptr++ << 8;
        i = 8;
        do
        {
            if (crc & 0x8000)
                crc = crc << 1 ^ 0x1021;
            else
                crc = crc << 1;
        } while(--i);
    }
    return (crc);
}
