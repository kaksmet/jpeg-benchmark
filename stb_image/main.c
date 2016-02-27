#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

uint8_t *read_file(const char *path, size_t *len) {
    FILE *file = fopen(path, "rb");
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    uint8_t *buffer = malloc(size);
    fread(buffer, size, 1, file);
    fclose(file);

    *len = size;

    return buffer;
}

int main(int argc, const char *argv[]) {
    size_t len = 0;
    const uint8_t *data = read_file(argv[1], &len);
    int iterations = atoi(argv[2]);
    bool failure = false;
    int width, height, component_count;

    for (int i = 0; i < iterations; i++) {
        stbi_uc *result = stbi_load_from_memory(data, len, &width, &height, &component_count, 0);
        failure = failure || result == NULL;
        stbi_image_free((void *)result);
    }

    free((void *)data);

    return failure? 1 : 0;
}
