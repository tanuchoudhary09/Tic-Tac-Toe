# Tic-Tac-Toe AI (C Implementation) 🎮

An algorithmic execution of Tic-Tac-Toe featuring an unbeatable artificial intelligence engine running in pure C.

## 🧠 Algorithmic Paradigm
The computer strategy is driven by a recursive **Minimax Evaluation Decision Tree**. At any board junction, the engine maps out every theoretical game branch to select the mathematically optimal position:
* Maximizes the reward score when tracking computer strategies ($+10$).
* Minimizes the penalty depth when tracking counter-player movements ($-10$).

## 🛠️ Build & Compilation Strategy
This repository leverages build automation via a local `Makefile`. Run the compilation utilities from your terminal environment:

```bash
# Build the binary using the automated Makefile matrix
make

# Run the terminal interface application
./ttt

# Clear the binary artifacts when finished
make clean
