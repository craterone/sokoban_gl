#define STB_IMAGE_RESIZE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_STATIC
#include "stb_image_resize.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class stbir_context {
public:
  stbir_context() {
    size = 1000000;
    memory = malloc(size);
  }

  ~stbir_context() { free(memory); }

  size_t size;
  void *memory;
} g_context;

int main() {
  int w, h, n;
  const char *file = "assets/tileset.png";
  unsigned char *input_data = stbi_load(file, &w, &h, &n, 0);

  if (input_data == NULL)
    return 0;

  int new_w = w / 2.5;
  int new_h = h / 2;

  float s0 = 0.17;
  float t0 = 0.1;
  float s1 = 0.3;
  float t1 = 0.3;
  unsigned char *output_data =
      (unsigned char *)malloc(new_w * new_h * n * sizeof(unsigned char));

  // float x_scale = 1;
  // float y_scale = 1;
  // float x_offset = 1;
  // float y_offset = 1;
  stbir_resize_region(input_data, w, h, 0, output_data, new_w, new_h, 0,
                      STBIR_TYPE_UINT8, n, STBIR_ALPHA_CHANNEL_NONE, 0,
                      STBIR_EDGE_CLAMP, STBIR_EDGE_CLAMP, STBIR_FILTER_BOX,
                      STBIR_FILTER_CATMULLROM, STBIR_COLORSPACE_SRGB,
                      &g_context, s0, t0, s1, t1);
  // stbir_resize_subpixel(input_data, w, h, 0, output_data, new_w, new_h, 0,
  //                       STBIR_TYPE_UINT8, n, STBIR_ALPHA_CHANNEL_NONE, 0,
  //                       STBIR_EDGE_CLAMP, STBIR_EDGE_CLAMP, STBIR_FILTER_BOX,
  //                       STBIR_FILTER_CATMULLROM, STBIR_COLORSPACE_SRGB,
  //                       &g_context, x_scale, y_scale, x_offset, y_offset);

  int a = stbi_write_png("a.png", new_w, new_h, n, output_data, 0);
  printf("result %d", a);

  free(output_data);
  stbi_image_free(input_data);

  return 0;
}