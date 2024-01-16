#pragma once

#include "Utilities.h"
#include "Snake.h"
#include <string>
#include <chrono>
#include <thread>

class Game{
   public:
       Game(uint32_t width = 28, uint32_t height = 20, uint32_t fps = 10);
       ~Game();

       void run();

   private:
      const uint32_t mWIDTH, mHEIGHT, mFPS;
      std::vector<std::string> mDefaultBoard;
      bool mGameOver;
      Snake mSnake;
      std::deque<Action> mActions;

   private:
       void GenerateBoard(const Position& apple, std::vector<std::string>& board);
       void ListenToActions();
};
