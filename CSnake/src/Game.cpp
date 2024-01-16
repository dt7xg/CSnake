#include "Game.h"

Game::Game(uint32_t w, uint32_t h, uint32_t fps): mWIDTH(w), mHEIGHT(h), mFPS(fps), mDefaultBoard(mHEIGHT+1), mGameOver(false) {
	printf(UCLEAR);

    // Generate the default board (2D array)
    for (size_t i(0); i <= mHEIGHT; i++) {
        if (i % mHEIGHT == 0)
            mDefaultBoard[i] = std::string(mWIDTH, '#');
        else
            mDefaultBoard[i] = "#" + std::string(mWIDTH - 2, ' ') + "#";
    }
}
Game::~Game() {
    printf("\n\nGAME OVER!!\n");
}

void Game::run() {
    auto board(mDefaultBoard);
    Position apple;

    std::thread listener([=] { Game::ListenToActions(); });

    while (!mGameOver) {
        mSnake.ApplyActions(mActions);
        mSnake.Advance();

        const auto& head(mSnake.head());
        switch (board[head.position.y][head.position.x]) {
            case '#': mGameOver = true; break;
            case '*': mGameOver = true; break;
            case '+':
                mSnake.Grow();
                apple.x = 0;
                break;
            default: break;
        }

        // Generate Apple
        if (apple.x == 0) {
            Position pos;
            do {
                pos = Position(random(2, mWIDTH - 2), random(2, mHEIGHT - 2));
            } while (board[pos.y][pos.x] != ' ');

            apple = pos;
        }

        GenerateBoard(apple, board);

        // Draw
        printf(UHOME);
        for (const auto& line : board) printf("%s\n", line.c_str());


        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / mFPS));
        printf("\n\nScore: %u", (uint32_t)mSnake.length());
    }

    listener.detach();
}

void Game::GenerateBoard(const Position& apple, std::vector<std::string>& board) {
    board = mDefaultBoard;

    board[apple.y][apple.x] = '+';
    for (const auto& chunk : mSnake.chunks()) board[chunk.position.y][chunk.position.x] = '*';
}

void Game::ListenToActions() {
    bool isArrow(false);
    char key;

        while (!mGameOver) {
            key = _getch();
#ifndef _WIN32
            isArrow = isArrow && key == 91;
#endif
            if (isArrow) {
                Direction last = mSnake.head().direction;
#ifndef _WIN32
                key = _getch();
#endif
                switch (key) {
                case kARROW_UP:
                    if (mSnake.length() == 1 || (last != Direction::UP && last != Direction::DOWN))
                        mActions.push_back(Action(Direction::UP));
                    break;
                case kARROW_DOWN:
                    if (mSnake.length() == 1 || (last != Direction::UP && last != Direction::DOWN))
                        mActions.push_back(Action(Direction::DOWN));
                    break;
                case kARROW_LEFT:
                    if (mSnake.length() == 1 || (last != Direction::LEFT && last != Direction::RIGHT))
                        mActions.push_back(Action(Direction::LEFT));
                    break;
                case kARROW_RIGHT:
                    if (mSnake.length() == 1 || (last != Direction::LEFT && last != Direction::RIGHT))
                        mActions.push_back(Action(Direction::RIGHT));
                    break;
                default: break;
                }
                isArrow = false;
            }
            else if (key == kARROW) isArrow = true;
        }
    }
