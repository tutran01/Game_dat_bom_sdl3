#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>

const int MAPS_ROWS = 25;
const int MAPS_COLS = 30;
const int TILE_SIZE = 40;

const int SCREEN_WIDTH = MAPS_COLS*TILE_SIZE;
const int SCREEN_HEIGHT = MAPS_ROWS*TILE_SIZE;


int tileMap[MAPS_ROWS][MAPS_COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 2, 2, 0, 2, 2, 0, 2, 2, 0, 2, 2, 0, 2, 2, 0, 2, 2, 0, 2, 2, 0, 2, 2, 0, 2, 2, 1},
    {1, 0, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 0, 1, 2, 1, 1},
    {1, 2, 2, 2, 0, 2, 0, 2, 2, 0, 2, 2, 0, 2, 2, 0, 2, 2, 0, 2, 2, 0, 2, 2, 0, 2, 2, 2, 2, 1},
    {1, 2, 1, 0, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 0, 1, 1},
    {1, 0, 2, 2, 2, 2, 0, 2, 2, 2, 2, 0, 2, 2, 2, 2, 0, 2, 2, 2, 2, 0, 2, 2, 2, 2, 0, 2, 0, 1},
    {1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 1},
    {1, 2, 0, 2, 2, 2, 2, 0, 2, 2, 2, 2, 0, 2, 2, 2, 2, 0, 2, 2, 2, 2, 0, 2, 2, 2, 2, 0, 2, 1},
    {1, 0, 1, 2, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 1},
    {1, 2, 2, 2, 0, 2, 0, 2, 2, 2, 2, 0, 2, 2, 2, 2, 0, 2, 0, 2, 2, 2, 2, 2, 0, 2, 0, 2, 2, 1},
    {1, 2, 1, 0, 1, 2, 1, 0, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 0, 1, 2, 1, 1},
    {1, 0, 2, 2, 2, 2, 0, 2, 2, 2, 2, 0, 2, 2, 2, 2, 0, 2, 2, 2, 2, 0, 2, 2, 2, 2, 0, 2, 0, 1},
    {1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 1},
    {1, 2, 0, 2, 2, 2, 2, 0, 2, 2, 2, 2, 0, 2, 2, 2, 2, 0, 2, 2, 2, 2, 0, 2, 2, 2, 2, 0, 2, 1},
    {1, 0, 1, 2, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 1},
    {1, 2, 2, 2, 0, 2, 0, 2, 2, 2, 2, 0, 2, 2, 2, 2, 0, 2, 0, 2, 2, 2, 2, 2, 0, 2, 0, 2, 2, 1},
    {1, 2, 1, 0, 1, 2, 1, 0, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 0, 1, 2, 1, 1},
    {1, 0, 2, 2, 2, 2, 0, 2, 2, 2, 2, 0, 2, 2, 2, 2, 0, 2, 2, 2, 2, 0, 2, 2, 2, 2, 0, 2, 0, 1},
    {1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 1},
    {1, 2, 0, 2, 2, 2, 2, 0, 2, 2, 2, 2, 0, 2, 2, 2, 2, 0, 2, 2, 2, 2, 0, 2, 2, 2, 2, 0, 2, 1},
    {1, 0, 1, 2, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 1},
    {1, 2, 2, 2, 0, 2, 0, 2, 2, 2, 2, 0, 2, 2, 2, 2, 0, 2, 0, 2, 2, 2, 2, 2, 0, 2, 0, 2, 2, 1},
    {1, 2, 1, 0, 1, 2, 1, 0, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 0, 1, 2, 1, 1},
    {1, 0, 2, 2, 2, 2, 0, 2, 2, 2, 2, 0, 2, 2, 2, 2, 0, 2, 2, 2, 2, 0, 2, 2, 2, 2, 0, 2, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};
int main(int argc, char* argv[]) {
  
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cout << "Lỗi khởi tạo SDL3: " << SDL_GetError() << std::endl;
        return -1;
    }

    
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (!SDL_CreateWindowAndRenderer("Game Dat Boom - SDL3", SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer)) {
        std::cout << "Lỗi tạo cửa sổ/trình vẽ: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }
    SDL_Texture* groundTex = IMG_LoadTexture(renderer, "ground.png");
    SDL_Texture* wallTex = IMG_LoadTexture(renderer, "wall.png");
    SDL_Texture* boxTex = IMG_LoadTexture(renderer, "box.png");
    
    if (!groundTex || !wallTex || !boxTex) {
        std::cout << "Lỗi: Không tìm thấy các file ảnh bản đồ! Hãy kiểm tra lại vị trí ảnh." << std::endl;
    }
    bool isRunning = true;
    SDL_Event event;

    while (isRunning) {
        
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                isRunning = false;
            }
        }

        
        SDL_SetRenderDrawColor(renderer, 20, 40, 80, 255);
        SDL_RenderClear(renderer);

        for (int r = 0; r < MAPS_ROWS; ++r) {
            for (int c = 0; c < MAPS_COLS; ++c) {

                
                SDL_FRect destRect;
                destRect.x = c * TILE_SIZE; 
                destRect.y = r * TILE_SIZE; 
                destRect.w = TILE_SIZE;
                destRect.h = TILE_SIZE;

               
                SDL_RenderTexture(renderer, groundTex, nullptr, &destRect);

                
                if (tileMap[r][c] == 1) {
                    SDL_RenderTexture(renderer, wallTex, nullptr, &destRect);
                }
               
                else if (tileMap[r][c] == 2) {
                    SDL_RenderTexture(renderer, boxTex, nullptr, &destRect);
                }
            }
        }
        
        SDL_RenderPresent(renderer);

        SDL_Delay(16); 
    }

    SDL_DestroyTexture(groundTex);
    SDL_DestroyTexture(wallTex);
    SDL_DestroyTexture(boxTex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}