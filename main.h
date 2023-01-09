#include <git2.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>

bool file_exists(char *);
void create_makefile(char *);
void create_file(char *, char *);
