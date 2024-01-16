#pragma once

#include <vector>
#include <deque>

struct SnakeChunk{
   Position position = Position(1, 1);
	Direction direction = Direction::RIGHT;
};

class Snake{
   public:
      Snake(){
         m_Snake.reserve(8);
         m_Snake.push_back(SnakeChunk());
      };

      SnakeChunk& Head() { return m_Snake[0]; };
      const size_t Length() const { return m_Snake.size(); }
      
      void Apply(std::deque<Move> &moves) {
         for(auto& move: moves){
            m_Snake[move.offset].direction = move.direction;
            move.offset++;
         }

         if(moves.front().offset >= m_Snake.size()) moves.pop_front();
      };
      
      void Move(){
         for(auto &chunk: m_Snake){
            switch(chunk.direction){
               case Direction::RIGHT: chunk.position.x++; break;
               case Direction::UP: chunk.position.y--; break;
               case Direction::DOWN: chunk.position.y++; break;
               case Direction::LEFT: chunk.position.x--; break;
               default: break;
            }    
         }
      };

      void Extend(){
         auto chunk = m_Snake.back();
         switch(chunk.direction){
            case Direction::UP: chunk.position.y++; break;
            case Direction::DOWN: chunk.position.y--; break;
            case Direction::RIGHT: chunk.position.x--; break;
            case Direction::LEFT: chunk.position.x++; break;
            default: break;
         }

         m_Snake.push_back(chunk);
      }

      const std::vector<SnakeChunk>& GetSnake() const { return m_Snake; };

   private:
      std::vector<SnakeChunk> m_Snake;
};
