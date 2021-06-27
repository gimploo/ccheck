#include "my_debug.h"

void *debug_malloc(size_t size, char *file_path, size_t line_num, const char *func_name)
{
    FILE *fp = fopen("debug_file.txt","w");
    fprintf(fp, "%s: In function '%s':\n", file_path, func_name);
    fprintf(fp, "%s:%li: MEMORY \033[0;32mALLOCTED\033[0m  OF SIZE:%0li\n", 
            file_path, line_num, size);
    fclose(fp);
    return malloc(size);
}

void *debug_realloc(void *pointer, size_t size, char *file_path, size_t line_num, const char *func_name)
{
    FILE *fp = fopen("debug_file.txt","w");
    fprintf(fp, "%s: In function '%s':\n", file_path, func_name);
    fprintf(fp, "%s:%li: MEMORY \033[01;34m REALLOCTED \033[0m OF SIZE:%0li\n" ,
            file_path, line_num, size);
    fclose(fp);
    return realloc(pointer, size);

}

void debug_free(void *pointer, char *pointer_name , char *file_path, size_t line_num, const char *func_name)
{
    FILE *fp = fopen("debug_file.txt","w");
    fprintf(fp, "%s: In function '%s':\n", file_path, func_name);
    fprintf(fp, "%s:%li: PTR: %s MEMORY \033[0;32m DEALLOCATED\033[0;32m\n" 
            ,file_path, line_num, pointer_name);
    fclose(fp);
    free(pointer);
}
