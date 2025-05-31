/**
 * @file Util.hpp
 * @ingroup Game
 * @brief Utility functions for terminal control and input handling.
 */

#ifndef UTIL_HPP
#define UTIL_HPP

namespace Util {

/**
 * @brief Clears the terminal screen.
 * Works for both Windows and Unix-like systems.
 */
void clearTerminal();

/**
 * @brief Waits for the user to press any key.
 * On Unix-like systems, enables raw mode to capture a single key press without
 * requiring Enter.
 */
void waitForAnyKey();

/**
 * @brief Enables terminal raw mode on Unix-like systems.
 * Disables canonical mode and echo.
 * Has no effect on Windows.
 */
void enableTerminalRawMode();

/**
 * @brief Disables terminal raw mode on Unix-like systems.
 * Restores canonical mode and echo.
 * Has no effect on Windows.
 */
void disableTerminalRawMode();

}  // namespace Util

#endif  // UTIL_HPP
