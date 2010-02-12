/*
 * message_enumerations.h
 *
 *  Created on: 31.7.2009
 *      Author: jussiva
 */

#ifndef MESSAGE_ENUMERATIONS_H_
#define MESSAGE_ENUMERATIONS_H_

/**
*   protocol message group
*/
typedef enum
{
    MESSAGE_GROUP_NONE = 0,
    MESSAGE_GROUP_QUERY,
    MESSAGE_GROUP_SET,
    MESSAGE_GROUP_RESPONSE,
    MESSAGE_GROUP_RESPONSE_OK,
    MESSAGE_GROUP_RESPONSE_FALSE,
    MESSAGE_GROUP_RESPONSE_NOT_IMPLEMENTED,
} MESSAGE_GROUP;

/**
*   protocol message type
*/
typedef enum
{
    MESSAGE_TYPE_NONE = 0,
    MESSAGE_TYPE_OK,
    MESSAGE_TYPE_PING,

    MESSAGE_TYPE_MEASURE_N_TIMES,
    MESSAGE_TYPE_MEASURE_BREAK,
    MESSAGE_TYPE_MEASURE_STATE,

    MESSAGE_TYPE_SUM_DATA,
    MESSAGE_TYPE_SQUARE_SUM_DATA,
    MESSAGE_TYPE_HISTOGRAM,
    MESSAGE_TYPE_MEASURE_COUNTER,

    MESSAGE_TYPE_VERSION,
    MESSAGE_TYPE_MEASURE_TIMER,
    MESSAGE_TYPE_MEASURE_TIME,

    MESSAGE_TYPE_SEND_TO_TDC,
    MESSAGE_TYPE_RECEIVE_FROM_TDC,
    MESSAGE_TYPE_QUERY_FROM_TDC,

    MESSAGE_TYPE_EXCEPTION,

    MESSAGE_TYPE_FORCE_KILL,	//kill some operation
    MESSAGE_TYPE_FORCE_ABORT,	//break measurement operation
    MESSAGE_TYPE_FORCE_RESTART,

    MESSAGE_TYPE_MEMORY,

    MESSAGE_TYPE_RAW_TDC_DATA

} MESSAGE_TYPE;

/**
*   protocol message type extension
*/
typedef enum
{
    MESSAGE_TYPE_EXTENSION_NONE = 0,
    MESSAGE_TYPE_EXTENSION_OK,

    MESSAGE_TYPE_EXTENSION_MEASURE_BEGIN,
    MESSAGE_TYPE_EXTENSION_MEASURE_END,

    MESSAGE_TYPE_EXTENSION_LAST_STOP,
    MESSAGE_TYPE_EXTENSION_LAST_WIDTH_TIME,
    MESSAGE_TYPE_EXTENSION_LAST_BUT_ONE_STOP,
    MESSAGE_TYPE_EXTENSION_LAST_BUT_ONE_WIDTH_TIME,
    MESSAGE_TYPE_EXTENSION_FIRST_STOP,
    MESSAGE_TYPE_EXTENSION_FIRST_WIDTH_TIME,
    MESSAGE_TYPE_EXTENSION_START_INTERPOLATOR,

    MESSAGE_TYPE_EXTENSION_STOP1_INTERPOLATOR,
    MESSAGE_TYPE_EXTENSION_STOP2_INTERPOLATOR,
    MESSAGE_TYPE_EXTENSION_STOP3_INTERPOLATOR,
    MESSAGE_TYPE_EXTENSION_STOP4_INTERPOLATOR,
    MESSAGE_TYPE_EXTENSION_STOP5_INTERPOLATOR,
    MESSAGE_TYPE_EXTENSION_STOP6_INTERPOLATOR,



    MESSAGE_TYPE_EXTENSION_SDRAM_SIZE,
    MESSAGE_TYPE_EXTENSION_SDRAM_USAGE,
    MESSAGE_TYPE_EXTENSION_SRAM_SIZE,
    MESSAGE_TYPE_EXTENSION_SRAM_USAGE

} MESSAGE_TYPE_EXTENSION;

typedef enum
{
	MESSAGE_TYPE_EXTENSION_HISTOGRAM_WINDOW_SIZE=1,
	MESSAGE_TYPE_EXTENSION_HISTOGRAM_WINDOW_MIN=2,
	MESSAGE_TYPE_EXTENSION_HISTOGRAM_WINDOW_MAX=3,
	MESSAGE_TYPE_EXTENSION_HISTOGRAM_PACKAGE=4,
} MESSAGE_TYPE_EXTENSION_HISTOGRAM;

#endif /* MESSAGE_ENUMERATIONS_H_ */
