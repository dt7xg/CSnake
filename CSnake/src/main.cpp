#include "Game.h"

void printHelp() {
   printf("Usage: ./<executable> [OPTIONS]\n");
   printf("Options:\n");
   printf("  -w, --width, w <width>   Set the width of the program window (doubled) (default: 28)\n");
   printf("  -h, --height, h <height>  Set the height of the program window (default: 18)\n");
   printf("  fps, --fps, -f <fps>   Set the frames per second (default: 16)\n");
   printf("  -h, --help   Show this help message\n");
}

int main(int argc, char** argv){
   uint32_t width(28), height(18), fps(16);

   for(size_t i(1); i < argc && argc > 1; i++){
      std::string arg(argv[i]);
      if((arg == "w" || arg == "--width" || arg == "-w") && argc > i + 1){
         width = std::stoi(argv[i+1]);
      }
      else if((arg == "h" || arg == "--height" || arg == "-h") && argc > i + 1){
         height = std::stoi(argv[i+1]);
      }
      else if((arg == "fps" || arg == "--fps" || arg == "-f") && argc > i + 1){
         fps = std::stoi(argv[i+1]);
      }
      else{
         printHelp();
         return 0;
      }
      i++;
   }

   Game* game = new Game(width, height, fps);
   game->run();

   delete game;

   return 0;
}
