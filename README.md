# C++ Object-Oriented Game Project

This project is a console-based application written in C++ that features a collection of three mini-games. The primary goal of this project is to demonstrate a strong understanding of Object-Oriented Programming (OOP) principles, including inheritance, polymorphism, abstract classes, and operator overloading.

## Key C++ Concepts Demonstrated

This project was designed to showcase several core C++ features:

-   **Object-Oriented Programming (OOP):** The entire architecture is built around classes and objects, encapsulating data and behavior.
-   **Inheritance:** A base `Game` class provides a common interface, and specific game classes (`Find_The_Synonym`, `GuessMovie`, `WordGame`) inherit from it.
-   **Polymorphism:** The program uses a `Game*` pointer array to dynamically create and manage different game objects at runtime. Virtual functions (`start()`, `rules()`) allow the correct game logic to be executed through a base class pointer.
-   **Abstract Classes and Pure Virtual Functions:** The `Game` class is an abstract base class with pure virtual functions (`virtual void start() = 0`), forcing all derived game classes to implement their own specific logic.
-   **Templates:** The `Player::updateScore()` method is a template function, allowing the score to be updated with different numeric types (e.g., `int` or `float`).
-   **Function Overloading:** The `Player::updateScore()` method is overloaded to provide different ways to modify the player's score.
-   **Operator Overloading:** The `<<` operator is overloaded for the `Player` class, enabling easy and intuitive printing of player details to the console (e.g., `cout << player;`).
-   **Dynamic Memory Management:** Game objects are created dynamically using `new` and properly deallocated using `delete` to manage memory.

## Features

-   **Main Menu:** A user-friendly menu to select one of the three available games or quit the application.
-   **Player Management:** A `Player` class tracks the user's name and score throughout the session.
-   **Dynamic Game Selection:** The program dynamically allocates memory for the selected game, demonstrating flexible code structure.
-   **Score Tracking:** Each game updates the player's score based on performance.
-   **Replayability:** Users can choose to play a game again, return to the main menu, or exit after a game ends.

## The Games

### 1. Find The Synonym
A simple word game where the player is given a word and must guess its synonym.
-   **Objective:** Guess the correct synonym.
-   **Gameplay:** You have 5 attempts per word. Your score is based on how many attempts you have left when you guess correctly.

### 2. Guess The Movie
A Hangman-style game where the player tries to guess the name of a movie.
-   **Objective:** Guess the movie title by guessing letters or the full name.
-   **Gameplay:** Choose a difficulty level (Easy, Medium, Hard). You have 10 attempts to solve the puzzle. Revealing letters that are not in the title costs an attempt.

### 3. Word Game
A trivia-style game with 14 questions of increasing word length (from 4 to 10 letters).
-   **Objective:** Answer a series of questions to earn points.
-   **Gameplay:** The answer is hidden. You can choose to either guess the full answer or reveal one letter at a time. Revealing a letter costs 100 points from the question's potential score.

## How to Compile and Run

You will need a C++ compiler (like g++ on Linux/macOS or MinGW/MSVC on Windows) to run this project.

1.  **Clone the repository or download the source code:**
    ```bash
    git clone https://github.com/Oguzhan2022/Game-Project.git
    cd Game-Project
    ```

2.  **Compile the code:**
    Open a terminal or command prompt in the project directory and run the following command:
    ```bash
    g++ main.cpp -o GameProject
    ```
    *(Assuming your main file is named `main.cpp`)*

3.  **Run the executable:**
    -   On Windows:
        ```bash
        GameProject.exe
        ```
    -   On macOS or Linux:
        ```bash
        ./GameProject
        ```

## Code Structure Overview

-   **`Player` Class:** Manages the player's state, including username and score. It showcases operator and function overloading, as well as templates.
-   **`Game` Class:** An abstract base class that defines the common interface for all games. It uses pure virtual functions to enforce implementation in derived classes.
-   **`Find_The_Synonym`, `GuessMovie`, `WordGame` Classes:** These are the concrete game classes that inherit from `Game` and implement the specific logic for each mini-game.
-   **`main()` function:** Contains the main application loop, handles user input for the menu, and manages the lifecycle of the game objects.
