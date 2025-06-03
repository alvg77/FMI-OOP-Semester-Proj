#include "Util.hpp"

#include <iostream>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

void Util::clearTerminal() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

void Util::waitForAnyKey() {
#ifdef _WIN32
  _getch();
#else
  enableTerminalRawMode();
  getchar();
  disableTerminalRawMode();
#endif
}

void Util::enableTerminalRawMode() {
#ifndef _WIN32
  termios term;
  tcgetattr(STDIN_FILENO, &term);
  term.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &term);
#endif
}

void Util::disableTerminalRawMode() {
#ifndef _WIN32
  termios term;
  tcgetattr(STDIN_FILENO, &term);
  term.c_lflag |= (ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &term);
#endif
}
