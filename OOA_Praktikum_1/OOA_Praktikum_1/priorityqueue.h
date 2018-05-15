#pragma once
#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <stdio.h>
#include <malloc.h>
#include <assert.h>

/*  Asserts:
size must be greater or equal than NULL
priority must be greater or equal than NULL
*/

struct priorityqueue_t {
    struct pqentry_t *first;
    struct pqentry_t *last;
	int entries;
};

struct pqentry_t {
    char *value;
    float priority;
    struct pqentry_t *next_entry;
};

void check_func(char message[])		//C++ Catch
{	
    printf("%s", message);
}

struct priorityqueue_t *pqueue_create() //create pq
{
    struct priorityqueue_t *pq = malloc(sizeof(struct priorityqueue_t));

	if (!pq)
	{
		check_func("ALLOCATE MEMORY FOR QUEUE:\nFAIL\n");
		return 0;
	}
	check_func("ALLOCATE MEMORY FOR QUEUE:\nPASS\n");
    pq->first = NULL;
    pq->last = NULL;
    pq->entries = 0;
	assert(pq->entries >= 0);
    return pq;
}

struct pqentry_t *create_entry(char *value, float p) //create entry
{
    struct pqentry_t *new_entry = (struct pqentry_t *) malloc(sizeof(struct pqentry_t));

	if (!new_entry)
	{
		check_func("ALLOCATE MEMORY FOR ENTRY:\nFAIL\n");
		return 0;
	}
	check_func("ALLOCATE MEMORY FOR ENTRY:\nPASS\n");
    new_entry->value = value;
    new_entry->priority = p;
    new_entry->next_entry = NULL;
	assert(new_entry->priority >= 0);
    return new_entry;
}

void pqueue_insert(struct priorityqueue_t *pq, char *value, float p) //insert new element 
{
    struct pqentry_t *new_entry = create_entry(value, p);

    if (pq->entries == 0)	//when pq empty insert direct
	{
        pq->first = new_entry;
        pq->last = new_entry;
        pq->entries = 1;
        return;
    }
	//search for correct prio value
    if (new_entry->priority >= pq->last->priority)
	{
        struct pqentry_t *last_entry = pq->last;
        last_entry->next_entry = new_entry;
        pq->last = new_entry;
    } 
	else if (new_entry->priority <= pq->first->priority) 
	{
        struct pqentry_t *first_stored_event = pq->first;
        pq->first = new_entry;
        new_entry->next_entry = first_stored_event;
    }
	else 
	{
        struct pqentry_t *current_event = pq->first;
        while (current_event->next_entry != NULL) 
		{
            if (new_entry->priority <= current_event->next_entry->priority) 
			{
                if (new_entry->priority >= current_event->priority) 
				{
                    struct pqentry_t *next = current_event->next_entry;
                    current_event->next_entry = new_entry;
                    new_entry->next_entry = next;
                    break;
                }
            }
            current_event = current_event->next_entry;
        }
    }
    pq->entries++;
}

char *pqueue_extractMin(struct priorityqueue_t *pq) //returns the element value with the highest priority
{
    if (pq->entries == 0) {
		check_func("EXTRACT:\n FAIL: EMPTY QUEUE\n");
        return 0;
    }

    struct pqentry_t *current_entry = pq->first;
    char *tempval = current_entry->value;

    if (pq->entries == 1) 
	{
        pq->first = NULL;
        pq->last = NULL;
        pq->entries = 0;
    }
	else
	{
        pq->first = current_entry->next_entry;
        pq->entries--;
    }
	check_func("EXTRACT:\n PASS: EMPTY QUEUE\n");
    return tempval;
}

void pqueue_remove(struct priorityqueue_t *pq, char *value) //removes an element of the queue by the given value
{
    struct pqentry_t *current_entry = pq->first;
    struct pqentry_t *previous_entry = NULL;
    if (current_entry == NULL) 
	{
        return;
    }

    while (current_entry->next_entry != NULL) 
	{
        if (current_entry->value == value)
		{
            if (previous_entry == NULL) 
			{
                pq->first = current_entry->next_entry;
                free(current_entry);
                break;
            }
            previous_entry->next_entry = current_entry->next_entry;
            free(current_entry);
            break;
        }
        previous_entry = current_entry;
        current_entry = current_entry->next_entry;
    }
    pq->entries--;
}

//Changes via removing and re inserting. TODO: change value and pointer in queue
void pqueue_decreaseKey(struct priorityqueue_t *pq, char *value, float p)
{
	pqueue_remove(pq, value);
	pqueue_insert(pq, value, p);
}

/**
 * destroy's the queue
 * @param pq
 */
void pqueue_destroy(struct priorityqueue_t *pq)
{
    if (pq) 
	{
        if (pq->first)		//free all elements
		{ 
            struct pqentry_t *current = pq->first;
            while (current->next_entry) 
			{
                struct pqentry_t *element = current;
                current = current->next_entry;
                free(element);
            }
        }
        pq = NULL; //TODO check if needed
        free(pq);
    }
}

#endif