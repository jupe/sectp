/**
   \file message_handler.h


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

*/

#ifndef MESSAGE_HANDLER_H_INCLUDED
#define MESSAGE_HANDLER_H_INCLUDED

#include "protocol.h"


/**
*   Handle message
*   @param message  message to be handling
*   @return none
*/
extern message_t* handle_message(	const message_t			*const message);

#endif // MESSAGE_HANDLER_H_INCLUDED
