# Dungeon Crawler Game

A C++ dungeon crawler game with a level editor for automatically generating maps. This is a project for my university
OOP course.

---

## 🛠️ Project Structure

- `src/` — Game source code
- `data/` — JSON files containing data about levels, monsters, items and saves
- `editor/` — Game level editor
- `CMakeLists.txt` — CMake build configuration
- `conanfile.py` — Conan dependencies

---

## 🚀 How to Start the Project

### 1. Prerequisites

Make sure the following are installed:

- [CMake](https://cmake.org/)
- [Conan](https://conan.io/) — install via:

  ```bash
  pip install conan
  ```

- A C++ compiler (e.g., GCC or Clang)
- Python (required for Conan)

---

### 2. Install Dependencies

Use Conan to install all required packages into the build folder:

```bash
conan install . --output-folder=cmake-build-debug --build=missing -s build_type=Debug
```

---

### 3. Configure the Project with CMake

Generate the build files using the Conan toolchain:

```bash
cmake -S . -B cmake-build-debug \
  -DCMAKE_TOOLCHAIN_FILE=conan_provider.cmake \
  -DCMAKE_BUILD_TYPE=Debug
```

---

### 4. Build the Project

Compile the source code:

```bash
cmake --build cmake-build-debug --target FMI_OOP_Semester_Proj -j 8
```

***The same steps can be followed for building the level editor, which is located in the `/level` folder.***

---

### 5. Ensure you have the required JSON files for the game

At the root of the project there should be a `data` folder. Inside it there will be 3 folders (a fourth one for the save
files will be created after saving the game for the first time). The 3 folders will be:

```bash
/levels
  level1.json
  level2.json
  ...
/items
  items1.json
  items2.json
  ...
/monsters
  monsters1.json
  monsters2.json
  ...
```

Each of those contains json files with data about a level in the game. Without those files you cannot start the game. As
of now there are 4 distinct levels that the player has to complete so each folder should contain 4 json files, each one
corresponding to a level. To create new maps for a level (1-4), you can use the level editor utility, which generates a
random map for the level, there you can also specify the number of monsters and treasures you can encounter on the
level.

---

### 6. Run the Game

After building, the executable should be inside `cmake-build-debug/`. You can run it with:

```bash
./cmake-build-debug/<executable_name>
```

> Replace `<executable_name>` with the actual name of the output binary specified in `CMakeLists.txt`.

---

### 7. (Optional) Generating Documentation with Doxygen

1. **Install Doxygen and Graphviz**

   Visit the official websites to download and install the latest versions for your platform:

- [Doxygen](https://www.doxygen.nl/download.html)
- [Graphviz](https://graphviz.org/download/)

2. **Generate a Default Configuration File**

   From the project root directory, run:

   ```bash
   doxygen -g
   ```

   This creates a `Doxyfile` with default settings.

3. **Configure the `Doxyfile`**

   Open `Doxyfile` in a text editor and set key options such as:

   ```ini
   OUTPUT_DIRECTORY = docs
   RECURSIVE = YES
   EXCLUDE = conanfile.py \
             conanfile.txt \
             conandata.yml \
             conan_provider.cmake
   ```

4. **Generate Documentation**

   Run:

   ```bash
   doxygen Doxyfile
   ```

   The generated documentation will be in the `docs/html` folder. Open `index.html` in your browser to view it.

---

## 🔮 Future Development

- Integrate a graphical interface using **SFML**
- Add music and sound effects
- Implement advanced gameplay mechanics:
    - Traps
    - Player and enemy skills
    - Consumable items (e.g., potions, buffs)
    - Limited vision system — restrict visibility to the player’s surroundings, hiding unexplored areas
- Introduce more playable **classes** and **races**

