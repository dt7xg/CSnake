#pragma once

#include <cstdio>
#include <random>
#ifdef _WIN32
#include<conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

using std::size_t;

// ANSI Colors
constexpr const char* UCLEAR = "\033[2J";
constexpr const char* UHOME = "\033[H";
constexpr const char* UGREEN = "\e[42m";  // Snake Color
constexpr const char* UWHITE = "\e[47m";
constexpr const char* URED = "\e[41m";    // Apple Color
constexpr const char* UBLACK = "\e[40m";  // Border Color
constexpr const char* URESET = "\e[0m";

// Keyboard Codes
#ifndef _WIN32
constexpr int8_t kARROW = 27;
constexpr int8_t kARROW_UP = 65;
constexpr int8_t kARROW_DOWN = 66;
constexpr int8_t kARROW_RIGHT = 67;
constexpr int8_t kARROW_LEFT = 68;
#else
constexpr int8_t kARROW = -32;
constexpr int8_t kARROW_UP = 72;
constexpr int8_t kARROW_DOWN = 80;
constexpr int8_t kARROW_RIGHT = 77;
constexpr int8_t kARROW_LEFT = 75;
#endif

// Utils
struct Position{
   size_t x, y;

   Position(size_t x = 0,  size_t y = 0): x(x), y(y) {};
};

enum class Direction{UP, DOWN, LEFT, RIGHT};

struct Action{
   Direction direction;
   int offset;

   Action(Direction dir, int offset = 0): offset(offset), direction(dir) {}
};

inline int random(int min, int max){
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(min,max);

    return dist(rng);
}

#ifndef _WIN32
inline char _getch(){
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror ("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror ("tcsetattr ~ICANON");
    return (buf);
};
#endif
