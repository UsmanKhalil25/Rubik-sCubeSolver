# Rubik's Cube Solver and Visualizer

This C++ project implements a Rubik's Cube solver and visualizer using SFML (Simple and Fast Multimedia Library). The solver utilizes Thistlethwaite's algorithm to find the optimal solution for any scrambled Rubik's Cube configuration. Additionally, the project provides a graphical interface to visualize each step of the solution.

## Prerequisites

Make sure you have the following dependencies installed before running the project:

- SFML library: [SFML Installation](https://www.sfml-dev.org/tutorials/2.5/start-linux.php)
- C++ compiler (supporting C++17 or later)

## How to Build

1. Clone the repository:

   ```bash
   git clone https://github.com/UsmanKhalil25/rubik-s-cubesolver.git
   ```

2. Navigate to the project directory:

   ```bash
   cd rubiks-cube-solver
   ```

3. Build the project:

   ```bash
   g++ -std=c++17 -o rubiks_cube_solver main.cpp Cube.cpp Solver.cpp -lsfml-graphics -lsfml-window -lsfml-system
   ```

## How to Run

After successfully building the project, run the executable:

```bash
./rubiks_cube_solver
```

## Usage

1. **Scramble the Cube:**
   - Press the 'S' key to scramble the Rubik's Cube.

2. **Solve the Cube:**
   - Press the 'Solve' button to initiate the solving process using Thistlethwaite's algorithm.

3. **Visualize the Solution:**
   - Observe the graphical representation of each step as the solver progresses.


## Controls

- **Rotate Faces:**
  - Use the arrow keys to rotate individual faces of the Rubik's Cube.
  - Or use mouse to toggle between the 6 face colors

## Acknowledgments

- Thistlethwaite's algorithm: [More about the algorithm](https://en.wikipedia.org/wiki/Optimal_solutions_for_Rubik%27s_Cube#Thistlethwaite's_algorithm)
- SFML: [SFML Documentation](https://www.sfml-dev.org/documentation/)
## Image
![rubik'sCubeSolver](https://github.com/UsmanKhalil25/Rubik-sCubeSolver/assets/142806683/306ca2c3-dbfa-416e-a669-3b0bd1a1fd31)

