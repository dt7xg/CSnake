#pragma once

#include "Utilities.h"
#include "Snake.h"
#include <string>
#include <chrono>
#include <thread>

class Game{
   public:
      Game(uint32_t width = 24, uint32_t height = 20, uint32_t fps = 10): m_Width(width), m_Height(height), m_FPS(fps){
         printf(UCLEAR);
         GenerateBoard();
      };

      void run(){
         std::vector<std::string> activeBoard(m_Board);
         Position apple;

         std::thread movement([=] { Game::ListenToMovement(m_Moves); });
            while(!m_GameOver){
               if(!m_Moves.empty()) m_Snake.Apply(m_Moves);
               m_Snake.Move();

               const auto& head(m_Snake.Head());
               switch(activeBoard[head.position.y][head.position.x]){
                  case '#': m_GameOver = true; break;
                  case '*': m_GameOver = true; break;
                  case '+':
                            m_Snake.Extend();
                            apple.y = 0;
                  default: break;
               }

               printf(UHOME);
               if(apple.y == 0) apple = GenerateApple(activeBoard);
               DrawBoard(apple, activeBoard);

               std::this_thread::sleep_for(std::chrono::milliseconds(1000/m_FPS));
               printf("\n\nScore: %u", m_Snake.Length());
            }
            printf("\nGAME OVER!!\n");
            movement.detach();
      }

   private:
      const uint32_t m_Width, m_Height, m_FPS;
      std::vector<std::string> m_Board;
      Snake m_Snake{};
      bool m_GameOver{false};
      std::deque<Move> m_Moves;

   private:
      void GenerateBoard(){
         m_Board.reserve(m_Height);

         for(size_t i(0); i <= m_Height; i++){
            if(i%m_Height == 0) 
               m_Board.push_back(std::string(m_Width, '#'));
            else
               m_Board.push_back("#" + std::string(m_Width-2, ' ') + "#");
         }
      }

      void DrawBoard(Position apple, std::vector<std::string> &board){
         board = m_Board;

         board[apple.y][apple.x] = '+';
         for(const auto &chunk: m_Snake.GetSnake())
            board[chunk.position.y][chunk.position.x] = '*';

         for(const auto &line: board) printf("%s\n", line.c_str());
      };

      Position GenerateApple(std::vector<std::string> &board){
         Position pos;
         do{
            pos = Position(random(1, m_Width-1), random(1, m_Height-1));
         }while(board[pos.y][pos.x] != ' ');

         return pos;
      }


      void ListenToMovement(std::deque<Move> &moves){
         bool isArrow(false);
         char key;

         while(true){
            key = _getch();
            if(isArrow && key == 91){
               Direction last = m_Snake.Head().direction;

               key = _getch();
               switch (key) {
                  case kARROW_UP:
                     if(m_Snake.Length() == 1 || (last != Direction::UP && last != Direction::DOWN))
                        moves.push_back(Move(Direction::UP));
                     break;
                  case kARROW_DOWN:
                     if(m_Snake.Length() == 1 || (last != Direction::UP && last != Direction::DOWN))
                        moves.push_back(Move(Direction::DOWN));
                     break;
                  case kARROW_LEFT:
                     if(m_Snake.Length() == 1 || (last != Direction::LEFT && last != Direction::RIGHT))
                        moves.push_back(Move(Direction::LEFT));
                     break;
                  case kARROW_RIGHT:
                     if(m_Snake.Length() == 1 || (last != Direction::LEFT && last != Direction::RIGHT))
                        moves.push_back(Move(Direction::RIGHT));
                     break;
                  default: 
                     break;
               }
               isArrow = false;
            }
            else if(key == kARROW) isArrow = true;
         }
      }
};
