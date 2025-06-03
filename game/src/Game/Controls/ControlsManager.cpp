#include "ControlsManager.hpp"

#include "../../Util/Util.hpp"
#include "../GameAction.hpp"

GameAction ControlsManager::getInputs() {
  while (true) {
#ifndef _WIN32
    Util::enableTerminalRawMode();

    char ch1 = getchar();
    if (ch1 == '\x1b') {
      char ch2 = getchar();
      if (ch2 == '[') {
        char ch3 = getchar();
        Util::disableTerminalRawMode();
        switch (ch3) {
          case 'A':
            return GameAction::MOVE_UP;
          case 'B':
            return GameAction::MOVE_DOWN;
          case 'C':
            return GameAction::MOVE_RIGHT;
          case 'D':
            return GameAction::MOVE_LEFT;
        }
      }
    } else if (ch1 == 's') {
      return GameAction::SAVE;
    } else if (ch1 == 'x') {
      return GameAction::EXIT;
    }

    Util::disableTerminalRawMode();

#else
    int ch = _getch();
    if (ch == 0 || ch == 224) {
      int ch2 = _getch();
      switch (ch2) {
        case 72:
          return MoveDirection::UP;
        case 80:
          return MoveDirection::DOWN;
        case 75:
          return MoveDirection::LEFT;
        case 77:
          return MoveDirection::RIGHT;
      }
    }
#endif
  }
}
