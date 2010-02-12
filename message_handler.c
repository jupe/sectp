/**
   message_handler.h

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
#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


#include "linked_list.h"
#include "protocol.h"
#include "message_enumerations.h"
#include "message_handler.h"


/**
*	Example handle function for Handle set-type of message
*/
static Bool handle_set_message(		const message_t		*const message,
									message_t			**new_tx_message);							
/**
*	Example handle function for Handle query-type of message
*/
static Bool handle_query_message(	const message_t		*const message);



message_t* handle_message(	const message_t			*const message
							const LinkedList_t 		*const histogramNodes)
{
	message_t *new_tx_message=0;
	Bool implemented = TRUE;
	if(message == NULL) return NULL;

    switch(message->group)
    {
        case(MESSAGE_GROUP_QUERY):
        	implemented = handle_query_message(message,dma_tdc, &new_tx_message);
            break;
        case(MESSAGE_GROUP_SET):
        	implemented = handle_set_message(message,dma_tdc,&new_tx_message);
            break;
        case(MESSAGE_GROUP_NONE):
            //client not receive any responses,,yet, maybe never
        case(MESSAGE_GROUP_RESPONSE):
        case(MESSAGE_GROUP_RESPONSE_NOT_IMPLEMENTED):
        default:
        	new_tx_message =
					protocol_create_message(  	MESSAGE_GROUP_RESPONSE,
												MESSAGE_TYPE_NONE,
												MESSAGE_TYPE_EXTENSION_NONE,
												(U8*)"WTF?",3
											);
        	break;
    }
    if(implemented == FALSE){
    	new_tx_message =
					protocol_create_message(  	MESSAGE_GROUP_RESPONSE_NOT_IMPLEMENTED,
												message->type,
												message->type_extension,
												NULL,0
												);
    }
    else if(new_tx_message == 0)
    {
    	new_tx_message =
				protocol_create_message(  	MESSAGE_GROUP_RESPONSE,
											MESSAGE_TYPE_OK,
											MESSAGE_TYPE_EXTENSION_NONE,
											NULL,0
											);
    }

    return new_tx_message;
}
static Bool handle_set_message(			const message_t			*const message,
										message_t** new_tx_message)
{
	*new_tx_message=0;
	Bool implemented = FALSE;
	U8 extension = (U8)message->type_extension;
	U32 u32;
	S32 s32a,s32b;
	U8 *ptr;
	MESSAGE_GROUP response_group = MESSAGE_GROUP_RESPONSE;

	switch(message->type)
	{
		case(MESSAGE_TYPE):
	        	*new_tx_message =
							protocol_create_message(  	response_group,
														message->type,
														MESSAGE_TYPE_EXTENSION_OK,
														NULL, 0
														);
				implemented = TRUE;
	        	break;
		default: break;
	}

	return implemented;
}
static Bool handle_query_message(	const message_t				*const message,
									message_t** new_tx_message)
{
	*new_tx_message=0;
	U8	*buffer=0, *ptr=0;
	U32 length=0;
	Bool implemented = FALSE;

    switch(message->type)
    {
        case(MESSAGE_TYPE_NONE):					//Type: 0
        	*new_tx_message =
					protocol_create_message(  	MESSAGE_GROUP_RESPONSE,
												MESSAGE_TYPE_NONE,
												MESSAGE_TYPE_EXTENSION_NONE,
												(U8*)"WTF, NO TYPE?",13
												);
			implemented = TRUE;
            break;
        case(MESSAGE_TYPE_OK):						//Type: 1
        	//why we received OK message?
            break;
        case(MESSAGE_TYPE_PING):					//Type: 2
        	*new_tx_message =
					protocol_create_message(  	MESSAGE_GROUP_RESPONSE,
												MESSAGE_TYPE_PING,
												MESSAGE_TYPE_EXTENSION_OK,
												NULL,0
												);
			implemented = TRUE;
            break;

        default:
        	break;
    }
    free(buffer);
    return implemented;
}