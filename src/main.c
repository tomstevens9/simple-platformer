#include <SDL.h>

enum {
    SCREEN_WIDTH = 1024,
    SCREEN_HEIGHT = 576,
    PLAYER_SIZE = 32,
    PLATFORM_HEIGHT = 50,
    PLAYER_SPEED = 5,
    JUMP_FORCE = 8,
};

static const float GRAVITY = 0.3F;

static const SDL_Color COLOR_BLACK = {0, 0, 0, 255};
static const SDL_Color COLOR_GREY = {100, 100, 100, 255};
static const SDL_Color COLOR_GREEN = {0, 255, 0, 255};

int main(void) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow(
        "Simple Platformer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Initialize player and platform
    SDL_Rect player = {(SCREEN_WIDTH / 2) - (PLAYER_SIZE / 2),
                       SCREEN_HEIGHT - (PLATFORM_HEIGHT * 2), PLAYER_SIZE,
                       PLAYER_SIZE};
    SDL_Rect platform = {0, SCREEN_HEIGHT - PLATFORM_HEIGHT, SCREEN_WIDTH,
                         PLATFORM_HEIGHT};

    float vel_x = 0;
    float vel_y = 0;
    SDL_bool is_jumping = SDL_FALSE;

    SDL_bool running = SDL_TRUE;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = SDL_FALSE;
            }
        }

        // Keyboard input handling
        const Uint8 *keys = SDL_GetKeyboardState(NULL);

        // Horizontal movement
        vel_x = 0;
        if (keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT]) {
            vel_x = -PLAYER_SPEED;
        }
        if (keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT]) {
            vel_x = PLAYER_SPEED;
        }

        // Jumping
        if ((keys[SDL_SCANCODE_SPACE] || keys[SDL_SCANCODE_W] ||
             keys[SDL_SCANCODE_UP]) &&
            !is_jumping) {
            vel_y = -JUMP_FORCE;
            is_jumping = SDL_TRUE;
        }

        // Apply physics
        vel_y += GRAVITY;
        player.x += (int)vel_x;
        player.y += (int)vel_y;

        // Platform collision
        if (player.y + player.h >= platform.y && vel_y > 0) {
            player.y = platform.y - player.h;
            vel_y = 0;
            is_jumping = SDL_FALSE;
        }

        // Screen boundaries
        if (player.x < 0) {
            player.x = 0;
        }
        if (player.x + player.w > SCREEN_WIDTH) {
            player.x = SCREEN_WIDTH - player.w;
        }

        // Rendering
        SDL_SetRenderDrawColor(renderer, COLOR_BLACK.r, COLOR_BLACK.g,
                               COLOR_BLACK.b, COLOR_BLACK.a);
        SDL_RenderClear(renderer);

        // Draw platform
        SDL_SetRenderDrawColor(renderer, COLOR_GREY.r, COLOR_GREY.g,
                               COLOR_GREY.b, COLOR_GREY.a);
        SDL_RenderFillRect(renderer, &platform);

        // Draw player
        SDL_SetRenderDrawColor(renderer, COLOR_GREEN.r, COLOR_GREEN.g,
                               COLOR_GREEN.b, COLOR_GREEN.a);
        SDL_RenderFillRect(renderer, &player);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
