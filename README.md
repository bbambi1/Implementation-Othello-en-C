# Othello Game in C

A simple implementation of the Othello (or Reversi) board game in C. The game offers multiple playing modes and AI strategies.

## Table of Contents

- [Othello Game in C](#othello-game-in-c)
  - [Table of Contents](#table-of-contents)
  - [Features](#features)
  - [Getting Started](#getting-started)
    - [Prerequisites](#prerequisites)
    - [Installation](#installation)
  - [Usage](#usage)
  - [AI Strategies](#ai-strategies)
  - [Contributions](#contributions)
  - [License](#license)

## Features

- Play against another human player.
- Challenge the computer with different AI strategies.
- AI vs. AI mode for fun and testing.

## Getting Started

### Prerequisites

Ensure you have a C compiler installed on your system.

### Installation

1. Clone the repository:
\```bash
git clone <repository-url>
\```
2. Navigate to the project directory and compile:
\```bash
cd othello
gcc -o othello gameplay.c
\```

## Usage

Run the game:
\```bash
./othello
\```
Follow the on-screen instructions to select the game mode and make your moves.

## AI Strategies

- **Random Strategy**: The AI selects a valid move randomly from the available options.
- **Greedy Strategy**: The AI simulates each valid move and picks the one that captures the maximum number of opponent's pieces.
- **Alpha-Beta Pruning**: A depth-limited minimax search algorithm enhanced with alpha-beta pruning for more efficient search.

## Contributions

Pull requests are welcome! For major changes, please open an issue first to discuss what you would like to change.

## License

This project is open source and available under the [MIT License](LICENSE).
