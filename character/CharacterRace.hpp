#ifndef CHARACTERRACE_HPP
#define CHARACTERRACE_HPP

enum class CharacterRace { HUMAN, ELF, DWARF };

inline std::ostream& operator<<(std::ostream& os, CharacterRace r) {
  switch (r) {
    case CharacterRace::HUMAN:
      os << "HUMAN";
      break;
    case CharacterRace::ELF:
      os << "ELF";
      break;
    case CharacterRace::DWARF:
      os << "DWARF";
      break;
  }

  return os;
}

#endif  // CHARACTERRACE_HPP
