#include "main.h"

int main(int argc, char *argv[]) {
  char *proj_name;
  git_repository *repo;
  if (argc < 1) {
    printf("Not Enough Arguments!");
    return 1;
  }
  if (argc < 2) {
    proj_name = "main";
  } else {
    proj_name = argv[1];
  }

  if (file_exists("Makefile")) {
    printf("Makefile Exists! \n");
    return 1;
  }
  errno = 0;
  create_makefile(proj_name);
  create_file("main.c", "#include \"main.h\" \n");
  create_file("main.h", NULL);
  if (errno != 0) {
    printf("Error while creating files!");
    return 1;
  }
  char cwd[PATH_MAX];
  git_libgit2_init();
  git_repository_init(&repo, getcwd(cwd, sizeof(cwd)), 0);
  if (errno != 0) {
    printf("Error during git init");
    return 1;
  }
}

void create_makefile(char *proj_name) {
  errno = 0;
  int fd = access("Makefile", W_OK);
  if (fd == -1) {
    perror("Error!");
    exit(1);
  }
  FILE *fp = fopen("Makefile", "a");
  fprintf(fp, "all:\n\tcc main.c -Wall -lm -o %s", proj_name);
  fclose(fp);
}

void create_file(char *fname, char *contents) {
  errno = 0;
  int fd = access(fname, W_OK);
  if (fd == -1) {
    perror("Error!");
    exit(1);
  }
  FILE *fp = fopen(fname, "a");
  if (contents != NULL) {
    fprintf(fp, "%s", contents);
  }
  fclose(fp);
}

bool file_exists(char *fname) {
  if (access(fname, F_OK) == 0) {
    return true;
  } else {
    return false;
  }
}
