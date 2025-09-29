/********************************************************************************
 * linked_list.c
 * Goal is to create a circularly-linked list:
 *   o<->o<->o
 *  /         \
 * o           o <- head
 *  \         /
 *   o<->o<->o
 ********************************************************************************/

#include <stdlib.h>
#include "linked_list.h"

#include "debug.h"

struct gm_Node_s
{
    gm_Node_t * prev;
    gm_Node_t * next;
    void * data;
};

struct gm_List_s
{
    gm_Node_t * head;
    size_t length;
};

gm_List_t * gm_createList()
{
    // calloc sets everything to NULL or 0
    gm_List_t * list = calloc(1, sizeof(gm_List_t));
    if (!list)
    {
        gm_setError(ERR_CODE,ERR_NOMEM);
    }
    return list;
}

gm_Node_t * gm_createNode(void * data)
{
    // calloc sets next/pref to NULL
    gm_Node_t * node = calloc(1, sizeof(gm_Node_t));
    if (!node)
    {
        gm_setError(ERR_CODE,ERR_NOMEM);
        return NULL;
    }
    node->data = data;
    return node;
}

size_t gm_getListLength(gm_List_t * list)
{
    if (!list) return 0;
    return list->length;
}

void gm_destroyList(gm_List_t * list)
{
    if (!list) return;
    while (list->head) gm_removeNodeAtHead(list);
    free(list);
}

int gm_insertNodeAtHead(gm_List_t * list, void * data)
{
    if (!list)
    {
        gm_setError(ERR_CODE,ERR_NULLP);
        return EXIT_FAILURE;
    }
    gm_Node_t * node = gm_createNode(data);
    if (!node) return EXIT_FAILURE;
    if (!list->head)
    {
        list->head = node;
        node->next = node;
        node->prev = node;
    }
    else
    {
        list->head->prev->next = node;
        list->head->prev = node;
        list->head = node;
    }
    list->length++;
    return EXIT_SUCCESS;
}

int gm_insertNodeAtTail(gm_List_t * list, void * data)
{
    if (!list)
    {
        gm_setError(ERR_CODE,ERR_NULLP);
        return EXIT_FAILURE;
    }
    gm_Node_t * node = gm_createNode(data);
    if (!node) return EXIT_FAILURE;
    if (!list->head)
    {
        list->head = node;
        node->next = node;
        node->prev = node;
    }
    else
    {
        gm_Node_t * penultimate = list->head->prev;
        penultimate->next = node;
        node->prev = penultimate;
        node->next = list->head;
        list->head->prev = node;
    }
    list->length++;
    return EXIT_SUCCESS;
}

// void * gm_getNodeAtIndex(gm_List_t * list, size_t index);

// void * gm_getNodeAtHead(gm_List_t * list);

// void * gm_getNodeAtTail(gm_List_t * list);

// void * gm_removeNodeAtIndex(gm_List_t * list, size_t index);

void * gm_removeNodeAtHead(gm_List_t * list)
{
    if (!list || !list->length) return NULL;
    void * data = list->head->data;
    list->head->prev->next = list->head->next;
    list->head->next->prev = list->head->prev;
    gm_Node_t * temp = NULL;
    if (list->length > 1) temp = list->head->next;
    free(list->head);
    list->head = temp;
    list->length--;
    return data;
}

// void * gm_removeNodeAtTail(gm_List_t * list);

int gm_removeNodeMatchingData(gm_List_t * list, void * data)
{
    if (!list || !list->length) return EXIT_FAILURE;
    gm_Node_t * search = list->head;
    for (int i=0; i<list->length; i++)
    {
        if (search->data == data)
        {
            search->prev->next = search->next;
            search->next->prev = search->prev;
            if (search == list->head) list->head = search->next;
            list->length--;
            free(search);
            if (list->length == 0) list->head = NULL;
            return EXIT_SUCCESS;
        }
        search = search->next;
    }
    return EXIT_FAILURE;
}

// void gm_pushObject(gm_List_t * list, void * data);

// void * gm_popObject(gm_List_t * list);