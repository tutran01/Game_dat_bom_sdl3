#include <SDL3/SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(int argc, char* argv[]) {
    // 1. Khởi tạo SDL3
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cout << "Lỗi khởi tạo SDL3: " << SDL_GetError() << std::endl;
        return -1;
    }

    // 2. Tạo cửa sổ và trình vẽ tích hợp sẵn (SDL3 gộp chung rất tiện)
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (!SDL_CreateWindowAndRenderer("Game Dat Boom - SDL3", SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer)) {
        std::cout << "Lỗi tạo cửa sổ/trình vẽ: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    // 3. Vòng lặp game (Game Loop)
    bool isRunning = true;
    SDL_Event event;

    while (isRunning) {
        // Xử lý sự kiện (Bấm nút X để thoát)
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                isRunning = false;
            }
        }

        // Xóa màn hình cũ (Tạo nền màu xanh dương đậm cho mát mắt)
        SDL_SetRenderDrawColor(renderer, 20, 40, 80, 255);
        SDL_RenderClear(renderer);

        // Hiển thị những gì đã vẽ lên màn hình
        SDL_RenderPresent(renderer);

        SDL_Delay(16); // Giới hạn ~60 FPS
    }

    // 4. Dọn dẹp bộ nhớ khi thoát game
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}