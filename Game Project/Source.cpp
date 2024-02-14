#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cctype>

using namespace std;

// Player class representing a player with a username, score, and name of the game played
class Player {
private:
    string username;
    float score;
    string gamename;
public:
    // Accessor methods for player attributes
    string getUsername() const { return username; }
    string getNameOfTheGamePlayed() const { return gamename; }
    int getScore() const { return score; }

    // Mutator and Template method to update the player's score
    template<class Type>
    void updateScore(Type points) { score += points; }

    //Function overloading example for updateScore, if updateScore does not have a specific value, to decreas the score by 1
    void updateScore() { score--; };

    // Operator Overloading the << operator to display player information
    friend ostream& operator<<(ostream& print, Player user) {
        print << "\nGame is over\n" << endl;
        print << "Player's Username \"" << user.username << "\"" << endl;
        print << "Player's Score \"" << user.score << "\"\n" << endl;
        return print;
    }

    // Parametrized constructor to initialize player attributes
    Player(string userna, string nameOfTheGamePlay) {
        gamename = nameOfTheGamePlay;
        username = userna;
        score = 0;
    }
    // Virtual destructor for the Player class
    virtual ~Player() {}
};

// Abstract base class representing a game
class Game {
public:
    // Pure virtual methods to be implemented by derived classes
    virtual void start() = 0;// to implement each game
    virtual void rules() = 0;// to show games rule
    // End function for terminate game
    void end() {
        cout << player;
    }
    // Default constructor
    Game() :player("Default", "Default") {}

    // Constructors for the different games for constructor with different parameters
    Game(int attempt, string user, string nameofgame) :player(user, nameofgame) {
        number_of_attempts = attempt;
    }
    Game(string user, string nameofgame) :player(user, nameofgame) {}
    // Virtual destructor for the Game class
    virtual ~Game() {}
protected: //Protected member attributes
    int number_of_attempts;
    Player player;
    int difficulty_level;
};


class Find_The_Synonym : public Game {
private:
    string wordlist[5] = { "Small","Sad","Fast","Talk","Look" }; // to store word list

    string synonymWordlist[5] = { "Tiny","Unhappy","Quick","Speak","See" }; // to store synonyms of word list

public:
    // Implementation of the start method for the Find_The_Synonym game
    void start() {

        bool played[5] = { false };// to store it asked or not

        int number_of_synonym_word = 5; // to use number of the synonym word

        int random; // to use rand

        string guess; // to get guess from the user

        bool finded = false; // to dedect its finded or not

        while (true) { //while loop that helps us determine the question to be asked randomly
            random = rand() % 5; // Assigns a number between 0 and 5
            if (played[random] == false) {//If it has not been asked before, we make it asked and break the loop.
                played[random] = true;
                break;
            }
            else// If it has been asked, the loop continues until it finds it has not been asked.
                continue;
        }

        player.updateScore(number_of_attempts); //We assign score of the question, it's five

        while (true) {
            cout << "\nFind the synonym word for\"" << wordlist[random] << "\"" << endl;
            cout << "You have " << number_of_attempts << " number of attempts\nEnter your guess: ";
            cin >> guess; // to get guess

            if (guess != synonymWordlist[random]) {// if its not true, it's shows error message
                cout << "Unfortunately your answer is false :/" << endl;
                number_of_attempts--;// to decrease number of attempt
                player.updateScore();// to decrease score of the question with operator overloading
                if (number_of_attempts == 0) { //Error message if there are no more attempts
                    cout << "\nUnfortunately you have no more attempts for this question\n\nCorrect answer is \"" << synonymWordlist[random] << "\"\n" << endl;
                    number_of_attempts = 5;//to renew the attempt for the next question
                    break;//If there are no more questions left, we break this loop to move on to the next question.
                }
            }
            else {// if we found the answer, shows message
                cout << "\nCongratulations !! You Found Correct Answer\nYou get " << number_of_attempts << " score for this question\n" << endl;
                number_of_attempts = 5; //to renew the attempt for the next question
                break; //If there are no more questions left, we break this loop to move on to the next question.
            }
        }

    }

