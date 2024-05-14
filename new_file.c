#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

char *this = NULL;

// prints the usage of the executable
void usage(void) {
  printf("usage:\n\t");
  printf("%s <filename>\n", this);
  printf("Be mindful: only the file name is expected, not a path\n");
}

void print_error_hier() {
  printf("[ERROR]: Unexpected directory hierarchy...\n");
  printf("         Expected: _ *current*\n");
  printf("                     |_ include\n");
  printf("                        |_ ...\n");
  printf("                     |_ src\n");
  printf("                        |_ ...\n");
  printf("                     |_ ...\n");
}

// Warning, the result of this function is to be freed
char *get_upper_filename(const char *fn) {
  size_t l = strlen(fn);
  char *buffer = malloc(l + 1);

  for (size_t i = 0; i < l; ++i) {
    buffer[i] = toupper(fn[i]);
  }
  buffer[l] = 0; // null-terminated string
  return buffer;
}

int folder_exists(const char *path) {
  struct stat sb;
  return (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode));
}

int file_exists(const char *path) { return access(path, F_OK) == 0; }

int main(int argc, char **argv) {
  this = argv[0];
  if (argc != 2) {
    printf("[ERROR]: expected 1 argument but got: %d\n", argc - 1);
    usage();
    exit(1);
  }
  char *file = argv[1];

  char filename_in[128] = {0};
  sprintf(filename_in, "./include/%s.h", file);

  char filename_src[128] = {0};
  sprintf(filename_src, "./src/%s.c", file);

  if (!folder_exists("include") || !folder_exists("src")) {
    print_error_hier();
    exit(1);
  }

  if (file_exists(filename_in) || file_exists(filename_src)) {
    printf("[ERROR]: File already exists !\n");
    exit(1);
  }

  FILE *inc = fopen(filename_in, "w");
  if (inc == NULL) {
    printf("[ERROR]: Could not create file \"%s\", aborting \n", filename_in);
    exit(1);
  }
  char *upper_file = get_upper_filename(file);
  fprintf(inc, "// %s HEADER FILE\n", upper_file);
  fprintf(inc, "// Paul Passeron\n\n");
  fprintf(inc, "// File created by the new_file tool !\n\n");
  fprintf(inc, "#ifndef %s_H\n", upper_file);
  fprintf(inc, "#define %s_H\n\n", upper_file);
  fprintf(inc, "#endif // %s_H\n", upper_file);
  fclose(inc);

  FILE *src = fopen(filename_src, "w");
  if (inc == NULL) {
    printf("[ERROR]: Could not create file \"%s\", aborting \n", filename_src);
    free(upper_file);
    exit(1);
  }

  fprintf(src, "// %s SOURCE FILE\n", upper_file);
  fprintf(src, "// Paul Passeron\n\n");
  fprintf(src, "#include \"../include/%s.h\"\n\n", file);
  fprintf(src, "// File created by the new_file tool !\n");

  fclose(src);
  free(upper_file);
  return 0;
}
