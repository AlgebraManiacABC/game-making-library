/********************************************************************************
 * linked_list.h
 * 
 ********************************************************************************/

#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <stddef.h>

typedef struct gm_Node_s gm_Node_t;
typedef struct gm_List_s gm_List_t;

/**
 * Creates a new (empty) Linked List
 * @returns the new `gm_List_t *`
 */
gm_List_t * gm_createList();

/**
 * Gets the list's node count
 * @param list the list to query
 * @returns the number of nodes in the provided list
 */
size_t gm_getListLength(gm_List_t * list);

/**
 * Destroys all nodes of and
 * frees all memory associated with a list
 * @param list the list to destroy
 */
void gm_destroyList(gm_List_t * list);

/**
 * Inserts a node at the head of the list,
 *  filling it with the specified data
 * @param list the list to change
 * @param data the data to insert
 * @returns EXIT_SUCCESS or EXIT_FAILURE
 */
int gm_insertNodeAtHead(gm_List_t * list, void * data);

/**
 * Inserts a node at the end of the list,
 *  filling it with the specified data
 * @param list the list to change
 * @param data the data insert
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
int gm_insertNodeAtTail(gm_List_t * list, void * data);

/**
 * Gets the data from the node at the given index
 * @param list the list from which to get data
 * @param index the index of the data node
 * @returns the data at the given index
 */
void * gm_getNodeAtIndex(gm_List_t * list, size_t index);

/**
 * Gets the data from the head node of the list
 * @param list the list from which to get data
 * @return the data at the head node
 */
void * gm_getNodeAtHead(gm_List_t * list);

/**
 * Gets the data from the tail (final) node of the list
 * @param list the list from which to get data
 * @return the data at the tail node
 */
void * gm_getNodeAtTail(gm_List_t * list);

/**
 * Remove a node by index, returning its data
 * @param list the list to change
 * @param index the index of the node to delete
 * @return the data from the deleted node
 */
void * gm_removeNodeAtIndex(gm_List_t * list, size_t index);

/**
 * Remove the head node of a list, returning its data
 * @param list the list to change
 * @return the data from the deleted node
 */
void * gm_removeNodeAtHead(gm_List_t * list);

/**
 * Remove the tail (final) node of a list, returning its data
 * @param list the list to change
 * @return the data from the deleted node
 */
void * gm_removeNodeAtTail(gm_List_t * list);

/**
 * Searches through the list for a node with matching data,
 *  then removes it.
 * @param list the list to change
 * @param data a pointer to compare with each node
 * @returns EXIT_SUCCESS on node removal, else EXIT_FAILURE (see gm_getError)
 */
int gm_removeNodeMatchingData(gm_List_t * list, void * data);

/**
 * Create a new node with data at the end of a list
 * @param list the list to change
 * @param data the data to append
 */
void gm_pushObject(gm_List_t * list, void * data);

/**
 * Destroy the last node at the end of a list, returning its data
 * @param list the list to change
 * @returns the data extracted from the node
 */
void * gm_popObject(gm_List_t * list);

#endif