    void rules() { // To show rules of the game
        cout << "\n\n\"" << player.getNameOfTheGamePlayed() << "\" Game Rules:\n";
        cout << "You need to guess the synonym for the given word.\n";
        cout << "You have 5 attempts to guess the synonym.\n";
        cout << "The game will provide feedback on each guess.\n";
        cout << "Your score is based on the number of remaining attempts.\n";
    }
    // Constructor for the Find_The_Synonym class
    Find_The_Synonym(int attempt, string user, string nameofgame) : Game(attempt, user, nameofgame) {}
    // Destructor for the Find_The_Synonym class
    ~Find_The_Synonym() {}
};

class GuessMovie : public Game {
private:
    string movieList[3][5] = { {"Pulp Fiction","Jurassic Park","Fight Club","Forrest Gump","The Intouchables"}, // easy mode index [0][x] x is column
                                 {"The Dark Knight","The Lion King","Top Gun Maverick","Alice in Wonderland","The Green Mile"},// medium mode index [1][x] x is column
                                 {"The Grand Budapest Hotel","Up in the Air","Night at the Museum","The Tree of Life","There Will Be Blood"} };// hard mode index [2][x] x is column

public:
    void start() {    // Implementation of the start method for the GuessMovie game

        char hiddenMovieName[100]; // to hide movie name with '*'

        char guessfilm[100]; // to get guess film name from the user
        char guesschar; // to get guess char from the user

        int index; // to roam the arrays and strings

        int guessSelect; // to get guess choice

        int random; // to use rand function

        char pressedAlphabet[26]; // to store allready entered guesschar's

        int sizeofPressedAlphabet = 0;// to store sizeof array and use pressedAlphabet array

        random = rand() % 5; // Since there are 5 questions for each difficulty, we enter a number between 0 and 4 into the random.

        for (index = 0; movieList[difficulty_level - 1][random][index] != '\0'; index++) { //This for loop will run until it reaches the end of the movie string we selected with the random variable, that is, until it reaches the '\0' character.
            if (isalpha(movieList[difficulty_level - 1][random][index])) {//If it is a character from the alphabet we need to hide it
                hiddenMovieName[index] = '*';
            }
            else// if not there should be a space
                hiddenMovieName[index] = ' ';
        }

        hiddenMovieName[index] = '\0'; // append '\0' to end the string

        while (true) { // loop for game flow
            bool letterFinded = false; //bool variable to check if letter is found or not

            cout << "\nFind the Movie Name \"" << hiddenMovieName << "\"" << endl; //We asked the user the question
            cout << "You have " << number_of_attempts << " number of attempts\nGuess Letter (1)\nGuess the Movie Name (2)\n";
            cin >> guessSelect; //We get the user's preference

            if (guessSelect == 1) { //If the user wants to guess the letter

                while (true) {
                    bool whetherPressed = false;// bool variable to store and determine whether the letter to be guessed has been guessed before

                    cout << "Press the letter guess: "; // to get letter guess from the user
                    cin >> guesschar;

                    if (sizeofPressedAlphabet == 0) { // if its first press add to entered letter guesses
                        pressedAlphabet[sizeofPressedAlphabet++] = guesschar;
                        break;
                    }
                    else {
                        for (int index = 0; index < sizeofPressedAlphabet; index++) { //If it is not the first guessed letter, we check whether that letter has been guessed before.
                            if (pressedAlphabet[index] == guesschar) {
                                whetherPressed = true; // If entered, it is true
                                break;
                            }
                        }
                    }

                    if (whetherPressed) {//We checked if this was true above.
                        cout << "\nYou already guessed this letter, try making different guesses\n" << endl;
                        continue; // sends it to the beginning of the loop for a different letter guess
                    }
                    else {
                        pressedAlphabet[sizeofPressedAlphabet++] = guesschar; //If it has not been entered before, we put that letter into the array for next guesses.
                        break;
                    }
                }

                for (int index = 0; movieList[difficulty_level - 1][random][index] != '\0'; index++) { //This for loop will run until it reaches the end of the movie string we selected with the random variable, that is, until it reaches the '\0' character.
                    if (tolower(movieList[difficulty_level - 1][random][index]) == tolower(guesschar)) { //We make all the letters in the same indexes lowercase and check whether they are equal. tolower function makes the letter small for us. We do this because of the value difference between lowercase letters and uppercase letters in the ascii table.
                        hiddenMovieName[index] = movieList[difficulty_level - 1][random][index];// If the guessed letter is found in the movie name, we replace the letter in that index with the letter in the movie in hidden. So now instead of * it should be letter
                        letterFinded = true; //To check whether the letter is present or not
                    }
                }

                if (letterFinded) { //If a letter is found, we show a congratulatory message and check whether all letters are guessed correctly. If all the letters are found, we finish the game and the user earns points equal to the remaining attempts.
                    cout << "\nCongratulations, you found a letter\n" << endl;
                    if (hiddenMovieName == movieList[difficulty_level - 1][random]) {
                        cout << "\nCongratulations !! You Found Movie Name\nYou get " << number_of_attempts << " score for this question\n" << endl;
                        cout << "\"" << movieList[difficulty_level - 1][random] << "\"\n" << endl;
                        player.updateScore(number_of_attempts);
                        break;
                    }
                }
                else { //error message if letter not found
                    cout << "\nUnfortunately, the letter you guessed was not found.\n" << endl;
                }

                number_of_attempts--; //to reduce the remaining attempt

            }
            else if (guessSelect == 2) { //If the user wants to guess the name of the movie
                cout << "Enter the Movie Name guess: " << endl;
                cin.ignore(); // to avoid cin and cin.get() functions flow error problem
                cin.get(guessfilm, 100); // we use the cin.get() because there are spaces in the name of the movie

                int guesslen = strlen(guessfilm);// We used the strlen() function in the cstring library to calculate the string length of the guess.
                bool whetherguess = false; //To check if the movie is found or not

                for (int index = 0; index < guesslen; index++) {//A for loop that runs up to the length of the guessed string
                    if (tolower(movieList[difficulty_level - 1][random][index]) == tolower(guessfilm[index])) {// We check whether the guess made is correct by checking the indexes one by one. We make all letters lowercase and check them because the int values ​​of uppercase characters are different so that there will be no problems. If there is even one unequal letter, we end the loop by assigning the fact that the movie is not guessed correctly to the bool variable.
                        whetherguess = true;
                    }
                    else {
                        whetherguess = false;
                        break;
                    }
                }

                if (whetherguess) {//If it is guessed correctly, we gain points equal to the remaining attempt and finish the game. If not, we show an error message and reduce the remaining attempt by 1.
                    cout << "\nCongratulations !! You Found Movie Name\nYou get " << number_of_attempts << " score for this question\n" << endl;
                    player.updateScore(number_of_attempts);
                    break;
                }
                else {
                    cout << "\nUnfortunately, the Movie Name you guessed was not true.\n" << endl;
                }

                number_of_attempts--;
            }
        }

    }

