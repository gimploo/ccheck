/*
 * This header prints debug info when allocating and freeing 
 * memory from the heap
 */
#ifndef MY_DEBUG_H
#define MY_DEBUG_H

#include <stdio.h>
#include <stdlib.h>

#ifdef DEBUG

#define malloc(n) debug_malloc(n, __FILE__, __LINE__, __func__)
#define realloc(n, m) debug_realloc(n, m, __FILE__, __LINE__, __func__)
#define free(n) debug_free(n, #n, __FILE__, __LINE__, __func__) 


extern void *debug_malloc(size_t size, char *file_path, size_t line_num, const char *func_name);
extern void *debug_realloc(void *pointer, size_t size, char *file_path, size_t line_num, const char *func_name);
extern void debug_free(void *pointer, char *pointer_name ,char *file_path, size_t line_num, const char *func_name);


#endif //DEBUG

/*
 * TODO: More detailed debug, maybe giving name of the pointer that memory is allocated to
 */
#endif //MY_DEBUG_H
