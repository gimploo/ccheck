#ifndef MY_STRING_H
#define MY_STRING_H

#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

typedef struct {
		char *data;
		size_t size;
} str_t;

// TODO: function that create a str_t according to just size

static inline str_t new_str(char *data)
{
		assert(data != NULL);
		return (str_t) {
				.data = data,
				.size = strlen(data)
		};
}

static inline str_t * new_pstr(char *data)
{
		assert(data != NULL);
		str_t * mystring = (str_t *)malloc(sizeof(str_t));
		mystring->data = data;
		mystring->size = strlen(data);
		return mystring;
}

static inline bool str_cmp(str_t a, str_t b)
{
		if (a.size != b.size)
				return false;
		for (size_t i = 0; i < a.size; i++) if (a.data[i] != b.data[i]) return false;
		return true;
}

static inline void str_destory(str_t *str)
{
		free(str->data);
		free(str);
}

#endif //MY_STRING_H
