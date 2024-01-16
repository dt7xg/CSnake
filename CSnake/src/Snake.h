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
         mChunks.reserve(8); // Fixes a Weird Glitch: Vector allocation error when push_back on length 4
         mChunks.push_back(SnakeChunk());
      };

      SnakeChunk& head() { return mChunks[0]; };
      const size_t length() const { return mChunks.size(); }
      const std::vector<SnakeChunk>& chunks() const { return mChunks; };

public:
      void ApplyActions(std::deque<Action> &actions) {
          if (actions.empty()) return;

         for(auto& action: actions){
            mChunks[action.offset].direction = action.direction;
            action.offset++;
         }

         if(actions.front().offset >= mChunks.size()) actions.pop_front();
      };
      
      void Advance(){
         for(auto &chunk: mChunks){
            switch(chunk.direction){
               case Direction::RIGHT: chunk.position.x++; break;
               case Direction::UP: chunk.position.y--; break;
               case Direction::DOWN: chunk.position.y++; break;
               case Direction::LEFT: chunk.position.x--; break;
               default: break;
            }    
         }
      };

      void Grow(){
         auto chunk = mChunks.back();
         switch(chunk.direction){
            case Direction::UP: chunk.position.y++; break;
            case Direction::DOWN: chunk.position.y--; break;
            case Direction::RIGHT: chunk.position.x--; break;
            case Direction::LEFT: chunk.position.x++; break;
            default: break;
         }

         mChunks.push_back(chunk);
      }


   private:
      std::vector<SnakeChunk> mChunks;
};