    void rules() {// To show rules of the game
        cout << "\n\n\"" << player.getNameOfTheGamePlayed() << "\" Game Rules:\n";
        cout << "A random movie name will be chosen based on the difficulty level.\n";
        cout << "You need to guess the movie name.\n";
        cout << "You have 10 attempts to guess the synonym.\n";
        cout << "The game will provide feedback on each guess.\n";
        cout << "Your score is based on the number remaining attempts.\n";
        cout << "Easy mode contains 2 words movies.\nMedium mode contains 3 words movies.\nHard mode contains 4 word movies.\n";
        cout << "Enter the difficult level (Easy 1,Medium 2, Hard 3): ";
        cin >> difficulty_level;
    }

    // Destructor for the GuessMovie class
    ~GuessMovie() {}

    // Constructor for the GuessMovie class
    GuessMovie(int attempt, string user, string nameofgame) : Game(attempt, user, nameofgame) {}

};

class WordGame : public Game {
private:
    string questionsAnswers[42][2] = {  // In the Word Game, 2 questions are asked each, with answers consisting of words with 4,5,6,7,8,9,10 letters. We created a two-dimensional string array with questions in the first column and answers in the second column.
        {"Name a planet in our solar system.", "Mars"},// 4 WORD list
        {"What is the main ingredient in sushi?", "Rice"},
        {"What is the currency used in the Eurozone?", "Euro"},
        {"Name a type of flower that is often associated with love.", "Rose"},
        {"What is the currency used in Mexico?", "Peso"},
        {"What is the capital of Italy?", "Rome"},

        {"What is the capital of France?", "Paris"},// 5 WORD
        {"What is the main ingredient in chocolate?", "Cocoa"},
        {"Name a country in East Asia.", "Japan"},
        {"What is the currency used in the United Kingdom?", "Pound"},
        {"What do you call a baby dog?", "Puppy"},
        {"What is the opposite of \"old\"?", "Young"},

        {"Name a type of fruit that is yellow and curved.", "Banana"},//6 WORD
        {"What is the capital of Russia?", "Moscow"},
        {"Name a famous scientist who discovered the law of gravity.", "Newton"},
        {"Name a country in South America.", "Brazil"},
        {"I speak without a mouth and hear without ears. I have no body, but I come alive with the wind. What am I?", "Echoes"},
        {"Name a planet with rings.", "Saturn"},

        {"What is the main ingredient in guacamole?", "Avocado"},//7 WORD
        {"Name a famous scientist who developed the theory of relativity.", "Einstein"},
        {"What is the largest ocean on Earth?", "Pacific"},
        {"What is the capital of China?", "Beijing"},
        {"Name a planet known as the \"Gas Giant.\"", "Jupiter"},
        {"What is the study of the structure of the body?", "Anatomy"},

        {"What is the capital of Brazil?", "Brasilia"},//8 WORD
        {"Name a famous painting by Leonardo da Vinci.", "Mona Lisa"},
        {"What has keys but can't open locks?", "Keyboard"},
        {"What is a short-lived burst of light in the sky?", "Firework"},
        {"What is the process of a liquid turning into a solid?", "Freezing"},
        {"What is a substance that speeds up a chemical reaction?", "Catalyst"},

        {"What is the main ingredient in hummus?", "Chickpeas"},//9 WORD
        {"What is a large, swirling storm with strong winds, typically over warm waters?", "Hurricane"},
        {"Which island country is known for its unique wildlife, including kangaroos and koalas?", "Australia"},
        {"What word means the study of celestial bodies?", "Astronomy"},
        {"What is the outermost layer of the Earth's atmosphere?", "Exosphere"},
        {"What is the process of drawing air into the lungs and exhaling it?", "Breathing"},

        {"What is the main ingredient in a margherita pizza?", "Mozzarella"},//10 WORD
        {"The more you take, the more you leave behind. What am I?", "Friendship"},
        {"What is a sudden, violent shaking of the ground, often causing damage?", "Earthquake"},
        {"What is the capital city of Mexico?", "Mexico City"},
        {"What is the capital of New Zealand?", "Wellington"},
        {"All of the planning, organizing, directing and controlling activities to achieve the goals of an organization.", "Management"}
    };
public:
    void start() { // Implementation of the start method for the Word game


        char hiddenAnswer[100]; //array to display the answers as '*'

        char guess[100]; //array to get guess from user

        char revealchar;// char variable to determine which char will be randomly revealed

        // Variables for indexing and selecting guesses
        int index;

        int guessSelect;

        // Variables for randomization and question indexes
        int random;

        int questionindex1 = 5; // Since the first two questions were chosen from index 0 to 5, we set such variables. Because questions with 4-letter answers are in these indexes.

        int questionindex2 = 0;

        // to store question number
        int questionNumber = 1;

        // Array to keep track of asked questions
        bool asked[42] = { false };


        while (questionNumber <= 14) { //while loop for ask question, its works until number of the question is 14
            int questionPoint = 0;// to store question point
            int answerLen = 0; // to store answerlen for point evaluation criteria
            int revealIndex = 0; // to store revealed index

            // to select a random unanswered question
            while (true) {
                random = rand() % (questionindex1 - questionindex2 + 1) + questionindex2;
                if (asked[random]) {
                    continue;
                }
                asked[random] = true;
                break;
            }

            // Initialize hiddenAnswer array based on the length of the answer
            for (index = 0; questionsAnswers[random][1][index] != '\0'; index++) { // its works until answer index is null
                if (isalpha(questionsAnswers[random][1][index])) { // if its alphabet, add '*' to hiddenanswer array
                    hiddenAnswer[index] = '*';
                    questionPoint += 100; // to arrange question point based word length
                    answerLen += 1;
                }
                else
                    hiddenAnswer[index] = ' '; // if its not alphabet, its means its whitespace
            }

            hiddenAnswer[index] = '\0'; //Since it is a char array, we put null at the end

            while (true) {// loop for game flow
                cout << questionNumber << ". Question\n" << "You can get " << questionPoint << " point for this question" << endl; //We ask the user the question we asked, and we tell him how many points he will get from this question. The score of the question is equal to the number of letters in the answer. For example, if a question has a 4-letter answer, 4 * 100 = 400 points. There will be 2 questions from each letter, the first two questions being 4 letters, and a total of 14 questions will be asked.
                cout << "\nQuestion: " << questionsAnswers[random][0] << endl;
                cout << "Answer: " << hiddenAnswer << "\n" << endl;
                cout << "\nReveal 1 letter (1)\nGuess the answer (2)\n"; //The user is asked to see 1 random letter from hiddenAnswer (this option will cause the score of the question to decrease by 100 points) or to guess the answer.
                cin >> guessSelect;

                if (guessSelect == 1) {//If the user wants a random letter to be revealed
                    while (true) { //A while loop to randomly open an index that has not been revealed before
                        revealIndex = rand() % (sizeof(hiddenAnswer) - 1);//Allows random numbers to be assigned within a range equal to the length of hiddenAnswer.
                        if (hiddenAnswer[revealIndex] == '*') {//If that index is '*', that is, if it has not been revealed before, it is revealed and the loop is finished, otherwise it continues until it is found.
                            hiddenAnswer[revealIndex] = questionsAnswers[random][1][revealIndex];
                            break;
                        }
                    }

                    if (hiddenAnswer == questionsAnswers[random][1]) {//If the user cannot find the answer to the question and reveals all the letters, an if statement is used to tell the user that he/she got 0 points and move on to the next question.
                        cout << "\nAnswer: " << hiddenAnswer << ", You will get 0 point for this question\n" << endl;
                        break;
                    }
                    else//If the user wanted only 1 letter to be revealed, to reduce the score of the question by 100 points.
                        questionPoint -= 100;
                }
                else if (guessSelect == 2) {//if the user wants to guess the answer
                    cout << "\nEnter your guess: ";
                    cin.ignore();//Since the answers to some questions contain spaces, we added cin.ignore() to avoid incompatibility between cin and cin.get(). This ensures that the value we enter in cin does not go to the cin.get() function.
                    cin.get(guess, 100);//We get guess from the user

                    if (guess == questionsAnswers[random][1]) {//If the user guesses correctly, user earns points as many points as the letter user knows (if user has revealed a letter before, user loses points as much as (100*number of letters revealed)).
                        player.updateScore(questionPoint);
                        cout << "\nCongratulations !! You Found Answer\nYou get " << questionPoint << " score for this question\n" << endl;
                        break;//break to move on to the next question;
                    }
                    else
                        cout << "\nUnfortunately, the answer you guessed was not true.\n" << endl;//If the user does not know the question
                }

            }

            questionNumber++;//to move on to the next question

            if ((questionNumber % 2) == 1) {//We wrote such an if statement because I asked 2 questions with 4-letter answers, 2 questions with 5-letter answers, and 2 questions with 10-letter answers. The logic here is that if the number of questions is more than 1 multiple of 2, we need to add 6 to the index in the question and answer array we defined at the top because we need to show the user the question with +1 more lettered answers.
                questionindex1 += 6;
                questionindex2 += 6;
            }
        }
    }

