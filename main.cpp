#define OLC_PGE_APPLICATION

#include <olcPixelGameEngine/olcPixelGameEngine.h>
#include <string>

class Tetris : public olc::PixelGameEngine {

    struct Tetromino {
        std::string name;
        std::wstring shape;
        olc::Pixel color;
    };

    Tetromino tetrominoes[7];

    int iFieldWidth = 10;
    int iFieldHeight = 20;
    int iSize = 16;
    int iDrawOffsetX = 0;
    int iDrawOffsetY = 0;

    unsigned char *pField = nullptr;

    int iCurrentPeice = 0;
    int iNextPeice = 0;
    int iCurrentRotation = 0;
    int iCurrentX = iFieldWidth / 2;        // Start the piece roughly in the middle of the playing field
    int iCurrentY = 0;

    int iSpeed = 15;
    int iSpeedCounter = 0;
    bool bForceDown = false;

    int iScore = 0;
    int iLinesCleared = 0;
    int iLevel = 1;

    std::vector<int> vLines;

public:
    bool bIsDebug;

    Tetris() {
        sAppName = "Tetris";
        bIsDebug = true;
    }

    bool OnUserCreate() override {

        tetrominoes[0].name = "Straight";
        tetrominoes[0].color = olc::DARK_CYAN;
        tetrominoes[0].shape = L"..X...X...X...X.";

        tetrominoes[1].name = "Square";
        tetrominoes[1].color = olc::DARK_YELLOW;
        tetrominoes[1].shape = L".....XX..XX.....";

        tetrominoes[2].name = "T";
        tetrominoes[2].color = olc::DARK_MAGENTA;
        tetrominoes[2].shape = L"..X..XX...X.....";

        tetrominoes[3].name = "L";
        tetrominoes[3].color = olc::Pixel(252, 129, 1);
        tetrominoes[3].shape = L".....X...X...XX.";

        tetrominoes[4].name = "Reverse L";
        tetrominoes[4].color = olc::Pixel(5, 18, 255);
        tetrominoes[4].shape = L"......X...X..XX.";

        tetrominoes[5].name = "Skew";
        tetrominoes[5].color = olc::Pixel(51, 253, 1);
        tetrominoes[5].shape = L"..X..XX..X......";

        tetrominoes[6].name = "Reverse Skew";
        tetrominoes[6].color = olc::Pixel(251, 25, 0);
        tetrominoes[6].shape = L".X...XX...X.....";


        // Initialize the playing field
        pField = new unsigned char[iFieldWidth * iFieldHeight];
        for (int x = 0; x < iFieldWidth; x++) {
            for (int y = 0; y < iFieldHeight; y++) {
                pField[y * iFieldWidth + x] = (x == 0 || x == iFieldWidth - 1 || y == iFieldHeight - 1) ? 11 : 0;
            }
        }

        iDrawOffsetX = 2;
        iDrawOffsetY = 2;


        iNextPeice = std::rand() % 7;

        SpawnRandomPeice();

        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override {
        Clear(olc::BLACK);

        //std::this_thread::sleep_for(std::chrono::milliseconds(50));
        iSpeedCounter++;
        bForceDown = (iSpeedCounter == iSpeed);

        iCurrentX -= (GetKey(olc::LEFT).bPressed &&
                      DoesPieceFit(iCurrentPeice, iCurrentRotation, iCurrentX - 1, iCurrentY)) ? 1 : 0;

        iCurrentX += (GetKey(olc::RIGHT).bPressed &&
                      DoesPieceFit(iCurrentPeice, iCurrentRotation, iCurrentX + 1, iCurrentY)) ? 1 : 0;

        iCurrentY += (GetKey(olc::DOWN).bHeld &&
                      DoesPieceFit(iCurrentPeice, iCurrentRotation, iCurrentX, iCurrentY + 1)) ? 1 : 0;

        iCurrentRotation += (GetKey(olc::Z).bPressed &&
                             DoesPieceFit(iCurrentPeice, iCurrentRotation + 1, iCurrentX, iCurrentY)) ? 1 : 0;


        if (bForceDown) {
            iSpeedCounter = 0;
            UpdatePositionsAndCheckForCollisios();
        }

        if (!DrawField(fElapsedTime)) return false;
        if (!DrawPieces(fElapsedTime)) return false;

        if (!vLines.empty()) {
            switch (vLines.size()) {
                case 1:
                    iScore += 10 * iLevel;
                    break;
                case 2:
                    iScore += 30 * iLevel;
                    break;
                case 3:
                    iScore += 60 * iLevel;
                    break;
                case 4:
                    iScore += 100 * iLevel;
                    break;
            }

            //TODO: Fix this
            std::this_thread::sleep_for(std::chrono::milliseconds(400));

            for (auto &v : vLines) {
                iLinesCleared++;
                for (int px = 1; px < iFieldWidth - 1; px++) {
                    for (int py = v; py > 0; py--) {
                        pField[py * iFieldWidth + px] = pField[(py - 1) * iFieldWidth + px];
                        pField[px] = 0;
                    }
                }
            }

            vLines.clear();
        }

        DrawUI();

        if (isGameOver) return false;

        return true;
    }

private:
    bool isGameOver = false;

    bool DrawField(float fElapsedTime) {
        for (int x = 0; x < iFieldWidth; x++) {
            for (int y = 0; y < iFieldHeight; y++) {

                if (pField[y * iFieldWidth + x] != 0 && pField[y * iFieldWidth + x] != 11 &&
                    pField[y * iFieldWidth + x] != 12) {
                    FillRect((x + iDrawOffsetX) * iSize, (y + iDrawOffsetY) * iSize, iSize, iSize,
                             tetrominoes[pField[y * iFieldWidth + x] -
                                         1].color);       // Dont forget, we add +1 when we "lock" a tetrominoe in place
                } else {
                    switch (pField[y * iFieldWidth + x]) {
                        case 0:
                            break;
                        case 11:
                            FillRect((x + iDrawOffsetX) * iSize, (y + iDrawOffsetY) * iSize, iSize, iSize,
                                     olc::DARK_RED);
                            break;
                        case 12:
                            FillRect((x + iDrawOffsetX) * iSize, (y + iDrawOffsetY) * iSize, iSize, iSize,
                                     olc::GREEN);
                            break;
                        default:
                            FillRect((x + iDrawOffsetX) * iSize, (y + iDrawOffsetY) * iSize, iSize, iSize,
                                     olc::Pixel(215, 83, 162));
                            break;
                    }
                }

                if (bIsDebug) {
                    DrawString((x + iDrawOffsetX) * iSize, (y + iDrawOffsetY) * iSize,
                               std::to_string(pField[y * iFieldWidth +
                                                     x]));// Dont forget, we added +1 when we "lock" a tetrominoe in place
                }

            }
        }
        return true;
    }

    bool DrawPieces(float fElapsedTime) {

        for (int px = 0; px < 4; px++) {
            for (int py = 0; py < 4; py++) {
                if (tetrominoes[iCurrentPeice].shape[Rotate(px, py, iCurrentRotation)] != L'.') {
                    // yeah, this is a piece
                    FillRect((iCurrentX + iDrawOffsetX + px) * iSize, (iCurrentY + iDrawOffsetY + py) * iSize, iSize,
                             iSize,
                             tetrominoes[iCurrentPeice].color);
                    if (bIsDebug)
                        DrawString((iCurrentX + iDrawOffsetX + px) * iSize, (iCurrentY + iDrawOffsetY + py) * iSize,
                                   std::to_string(iCurrentPeice));
                }
            }
        }


        return true;
    }

    void DrawPreview(int iposX, int iposY) {
        for (int px = 0; px < 4; px++) {
            for (int py = 0; py < 4; py++) {
                if (tetrominoes[iNextPeice].shape[Rotate(px, py, 0)] != L'.') {
                    FillRect((iposX + iDrawOffsetX + px) * iSize, (iposY + iDrawOffsetY + py) * iSize, iSize, iSize,
                             tetrominoes[iNextPeice].color);
                    if (bIsDebug)
                        DrawString((iposX + iDrawOffsetX + px) * iSize, (iposY + iDrawOffsetY + py) * iSize,
                                   std::to_string(iNextPeice));
                }
            }
        }
    }

    void DrawUI() {
        DrawString(iFieldWidth + 230 + iDrawOffsetX, iSize + iSize, "NEXT TETROMINO");
        DrawPreview(iFieldWidth + iDrawOffsetX, 2);

        DrawString(iFieldWidth + 230 + iDrawOffsetX, iSize + iSize * 3 + 88,
                   "Score: " + std::to_string(iScore));
        DrawString(iFieldWidth + 230 + iDrawOffsetX, iSize + iSize * 3 + 100,
                   "Cleared Lines: " + std::to_string(iLinesCleared));
        DrawString(iFieldWidth + 230 + iDrawOffsetX, iSize + iSize * 3 + 112,
                   "Speed: " + std::to_string(iSpeed));
        DrawString(iFieldWidth + 230 + iDrawOffsetX, iSize + iSize * 3 + 124,
                   "Level: " + std::to_string(iLevel));
    }

    void UpdatePositionsAndCheckForCollisios() {
        if (DoesPieceFit(iCurrentPeice, iCurrentRotation, iCurrentX, iCurrentY + 1)) {
            iCurrentY++;
        } else {
            // Lock the current piece in place
            for (int px = 0; px < 4; px++) {
                for (int py = 0; py < 4; py++) {
                    if (tetrominoes[iCurrentPeice].shape[Rotate(px, py, iCurrentRotation)] != L'.') {
                        pField[(iCurrentY + py) * iFieldWidth + (iCurrentX + px)] = iCurrentPeice + 1;
                    }
                }
            }

            // Check if we careted any horizontal lines
            for (int py = 0; py < 4; py++) {
                if (iCurrentY + py < iFieldHeight - 1) {
                    bool line = true;       // We assume there is going to be a line
                    // Some small optimization: only check last 4 lines where tetrmomine was fixed at

                    for (int px = 1; px < iFieldWidth - 1; px++) {
                        line &= (pField[(iCurrentY + py) * iFieldWidth + px]) != 0;
                    }

                    if (line) {
                        for (int px = 1; px < iFieldWidth - 1; px++) {
                            pField[(iCurrentY + py) * iFieldWidth + px] = 12;
                        }
                        vLines.push_back(iCurrentY + py);
                    }
                }
            }

            // Generate a new peice
            SpawnRandomPeice();

            // If new piece doent fit, Game Over
            isGameOver = !DoesPieceFit(iCurrentPeice, iCurrentRotation, iCurrentX, iCurrentY);
        }
    }

    void SpawnRandomPeice() {
        iCurrentPeice = iNextPeice;
        iNextPeice = std::rand() % 7;
        iCurrentRotation = rand() % 3;
        iCurrentX = iFieldWidth / 2;        // Start the piece roughly in the middle of the playing field
        iCurrentY = 0;
    }

    int Rotate(int posX, int posY, int r) {
        switch (r % 4) {
            case 0:         // 0 degress
                return posY * 4 + posX;
            case 1:         // 90 degrees
                return 12 + posY - (posX * 4);
            case 2:         // 180 degrees
                return 15 - (posY * 4) - posX;
            case 3:         // 270 degrees
                return 3 - posY + (posX * 4);
        }
        return 0;
    }

    bool DoesPieceFit(int iTetrmonino, int iRotation, int iposX, int iposY) {

        for (int px = 0; px < 4; px++) {
            for (int py = 0; py < 4; py++) {
                int pi = Rotate(px, py, iRotation);

                int fieldIndex = (iposY + py) * iFieldWidth + (iposX + px);

                // make sure we are inside the field
                if (iposX + px >= 0 && iposX + px < iFieldWidth) {
                    if (iposY + py >= 0 && iposY + py < iFieldHeight) {
                        // we are inside the playing field

                        // We are hitting something
                        if (tetrominoes[iTetrmonino].shape[pi] != L'.' && pField[fieldIndex] != 0) {
                            return false;
                        }
                    }
                }
            }
        }

        return true;
    }
};

int main() {
    std::srand((int) time(0));
    Tetris tGame;
    tGame.bIsDebug = false;

    if (tGame.Construct(800, 600, 1, 1))
        tGame.Start();


    return 0;
}