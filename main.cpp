#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h> // Thư viện để đọc ảnh PNG
#include <iostream>

// Cấu hình kích thước game
const int MAP_ROWS = 15;   // Bản đồ gồm 15 hàng
const int MAP_COLS = 20;   // Bản đồ gồm 20 cột
const int TILE_SIZE = 40;  // Mỗi ô vuông có kích thước 40x40 pixel

const int SCREEN_WIDTH = MAP_COLS * TILE_SIZE;  // 800 pixel
const int SCREEN_HEIGHT = MAP_ROWS * TILE_SIZE; // 600 pixel

// Định nghĩa Ma trận Bản đồ (0: Đất trống, 1: Tường đá, 2: Thùng gỗ)
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
    // 1. Khởi tạo SDL3
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cout << "Lỗi khởi tạo SDL3: " << SDL_GetError() << std::endl;
        return -1;
    }

    // 2. Tạo cửa sổ và Trình vẽ
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    if (!SDL_CreateWindowAndRenderer("Game Dat Boom - Tuan 2: Bản Đồ", SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer)) {
        std::cout << "Lỗi tạo cửa sổ: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    // 3. Tải hình ảnh gạch đá từ thư mục vào Game (Sử dụng SDL3_image)
    SDL_Texture* groundTex = IMG_LoadTexture(renderer, "ground.png");
    SDL_Texture* wallTex = IMG_LoadTexture(renderer, "wall.png");
    SDL_Texture* boxTex = IMG_LoadTexture(renderer, "box.png");

    // Kiểm tra xem có bị tải lỗi ảnh không
    if (!groundTex || !wallTex || !boxTex) {
        std::cout << "Lỗi: Không tìm thấy các file ảnh bản đồ! Hãy kiểm tra lại vị trí ảnh." << std::endl;
    }

    // 4. Vòng lặp Game Loop
    bool isRunning = true;
    SDL_Event event;

    while (isRunning) {
        // Xử lý sự kiện tắt game
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                isRunning = false;
            }
        }

        // Xóa màn hình cũ để vẽ mới
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // --- THUẬT TOÁN VẼ BẢN ĐỒ ---
        // Duyệt qua từng ô của mảng 2 chiều bằng 2 vòng lặp lồng nhau
        for (int r = 0; r < MAP_ROWS; ++r) {
            for (int c = 0; c < MAP_COLS; ++c) {

                // Xác định vị trí (tọa độ pixel X, Y) của ô gạch trên màn hình
                SDL_FRect destRect;
                destRect.x = c * TILE_SIZE; // Vị trí cột nhân với kích thước ô
                destRect.y = r * TILE_SIZE; // Vị trí hàng nhân với kích thước ô
                destRect.w = TILE_SIZE;
                destRect.h = TILE_SIZE;

                // Luôn vẽ nền đất ở dưới trước để làm nền
                SDL_RenderTexture(renderer, groundTex, nullptr, &destRect);

                // Nếu tại ô đó là số 1 -> Vẽ đè viên tường đá lên
                if (tileMap[r][c] == 1) {
                    SDL_RenderTexture(renderer, wallTex, nullptr, &destRect);
                }
                // Nếu tại ô đó là số 2 -> Vẽ đè cái thùng gỗ lên
                else if (tileMap[r][c] == 2) {
                    SDL_RenderTexture(renderer, boxTex, nullptr, &destRect);
                }
            }
        }

        // Cập nhật hiển thị lên màn hình
        SDL_RenderPresent(renderer);
        SDL_Delay(16); // ~60 FPS
    }

    // 5. Giải phóng tài nguyên ảnh và bộ nhớ trước khi thoát
    SDL_DestroyTexture(groundTex);
    SDL_DestroyTexture(wallTex);
    SDL_DestroyTexture(boxTex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}