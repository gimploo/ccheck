#include "common.h"

typedef struct {
    char *name;
    size_t size;
} file_t;

static FILE * program_create_generic_template_file(void)
{
    FILE *tmp = fopen("tmp.c", "w");

    // NOTE: for the time being a quick hack to resolve that one annoying
    // problem (apparantely #include cant be in the same line as int main(void))
    char header_buffer[] = 
                    "#include <stdio.h> \n"
                    "#include <stdlib.h> \n"
                    "#include <stdbool.h> \n"
                    "#include <unistd.h> \n"
                    "#include <assert.h> \n"
                    "int main(int argc, char *argv[]) {\n";

    if (tmp == NULL) return NULL;
    fwrite(header_buffer, 1, sizeof(header_buffer), tmp);
    fseek(tmp, sizeof(header_buffer)-1, SEEK_SET); // Now the file ptr is pointing to the newline character
    return tmp;
}

size_t file_get_size(char *file_path)
{
    FILE *fp = fopen(file_path, "r");
    if (fp == NULL) {
        fprintf(stderr, ERROR"%s Unable to open file\n", __func__);
        return -1;
    }
    fseek(fp, 0L, SEEK_END);
    size_t file_size = ftell(fp);
    fclose(fp);
    return file_size;
}

static void file_print_to_stdout(char *name, size_t size)
{
    char buffer[MAXSIZE] = {0};
    FILE *fp = fopen(name, "r");
    if (fp == NULL) {
        fprintf(stderr, ERROR"%s Unable to open file\n", __func__);
        exit(1);
    }
    printf("\033[0;35m\n====PROGRAM=====\n\033[0m");
    fread(buffer, size, 1, fp);
    printf("%s\n", buffer);
    printf("\033[0;35m\n================\n\033[0m");
    fclose(fp);
}

bool program_write_user_input_to_file(char *buffer, size_t size)
{
    FILE *tmp = program_create_generic_template_file();
    if (tmp == NULL) return false;
    fwrite(buffer, size, 1, tmp); // Ignores the null character at the end
    fputs("\n}\0", tmp);
    fclose(tmp);
    return true;
}

typedef struct {
    char content[MAXSIZE];
    size_t content_size;
    size_t cursor; // keeps track of last stdin char entry before null char
} interpreter_t;

static inline size_t program_inc_content(interpreter_t *program)
{
    program->cursor = program->content_size;
    program->content_size++;
    return (program->cursor);
}

static inline void program_read_stdin(interpreter_t *program)
{
    char chr;
    while ((chr = getchar()) != '\n') program->content[program_inc_content(program)] = chr;
    program->content[program_inc_content(program)] = '\n'; //sets a space after every line
}

static inline bool program_check_user_pressed_esc(interpreter_t *program)
{
    if (program->content[--program->cursor] == 0x1B) {
        program->content[--program->content_size] = '\0';
        program->content[program->cursor] = '\n';
        return true;
    }
    return false;
}

static size_t run_command_on_linux(char *command)
{
#ifdef DEBUG
    printf(DBG"CMD: %s\n", command);
#endif //DEBUG
    FILE * fp = popen(command, "r");
    char buffer[MAXSIZE];
    if (fp == NULL) {
        fprintf(stderr, "compile_program_get_output: fp is null\n");
        fclose(fp);
        exit(1);
    }
    while (fscanf(fp, "%s", buffer) != EOF) printf("%s ", buffer); 

    // Exit status of gcc
    size_t exit_status =  WEXITSTATUS(pclose(fp));
#ifdef DEBUG
    printf(DBG"Exit code: %li\n", exit_status);
#endif //DEBUG
    return exit_status;
}

static bool gcc_compile_program(char *file_path) 
{
    if (file_path == NULL) {
       if (run_command_on_linux("gcc tmp.c") != 0) return false;
    } else {
        char cmd_buf[KB] = {0};
        snprintf(cmd_buf, KB, "gcc %s", file_path);
        if (run_command_on_linux(cmd_buf) != 0) return false;
    }
    return true;
}

static inline void gcc_run_compiled_binary(void) 
{
    printf(OK"COMPILATION SUCCESSFULL\n");
    if (run_command_on_linux("./a.out") != 0) {
        fprintf(stderr, ERROR"file not found\n");
        exit(1);
    }
    printf("\n");
}

static bool file_init(file_t *file, char *name)
{
    if (file == NULL) {
        fprintf(stderr, ERROR"%s failed\n", __func__);
        return false;
    }

    file->name = name;
    file->size = file_get_size(name);
    return true;
}


int main(int argc, char *argv[])
{
    char *c_file_path = NULL;
    file_t program_file = {0};

    if (argc > 1) {
        if (!fopen(argv[1], "r")) {
            printf("USAGE: %s file.c\n", argv[0]);
            fprintf(stderr, ERROR"File doesnt exist\n");
            exit(1);
        } 
        file_t program_file = {0};
        assert(file_init(&program_file, argv[1]));
        printf(OK"FILE FOUND: %s\n", c_file_path);
    }

    // If the user passed in a file as an argument
    
    if (c_file_path != NULL) {
        if (!gcc_compile_program(program_file.name)) {
            fprintf(stderr, ERROR"COMPILATION FAILED\n");
            exit(1);
        } else {
            gcc_run_compiled_binary();
        }
        goto cleanup;
    }

    // ======================================================
    // Interperter 
    // ======================================================
    
    interpreter_t program = {0};
    while (true)
    {
        printf(CCHECK); //prints ccheck in a colored prompt
        program_read_stdin(&program);
        if (program_check_user_pressed_esc(&program)) break;
    }
    assert(program_write_user_input_to_file(program.content, program.cursor));

#ifdef DEBUG
    file_print_to_stdout("tmp.c", file_get_size("tmp.c"));
#endif //DEBUG


    if (!gcc_compile_program(NULL)) {
        fprintf(stderr, ERROR"COMPILATION FAILED\n");
        exit(1);
    } else {
        gcc_run_compiled_binary();
    }
    goto cleanup;

cleanup:
#ifndef DEBUG
        system("rm -f a.out tmp.c");
#endif //DEBUG
        return EXIT_SUCCESS;
}
