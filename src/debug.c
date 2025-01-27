#include "cube3d.h"

void print_string_array(char **array, int n) {
    for (int i = 0; i < n; i++) {
        if (array[i] != NULL) {
            printf("%s\n", array[i]);
        } else {
            printf("(null)\n");
        }
    }
}
