#include "main.h"

int main(int argc, char *argv[]) {
  char *proj_name;
  git_repository *repo;
  char cwd[PATH_MAX];
  errno = 0;

  if (access(getcwd(cwd, sizeof(cwd)), W_OK) == -1) {
    perror("Error!");
    exit(errno);
  }

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
  git_libgit2_init();
  git_repository_init(&repo, getcwd(cwd, sizeof(cwd)), 0);
  if (errno != 0) {
    printf("Error during git init");
    return 1;
  }
}

void create_makefile(char *proj_name) {
  FILE *fp = fopen("Makefile", "a");
  fprintf(fp, "all:\n\tcc main.c -Wall -lm -o %s\n", proj_name);
  fprintf(fp, "clean:\n\t rm %s \n", proj_name);
  fprintf(fp, "install:\n\t cp %s /usr/local/bin \n", proj_name);
  fclose(fp);
}

void create_file(char *fname, char *contents) {
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
