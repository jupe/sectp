# Introduction #

## How to use this protocol ##

Protocol use transfer and receive buffers. Buffers is created by linked list method. (wiki: linked list). And it's possible to push/pop messages like FIFO-buffers.

Includes:
```
#include "protocol.h"
#include "message_handler.h"
```

Buffers:
```
message_buffer_t* buffers = protocol_allocate();
```

just push new message to tx buffer

```
message_t* msg = protocol_create_message( MESSAGE_GROUP_PING, MESSAGE_TYPE_NONE, MESSAGE_TYPE_EXTENSION_NONE, 0,0);
protocol_push( buffers->tx , &msg );
```
don't free msg because it' will be use later when pop msg to transferring...

Reading message from "bytestream":
```
protocol_push( buffers->rx, protocol_parse_raw_message(U8 *input, int inputlen) );
```

also need to handle messages. Message handler can also construct new message. It can be passed directly to the transfer buffer).
```
protocol_push( buffers->tx, handle_message( protocol_pop_botton( buffers->rx) ) );
```

and delete handled rx message from buffer:
```
protocol_pop_delete( buffers->rx);
```

# Details #
Just so simple as can.. or is it? if You think it can be more simple, explain what you are thinking to me and maybe I learn more.... =)