    void rules() {// To show rules of the game
        cout << "\n\n\"" << player.getNameOfTheGamePlayed() << "\" Game Rules:\n";
        cout << "You will be presented with a series of word-based 14 questions.\n";
        cout << "Each question has a hidden answer represented by asterisks (*).\n";
        cout << "You can choose to reveal one letter of the answer or guess the entire answer.\n";
        cout << "For each revealed letter, you lose 100 points from the potential score for that question.\n";
        cout << "The potential score varies depending on the length of the answers to the questions.\nFor example, if the answer to the question is 5 letters long, the potential score is 500.\n";
        cout << "Guessing the complete answer correctly adds the total potential score to your overall score.\n";
        cout << "The game consists of 14 questions with varying word lengths(4,5,6...10 letter).\n";
        cout << "The goal is to accumulate as many points as possible by the end of the game.\n" << endl;
    }

    // Destructor for the WordGame class
    ~WordGame() {}

    // Constructor for the WordGame class, we called a different base constructor because the attempts value is not used in this game.
    WordGame(string user, string nameofgame) :Game(user, nameofgame) {}
};



void gameschema(Game* game[], bool& exitmenu, int gameselect) { //Function for game flow scheduling
    int intexitmenu;

    game[gameselect]->rules(); // it shows rules of the selected game
    game[gameselect]->start(); // it starts game
    game[gameselect]->end();   // it terminates the selected game and shows us player's score and username
    cout << "Press 1 to play again, press 2 to return menu, press 3 to exit the game" << endl; // to ask to user play again, return menu or exit the game
    cin >> intexitmenu;
    if (intexitmenu == 1)
        gameschema(game, exitmenu, gameselect); // if user wants to play again, we call this function again
    else if (intexitmenu == 2) // if user wants to return menu
        exitmenu = false;
    else                       // if user exit to gane
        exitmenu = true;
    cout << "\n";

}

