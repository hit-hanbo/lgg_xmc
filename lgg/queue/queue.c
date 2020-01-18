#include "queue.h"
#include "stdlib.h"

/*
 *    LGG Driver for ARM Cortex-M
 *    Circular Queue (FIFO)
 *    < @History: 2019-04-08 Add basic options >
 *    <           2019-12-16 Change name >
 *    <			  2020-01-18             >
 *
 */

/*
 *	 Circular Queue Init Funtion
 *   @ Brief : Init Circular Queue
 *   @ param : pointer to queue handler
 *   @ retval: errcode
 *
 */
uint8_t lgg_queue_init(LGG_Queue_TypeDef* queue)
{
	if(queue == NULL)
	{
		queue = (LGG_Queue_TypeDef*) malloc(sizeof(LGG_Queue_TypeDef));
		if(queue == NULL)
		{
			return LGG_QUEUE_ERR_MALLOC;
		}
	}
	queue->head = 0;
	queue->tail = 0;
	return LGG_QUEUE_OK;
}

/*
 *	 Check if queue is empty
 *   @ Brief : Check if queue is empty
 *   @ param : pointer to queue handler
 *   @ retval: errcode
 *
 */
uint8_t lgg_queue_isEmpty(LGG_Queue_TypeDef* queue)
{
	if(queue->head == queue->tail)
	{
		return LGG_QUEUE_EMPTY;
	}
	else
	{
		return LGG_QUEUE_NONEMPTY;
	}
}

/*
 *	 Check if queue is full
 *   @ Brief : Check if queue is full
 *   @ param : pointer to queue handler
 *   @ retval: errcode
 *
 */
uint8_t lgg_queue_IsFull(LGG_Queue_TypeDef* queue)
{
	if( (queue->tail + 1) % LGG_QUEUE_SIZE  == queue->head )
	{
		return LGG_QUEUE_FULL;
	}
	else
	{
		return LGG_QUEUE_NONFULL;
	}
}

/*
 *	 Push one data to queue
 *   @ Brief : Push one data to queue
 *   @ param : pointer to queue handler, data
 *   @ retval: errcode
 *
 */
uint8_t lgg_queue_push_data(LGG_Queue_TypeDef* queue, LGG_QUEUE_DATA_TYPE data)
{
	if(lgg_queue_isFull(queue) == LGG_QUEUE_FULL)
	{
		return LGG_QUEUE_FULL;
	}
	else
	{
		queue->tail = (queue->tail + 1) % LGG_QUEUE_SIZE;
		queue->data[queue->tail] = data;
		return LGG_QUEUE_OK;
	}
}

/*
 *	 Pop one data from queue
 *   @ Brief : Pop one data from queue
 *   @ param : pointer to queue handler, pointer to data
 *   @ retval: errcode
 *
 */
uint8_t lgg_queue_pop_data(LGG_Queue_TypeDef* queue, LGG_QUEUE_DATA_TYPE* data)
{
	if(lgg_queue_isEmpty(queue) == LGG_QUEUE_EMPTY)
	{
		return LGG_QUEUE_EMPTY;
	}
	else
	{
		queue->head = (queue->head + 1) % LGG_QUEUE_SIZE;
		*data = queue->data[queue->head];
		return LGG_QUEUE_OK;
	}
}

/*
 *	 Get Head data from queue, no POP
 *   @ Brief : Get Head data from queue but not pop it
 *   @ param : pointer to queue handler, pointer to data
 *   @ retval: errcode
 *
 */
uint8_t lgg_queue_get_head_data(LGG_Queue_TypeDef* queue, LGG_QUEUE_DATA_TYPE* data)
{
	if(lgg_queue_isEmpty(queue) == LGG_QUEUE_EMPTY)
	{
		return LGG_QUEUE_EMPTY;
	}
	else
	{
		*data = queue->data[(queue->head + 1) % LGG_QUEUE_SIZE];
		return LGG_QUEUE_OK;
	}
}

/*
 *	 Clear data from queue
 *   @ Brief : Clear data from queue
 *   @ param : pointer to queue handler
 *   @ retval: errcode
 *
 */
uint8_t lgg_queue_clear(LGG_Queue_TypeDef* queue)
{
	queue->head = 0;
	queue->tail = 0;
	return LGG_QUEUE_OK;
}


