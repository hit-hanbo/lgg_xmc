#ifndef QUEUE_H_
#define QUEUE_H_

#include "stdio.h"
#include "XMC4500.h"

/*
 *    Queue Options Error code define
 */
#define  LGG_QUEUE_OK           0x00
#define  LGG_QUEUE_ERR_MALLOC   0xFF

#define  LGG_QUEUE_EMPTY    0x11
#define  LGG_QUEUE_NONEMPTY 0xEE

#define  LGG_QUEUE_FULL     0x22
#define  LGG_QUEUE_NONFULL  0xDD

typedef  uint32_t               LGG_QUEUE_DATA_TYPE;
#define  LGG_QUEUE_SIZE         12

/*
 *   Define Queue Struct
 */
typedef struct
{
	uint32_t                data[LGG_QUEUE_SIZE];
	uint8_t                 head;
	uint8_t                 tail;
}LGG_Queue_TypeDef;

/*
 *   Function Declaration
 */
uint8_t lgg_queue_init(LGG_Queue_TypeDef* queue);
uint8_t lgg_queue_isEmpty(LGG_Queue_TypeDef* queue);
uint8_t lgg_queue_isFull(LGG_Queue_TypeDef* queue);
uint8_t lgg_queue_push_data(LGG_Queue_TypeDef* queue, LGG_QUEUE_DATA_TYPE data);
uint8_t lgg_queue_pop_data(LGG_Queue_TypeDef* queue, LGG_QUEUE_DATA_TYPE* data);
uint8_t lgg_queue_get_head_data(LGG_Queue_TypeDef* queue, LGG_QUEUE_DATA_TYPE* data);
uint8_t lgg_queue_clear(LGG_Queue_TypeDef* queue);

#endif

