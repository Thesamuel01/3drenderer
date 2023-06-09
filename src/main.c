#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "display.h"
#include "vector.h"

bool is_running = false;

void setup(void) {
  // Allocate the required memory in bytes to hold the color buffer
	color_buffer = (u_int32_t*) malloc(sizeof(u_int32_t) * window_width * window_height);

  //  Creating a SDL texture that is used to display the clor buffer
	color_buffer_texture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		window_width,
		window_height
	);
}

void process_input(void) {
  SDL_Event event;
  SDL_PollEvent(&event);

  switch (event.type) {
    case SDL_QUIT:
      is_running = false;
      break;

    case SDL_KEYDOWN:
      if (event.key.keysym.sym == SDLK_ESCAPE) {
        is_running = false;
      }
      
      break;
    
    default:
      break;
  }
}

void update(void) {

}

void render(void) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  draw_grid();

  draw_pixel(20, 20, 0xFFFFFF00);
  draw_rect(700, 200, 500, 200, 0xFF459802);

	render_color_buffer();
	clear_color_buffer(0xFF000000);

	SDL_RenderPresent(renderer);
}

int main(void) {
  is_running = initialize_window();

  setup();

  vec3_t myvector = { 2.0, 3.0, -4.0 };

  while (is_running) {
    process_input();
    update();
    render();
  }
  
	destroy_window();

  return 0;
}