int main() {
    Game* game[3] = { nullptr, nullptr, nullptr };     // Pointer array to store objects of the Game class
    int gameselect; // Variable to store the selected game
    char username[100]; // Array to store the username
    bool exitmenu = false; // Variable to control whether to exit the menu or not

    srand(time(0)); // for create random number creator with current time

    cout << "Enter your username" << endl; // to get username
    cin.get(username, 100);

    cin.ignore(); // to avoid newline error

    while (true) {// menu loop
        cout << "\nWelcome the Game Menu\nGame List:\n(1) Find The Synonym\n(2) Guess Movie\n(3) Word Game\n(4) If you want to quit the game\nEnter your option: " << endl;
        cin >> gameselect; // to get game selection

        // check the selected game and create an objects of the corresponding game
        if (gameselect == 1) {
            game[gameselect - 1] = new Find_The_Synonym(5, username, "Find The Synonym");// we pass the values(attempts, username, gamename) into constructor
            // Call the function for game flow with the selected game type
            gameschema(game, exitmenu, gameselect - 1);
        }
        else if (gameselect == 2) {
            game[gameselect - 1] = new GuessMovie(10, username, "Guess Movie");
            gameschema(game, exitmenu, gameselect - 1);
        }
        else if (gameselect == 3) {
            game[gameselect - 1] = new WordGame(username, "Word Game");// we use different constructor this game, because it doesnt requiere attempt value
            gameschema(game, exitmenu, gameselect - 1);
        }
        else if (gameselect == 4) { // if user wants to quit game
            exitmenu = true;
        }
        else {// to display error message for wrong selection
            cout << "\nYou selected wrong option\nTry again" << endl;
        }

        if (exitmenu == true) {// check if the user chose to exit the menu, if statemant for delete game objects
            if (game[0] != nullptr) //to check is played or not
                delete game[0];
            if (game[1] != nullptr)
                delete game[1];
            if (game[2] != nullptr)
                delete game[2];
            return 0;
        }
    }
}