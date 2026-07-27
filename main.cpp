#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>

using namespace std;

const int MAPS_ROWS = 25;
const int MAPS_COLS = 30;
const int TILE_SIZE = 40;

const int SCREEN_WIDTH = MAPS_COLS * TILE_SIZE;
const int SCREEN_HEIGHT = MAPS_ROWS * TILE_SIZE;

// Trang thai cua game
enum GameState {
    STATE_MENU,
    STATE_PLAYING
};

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

// Kiem tra nhan vat o vi tri (x, y) co dam vao tuong (1) hoac hop (2) khong.
// x, y la goc tren-trai cua nhan vat, kich thuoc TILE_SIZE x TILE_SIZE.
bool biChan(float x, float y) {
    int cotTrai = (int)(x) / TILE_SIZE;
    int cotPhai = (int)(x + TILE_SIZE - 1) / TILE_SIZE;
    int hangTren = (int)(y) / TILE_SIZE;
    int hangDuoi = (int)(y + TILE_SIZE - 1) / TILE_SIZE;

    // Ra ngoai bien -> coi nhu bi chan
    if (cotTrai < 0 || hangTren < 0 || cotPhai >= MAPS_COLS || hangDuoi >= MAPS_ROWS)
        return true;

    for (int r = hangTren; r <= hangDuoi; ++r) {
        for (int c = cotTrai; c <= cotPhai; ++c) {
            if (tileMap[r][c] == 1 || tileMap[r][c] == 2)
                return true;
        }
    }
    return false;
}

int main(int argc, char* argv[]) {

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        cout << "Loi khoi tao SDL3: " << SDL_GetError() << endl;
        return -1;
    }

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (!SDL_CreateWindowAndRenderer("Game Dat Boom - SDL3", SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer)) {
        cout << "Loi tao cua so/trinh ve: " << SDL_GetError() << endl;
        SDL_Quit();
        return -1;
    }

    // Anh ban do
    SDL_Texture* groundTex = IMG_LoadTexture(renderer, "ground.png");
    SDL_Texture* wallTex = IMG_LoadTexture(renderer, "wall.png");
    SDL_Texture* boxTex = IMG_LoadTexture(renderer, "box.png");

    if (!groundTex || !wallTex || !boxTex) {
        cout << "Loi: Khong tim thay cac file anh ban do!" << endl;
    }

    // Anh nen menu
    SDL_Texture* menuTex = IMG_LoadTexture(renderer, "menu.png");
    if (!menuTex) {
        cout << "Chua co menu.png - menu se dung nen mau don gian." << endl;
    }

    // Anh nhan vat theo 4 huong
    SDL_Texture* nguoiChoiTrai  = IMG_LoadTexture(renderer, "player_trai.png");
    SDL_Texture* nguoiChoiPhai  = IMG_LoadTexture(renderer, "player_phai.png");
    SDL_Texture* nguoiChoiLen   = IMG_LoadTexture(renderer, "player_len.png");
    SDL_Texture* nguoiChoiXuong = IMG_LoadTexture(renderer, "player_xuong.png");
    if (!nguoiChoiTrai || !nguoiChoiPhai || !nguoiChoiLen || !nguoiChoiXuong) {
        cout << "Khong tim thay file player_*.png!" << endl;
    }

    // Vi tri va toc do nhan vat (tinh theo pixel). Bat dau o o (hang 1, cot 1).
    float nguoiChoiX = 1 * TILE_SIZE;
    float nguoiChoiY = 1 * TILE_SIZE;
    const float tocDo = 3.0f;   // pixel moi khung hinh

    // Huong nhan vat dang quay mat: 0=xuong, 1=len, 2=trai, 3=phai
    int huong = 0;

    bool isRunning = true;
    GameState state = STATE_MENU;
    SDL_Event event;

    while (isRunning) {

        // ===== XU LY SU KIEN =====
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                isRunning = false;
            }
            else if (event.type == SDL_EVENT_KEY_DOWN) {

                if (state == STATE_MENU) {
                    if (event.key.key == SDLK_RETURN || event.key.key == SDLK_SPACE) {
                        state = STATE_PLAYING;
                    }
                    else if (event.key.key == SDLK_ESCAPE) {
                        isRunning = false;
                    }
                }
                else if (state == STATE_PLAYING) {
                    if (event.key.key == SDLK_ESCAPE) {
                        state = STATE_MENU;
                    }
                }
            }
        }

        // ===== CAP NHAT (di chuyen nhan vat) =====
        if (state == STATE_PLAYING) {
            const bool* phim = SDL_GetKeyboardState(nullptr);

            // Di chuyen theo truc X, kiem tra va cham rieng de van truot duoc
            float NewX = nguoiChoiX;
            if (phim[SDL_SCANCODE_LEFT])  { NewX -= tocDo; huong = 2; }
            if (phim[SDL_SCANCODE_RIGHT]) { NewX += tocDo; huong = 3; }
            if (!biChan(NewX, nguoiChoiY))
                nguoiChoiX = NewX;

            // Di chuyen theo truc Y
            float NewY = nguoiChoiY;
            if (phim[SDL_SCANCODE_UP])   { NewY -= tocDo; huong = 1; }
            if (phim[SDL_SCANCODE_DOWN]) { NewY += tocDo; huong = 0; }
            if (!biChan(nguoiChoiX, NewY))
                nguoiChoiY = NewY;
        }

        // ===== VE MAN HINH =====
        if (state == STATE_MENU) {
            if (menuTex) {
                SDL_RenderTexture(renderer, menuTex, nullptr, nullptr);
            }
            
        }
        else if (state == STATE_PLAYING) {
            // Ve ban do
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

            // Ve nhan vat len tren ban do.
            // Sprite goc 20x30 (ti le 2:3) -> ve rong 24, cao 36, canh giua trong o 40x40.
            const float Verong = 24.0f;
            const float Vecao = 36.0f;
            SDL_FRect oNhanVat = {
                nguoiChoiX + (TILE_SIZE - Verong) / 2.0f,   // canh giua ngang
                nguoiChoiY + (TILE_SIZE - Vecao),           // sat day o
                Verong,
                Vecao
            };

            // Chon hinh theo huong dang quay mat
            SDL_Texture* hinhNhanVat = nguoiChoiXuong;
            if (huong == 1) hinhNhanVat = nguoiChoiLen;
            else if (huong == 2) hinhNhanVat = nguoiChoiTrai;
            else if (huong == 3) hinhNhanVat = nguoiChoiPhai;

            SDL_RenderTexture(renderer, hinhNhanVat, nullptr, &oNhanVat);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    // ===== DON DEP =====
    SDL_DestroyTexture(groundTex);
    SDL_DestroyTexture(wallTex);
    SDL_DestroyTexture(boxTex);
    SDL_DestroyTexture(menuTex);
    SDL_DestroyTexture(nguoiChoiTrai);
    SDL_DestroyTexture(nguoiChoiPhai);
    SDL_DestroyTexture(nguoiChoiLen);
    SDL_DestroyTexture(nguoiChoiXuong);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
