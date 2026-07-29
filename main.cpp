#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include <vector>

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

// Mot qua bom dat tren ban do
struct Bom {
    int hang, cot;          // o luoi dang dat bom
    Uint64 thoiGianDat;     // moc thoi gian dat (ms)
};

// Mot o lua khi bom no
struct Lua {
    int hang, cot;
    Uint64 thoiGianTao;     // moc thoi gian lua xuat hien (ms)
};

const Uint64 THOI_GIAN_NO = 2000;   // bom no sau 2 giay
const Uint64 THOI_GIAN_LUA = 500;   // lua ton tai 0.5 giay
const int TAM_NO = 2;               // ban kinh no: lan 2 o moi huong

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
    

    // Sprite sheet nhan vat: 1 anh chua ca 12 khung (4 huong x 3 khung di bo)
    SDL_Texture* nguoiChoiSheet = IMG_LoadTexture(renderer, "player_sheet.png");    

    // Anh bom va lua no
    SDL_Texture* bomTex = IMG_LoadTexture(renderer, "bomb.png");
    SDL_Texture* luaTex = IMG_LoadTexture(renderer, "explosion.png");
    if (!bomTex || !luaTex) {
        cout << "Khong tim thay bomb.png hoac explosion.png!" << endl;
    }

    // Danh sach bom va lua dang co tren ban do
    vector<Bom> danhSachBom;
    vector<Lua> danhSachLua;

    // Kich thuoc 1 khung tren sheet (goc, chua phong to)
    const int KHUNG_W = 20;
    const int KHUNG_H = 30;
    const int SO_KHUNG = 3;   // moi huong co 3 khung

    // Cot khung dau tien cua tung huong tren sheet (don vi = so khung).
    // huong: 0=xuong, 1=len, 2=trai, 3=phai
    // xuong bat dau o cot 3, len cot 6, trai cot 0, phai cot 9
    int cotBatDau[4] = { 3, 6, 0, 9 };

    // Vi tri va toc do nhan vat (tinh theo pixel). Bat dau o o (hang 1, cot 1).
    float nguoiChoiX = 1 * TILE_SIZE;
    float nguoiChoiY = 1 * TILE_SIZE;
    const float tocDo = 3.0f;   // pixel moi khung hinh

    // Huong nhan vat dang quay mat: 0=xuong, 1=len, 2=trai, 3=phai
    int huong = 0;

    // Trang thai hoat anh
    int khungHienTai = 1;              // khung dang ve (0..2); 1 = dang dung
    Uint64 thoiGianDoiKhung = 0;       // moc thoi gian lan doi khung gan nhat (ms)
    const Uint64 NHIP_DOI_KHUNG = 120; // cu 120ms doi 1 khung khi dang di

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
                    // SPACE -> dat bom tai o nhan vat dang dung
                    else if (event.key.key == SDLK_SPACE) {
                        int cotBom = (int)(nguoiChoiX + TILE_SIZE / 2) / TILE_SIZE;
                        int hangBom = (int)(nguoiChoiY + TILE_SIZE / 2) / TILE_SIZE;

                        // Khong dat 2 bom trung 1 o
                        bool daCoBom = false;
                        for (const Bom& b : danhSachBom)
                            if (b.hang == hangBom && b.cot == cotBom)
                                daCoBom = true;

                        if (!daCoBom)
                            danhSachBom.push_back({ hangBom, cotBom, SDL_GetTicks() });
                    }
                }
            }
        }

        // ===== CAP NHAT (di chuyen nhan vat) =====
        if (state == STATE_PLAYING) {
            const bool* phim = SDL_GetKeyboardState(nullptr);

            bool dangDi = false;   // co bam phim di chuyen trong khung nay khong?
            bool diNgang = false;  // dang di trai/phai?
            bool diDoc = false;    // dang di len/xuong?

            // Di chuyen theo truc X, kiem tra va cham rieng de van truot duoc
            float NewX = nguoiChoiX;
            if (phim[SDL_SCANCODE_LEFT]  || phim[SDL_SCANCODE_A]) 
            { NewX -= tocDo; huong = 2; dangDi = true; diNgang = true; }
            if (phim[SDL_SCANCODE_RIGHT] || phim[SDL_SCANCODE_D]) 
            { NewX += tocDo; huong = 3; dangDi = true; diNgang = true; }
            if (!biChan(NewX, nguoiChoiY))
                nguoiChoiX = NewX;
            float NewY = nguoiChoiY;
            if (phim[SDL_SCANCODE_UP]   || phim[SDL_SCANCODE_W]) 
            { NewY -= tocDo; huong = 1; dangDi = true; diDoc = true; }
            if (phim[SDL_SCANCODE_DOWN] || phim[SDL_SCANCODE_S]) 
            { NewY += tocDo; huong = 0; dangDi = true; diDoc = true; }
            if (!biChan(nguoiChoiX, NewY))
                nguoiChoiY = NewY;

            // ----- Auto-canh lane: chong ket khi lach qua khe giua hai tuong -----
            // Khi di ngang, keo Y ve hang gan nhat (moi hang = boi so cua TILE_SIZE)
            if (diNgang) {
                int hangGan = (int)((nguoiChoiY + TILE_SIZE / 2.0f) / TILE_SIZE);
                float dich = hangGan * (float)TILE_SIZE;
                float snapY = nguoiChoiY;
                if (snapY < dich) { snapY += tocDo; if (snapY > dich) snapY = dich; }
                else if (snapY > dich) { snapY -= tocDo; if (snapY < dich) snapY = dich; }
                if (!biChan(nguoiChoiX, snapY))
                    nguoiChoiY = snapY;
            }
            // Khi di doc, keo X ve cot gan nhat
            if (diDoc) {
                int cotGan = (int)((nguoiChoiX + TILE_SIZE / 2.0f) / TILE_SIZE);
                float dich = cotGan * (float)TILE_SIZE;
                float snapX = nguoiChoiX;
                if (snapX < dich) { snapX += tocDo; if (snapX > dich) snapX = dich; }
                else if (snapX > dich) { snapX -= tocDo; if (snapX < dich) snapX = dich; }
                if (!biChan(snapX, nguoiChoiY))
                    nguoiChoiX = snapX;
            }

            // Cap nhat hoat anh
            Uint64 bayGio = SDL_GetTicks();
            if (dangDi) {
                if (bayGio - thoiGianDoiKhung > NHIP_DOI_KHUNG) {
                    khungHienTai = (khungHienTai + 1) % SO_KHUNG;  // 0->1->2->0...
                    thoiGianDoiKhung = bayGio;
                }
            }
            else {
                khungHienTai = 1;   // dung yen -> khung giua (dang dung)
            }

            // ----- Bom: het gio thi no -----
            int dx[4] = { 1, -1, 0, 0 };   // phai, trai
            int dy[4] = { 0, 0, 1, -1 };   // xuong, len
            for (int i = 0; i < (int)danhSachBom.size(); ) {
                if (bayGio - danhSachBom[i].thoiGianDat >= THOI_GIAN_NO) {
                    int bh = danhSachBom[i].hang;
                    int bc = danhSachBom[i].cot;

                    // Lua o tam
                    danhSachLua.push_back({ bh, bc, bayGio });

                    // Lan ra 4 huong
                    for (int d = 0; d < 4; ++d) {
                        for (int b = 1; b <= TAM_NO; ++b) {
                            int nh = bh + dy[d] * b;
                            int nc = bc + dx[d] * b;
                            // ra ngoai bien -> dung
                            if (nh < 0 || nc < 0 || nh >= MAPS_ROWS || nc >= MAPS_COLS) break;
                            // tuong cung -> chan, khong co lua
                            if (tileMap[nh][nc] == 1) break;
                            // hop -> pha vo, dat lua roi dung (lua khong xuyen qua)
                            if (tileMap[nh][nc] == 2) {
                                tileMap[nh][nc] = 0;
                                danhSachLua.push_back({ nh, nc, bayGio });
                                break;
                            }
                            // o trong -> lua lan qua
                            danhSachLua.push_back({ nh, nc, bayGio });
                        }
                    }
                    danhSachBom.erase(danhSachBom.begin() + i);
                }
                else {
                    ++i;
                }
            }

            // ----- Lua: het gio thi bien mat -----
            for (int i = 0; i < (int)danhSachLua.size(); ) {
                if (bayGio - danhSachLua[i].thoiGianTao >= THOI_GIAN_LUA)
                    danhSachLua.erase(danhSachLua.begin() + i);
                else
                    ++i;
            }
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

            // Ve bom (nam duoi nhan vat)
            for (const Bom& b : danhSachBom) {
                SDL_FRect r = { (float)(b.cot * TILE_SIZE), (float)(b.hang * TILE_SIZE),
                                (float)TILE_SIZE, (float)TILE_SIZE };
                SDL_RenderTexture(renderer, bomTex, nullptr, &r);
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

            // Cat dung khung tren sprite sheet:
            // cot = cot dau cua huong + khung dang chay
            SDL_FRect nguon;
            nguon.x = (float)((cotBatDau[huong] + khungHienTai) * KHUNG_W);
            nguon.y = 0.0f;
            nguon.w = (float)KHUNG_W;
            nguon.h = (float)KHUNG_H;

            SDL_RenderTexture(renderer, nguoiChoiSheet, &nguon, &oNhanVat);

            // Ve lua (nam tren cung)
            for (const Lua& l : danhSachLua) {
                SDL_FRect r = { (float)(l.cot * TILE_SIZE), (float)(l.hang * TILE_SIZE),
                                (float)TILE_SIZE, (float)TILE_SIZE };
                SDL_RenderTexture(renderer, luaTex, nullptr, &r);
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    // ===== DON DEP =====
    SDL_DestroyTexture(groundTex);
    SDL_DestroyTexture(wallTex);
    SDL_DestroyTexture(boxTex);
    SDL_DestroyTexture(menuTex);
    SDL_DestroyTexture(nguoiChoiSheet);
    SDL_DestroyTexture(bomTex);
    SDL_DestroyTexture(luaTex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
