#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>


const int MAP_ROWS = 15;
const int MAP_COLS = 20;
const int TILE_SIZE = 40;

const int SCREEN_WIDTH = MAP_COLS * TILE_SIZE;  
const int SCREEN_HEIGHT = MAP_ROWS * TILE_SIZE; 


int tileMap[MAP_ROWS][MAP_COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1},
    {1, 2, 0, 2, 2, 0, 0, 2, 0, 0, 2, 2, 0, 0, 2, 2, 0, 0, 2, 1},
    {1, 0, 1, 0, 1, 2, 1, 0, 1, 2, 1, 0, 1, 2, 1, 0, 1, 2, 1, 1},
    {1, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 2, 1, 0, 1, 0, 1, 0, 1, 2, 1, 0, 1, 1},
    {1, 2, 0, 0, 2, 2, 0, 0, 2, 2, 0, 0, 2, 2, 0, 0, 2, 0, 2, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1},
    {1, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 2, 1, 0, 1, 2, 1, 0, 1, 2, 1, 0, 1, 2, 1, 1},
    {1, 2, 0, 2, 2, 0, 0, 2, 0, 0, 2, 2, 0, 0, 2, 2, 0, 0, 2, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1},
    {1, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

int main(int argc, char* argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        return -1;
    }

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    if (!SDL_CreateWindowAndRenderer("Game Dat Boom - Tuan 3: Nhan Vat", SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer)) {
        SDL_Quit();
        return -1;
    }

    // Tải hình ảnh Bản đồ
    SDL_Texture* groundTex = IMG_LoadTexture(renderer, "ground.png");
    SDL_Texture* wallTex = IMG_LoadTexture(renderer, "wall.png");
    SDL_Texture* boxTex = IMG_LoadTexture(renderer, "box.png");

    //  Tải hình ảnh Nhân vật ---
    SDL_Texture* playerTex = IMG_LoadTexture(renderer, "player.png");

    if (!groundTex || !wallTex || !boxTex || !playerTex) {
        std::cout << "Loi: Khong tai duoc anh! Hãy kiem tra lại file trong thu muc Boom1." << std::endl;
    }

    //  Khỏi tạo vị trí và vận tốc nhân vật ---
    float playerX = 40.0f; // Xuất phát ở ô (Hàng 1, Cột 1) để tránh tường đá
    float playerY = 40.0f;
    float playerSpeed = 4.0f; // Tốc độ di chuyển (pixel mỗi khung hình)

    bool isRunning = true;
    SDL_Event event;

    // Mảng lưu trạng thái các phím đang được giữ (Tránh bị khựng khi di chuyển)
    const bool* keyStates = SDL_GetKeyboardState(nullptr);

    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                isRunning = false;
            }
        }

        //  Xử lý bấm phím di chuyển mượt mà ---
        if (keyStates[SDL_SCANCODE_W] || keyStates[SDL_SCANCODE_UP]) {
            playerY -= playerSpeed; // Đi lên
        }
        if (keyStates[SDL_SCANCODE_S] || keyStates[SDL_SCANCODE_DOWN]) {
            playerY += playerSpeed; // Đi xuống
        }
        if (keyStates[SDL_SCANCODE_A] || keyStates[SDL_SCANCODE_LEFT]) {
            playerX -= playerSpeed; // Sang trái
        }
        if (keyStates[SDL_SCANCODE_D] || keyStates[SDL_SCANCODE_RIGHT]) {
            playerX += playerSpeed; // Sang phải
        }

        // Xóa màn hình
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Vẽ Bản đồ 
        for (int r = 0; r < MAP_ROWS; ++r) {
            for (int c = 0; c < MAP_COLS; ++c) {
                SDL_FRect destRect = { (float)c * TILE_SIZE, (float)r * TILE_SIZE, (float)TILE_SIZE, (float)TILE_SIZE };
                SDL_RenderTexture(renderer, groundTex, nullptr, &destRect);

                if (tileMap[r][c] == 1) {
                    SDL_RenderTexture(renderer, wallTex, nullptr, &destRect);
                }
                else if (tileMap[r][c] == 2) {
                    SDL_RenderTexture(renderer, boxTex, nullptr, &destRect);
                }
            }
        }

        // ---  Vẽ Nhân vật lên màn hình ---
        SDL_FRect playerRect = { playerX, playerY, 32.0f, 32.0f }; // Vẽ nhân vật nhỏ hơn ô gạch một chút cho đẹp
        SDL_RenderTexture(renderer, playerTex, nullptr, &playerRect);

        SDL_RenderPresent(renderer);
        SDL_Delay(16); // Giới hạn khung hình ~60FPS
    }

    // Giải phóng bộ nhớ
    SDL_DestroyTexture(groundTex);
    SDL_DestroyTexture(wallTex);
    SDL_DestroyTexture(boxTex);
    SDL_DestroyTexture(playerTex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}