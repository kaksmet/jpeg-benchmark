#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include <jpeglib.h>

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
    uint8_t *data = read_file(argv[1], &len);
    int iterations = atoi(argv[2]);

    for (int i = 0; i < iterations; i++) {
        struct jpeg_decompress_struct info;
        struct jpeg_error_mgr err;

        jpeg_create_decompress(&info);
        info.err = jpeg_std_error(&err);

        jpeg_mem_src(&info, data, len);

        jpeg_read_header(&info, TRUE);
        jpeg_start_decompress(&info);

        uint8_t *buffer = malloc(info.output_width * info.output_height * info.output_components);
        uint8_t *scanline = buffer;

        while (info.output_scanline < info.output_height) {
            int count = jpeg_read_scanlines(&info, (JSAMPARRAY)&scanline, 1);
            scanline += count * info.output_width * info.output_components;
        }

        free(buffer);
        jpeg_finish_decompress(&info);
        jpeg_destroy_decompress(&info);
    }

    free((void *)data);

    return 0;
}
