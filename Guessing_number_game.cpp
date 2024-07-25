#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

struct Player {
    string name;
    int points;
    int hints[3]; // Store hints left for easy, medium, and hard modes
    int lifelines; // Number of lifelines left

    // To facilitate sorting
    bool operator<(const Player& other) const {
        return points > other.points;
    }
};

void loadLeaderboard(vector<Player>& leaderboard) {
    ifstream inFile("leaderboard.txt");
    if (inFile.is_open()) {
        Player player;
        while (inFile >> player.name >> player.points >> player.hints[0] >> player.hints[1] >> player.hints[2] >> player.lifelines) {
            leaderboard.push_back(player);
        }
        inFile.close();
    }
}

void saveLeaderboard(const vector<Player>& leaderboard) {
    ofstream outFile("leaderboard.txt");
    if (outFile.is_open()) {
        for (const auto& player : leaderboard) {
            outFile << player.name << " " << player.points << " "
                    << player.hints[0] << " " << player.hints[1] << " " << player.hints[2] << " "
                    << player.lifelines << endl;
        }
        outFile.close();
    }
}

void showLeaderboard(const vector<Player>& leaderboard) {
    cout << "\n--- Leaderboard ---\n";
    for (const auto& player : leaderboard) {
        cout << player.name << ": " << player.points << " points, "
             << player.lifelines << " lifelines left\n";
    }
    cout << "-------------------\n";
}

void showPlayerStats(const Player& player) {
    cout << "\n--- Player Stats ---\n";
    cout << "Total points earned: " << player.points << "\n";
    cout << "Hints left: \n";
    cout << "  Easy mode: " << player.hints[0] << "\n";
    cout << "  Medium mode: " << player.hints[1] << "\n";
    cout << "  Hard mode: " << player.hints[2] << "\n";
    cout << "Lifelines left: " << player.lifelines << "\n";
    cout << "--------------------\n";
}

int getMaxHints(int mode) {
    switch (mode) {
        case 1: return 5; // Easy
        case 2: return 3; // Medium
        case 3: return 1; // Hard
        case 4: return 0; // Expert
        case 5: return 0; // Legendary
        default: return 0;
    }
}

int getMaxTries(int mode) {
    switch (mode) {
        case 1: return 8; // Easy
        case 2: return 7; // Medium
        case 3: return 5; // Hard
        case 4: return 3; // Expert
        case 5: return 1; // Legendary
        default: return 0;
    }
}

vector<int> generateNumbers(int range, int mode) {
    vector<int> numbers;
    if (range < 20 && mode == 5) {
        while (numbers.size() < 3) {
            int num = rand() % (range + 1);
            if (find(numbers.begin(), numbers.end(), num) == numbers.end()) {
                numbers.push_back(num);
            }
        }
    } else if (mode == 5) { // Legendary mode
        int count = 5;
        while (numbers.size() < count) {
            int num = rand() % (range + 1);
            if (find(numbers.begin(), numbers.end(), num) == numbers.end()) {
                numbers.push_back(num);
            }
        }
    } else {
        numbers.push_back(rand() % (range + 1));
    }
    return numbers;
}

void playGame(Player& player, vector<Player>& leaderboard) {
    int range, mode;
    cout << "Enter the range (0 to N): ";
    cin >> range;
    cout << "Choose mode: 1. Easy 2. Medium 3. Hard 4. Expert 5. Legendary: ";
    cin >> mode;

    if (mode < 1 || mode > 5) {
        cout << "Invalid mode selected. Please choose a valid mode.\n";
        return;
    }

    int maxTries = getMaxTries(mode);
    int maxHints = getMaxHints(mode);
    int hintsLeft = player.hints[mode - 1]; // Use stored hints for the selected mode
    vector<int> numbersToGuess = generateNumbers(range, mode);
    int triesLeft = maxTries;
    int guess;
    bool won = false;

    int triesBeforeHint = 2;

    while (triesLeft > 0) {
        if (range < 20 && mode == 5) {
            cout << "Choose from these numbers: ";
            for (int num : numbersToGuess) {
                cout << num << " ";
            }
            cout << endl;
        }

        cout << "You have " << triesLeft << " tries left. Enter your guess (0-" << range << "): ";
        cin >> guess;

        if (guess < 0 || guess > range) {
            cout << "Invalid guess. Please enter a number within the range.\n";
            continue;
        }

        if (find(numbersToGuess.begin(), numbersToGuess.end(), guess) != numbersToGuess.end()) {
            cout << "Correct! You win!\n";
            int pointsWon = 10;
            if (maxHints > 0 && hintsLeft != maxHints) {
                pointsWon -= 2;
            }
            player.points += pointsWon;
            cout << "You earned " << pointsWon << " points. Total points: " << player.points << "\n";
            won = true;
            break;
        } else {
            cout << "Incorrect guess.\n";
            triesLeft--;

            if (triesBeforeHint == 0 && triesLeft > 0 && hintsLeft > 0) {
                char useHint;
                cout << "Do you want a hint? You have " << hintsLeft << " hints left (y/n): ";
                cin >> useHint;
                if (useHint == 'y' || useHint == 'Y') {
                    hintsLeft--;
                    player.hints[mode - 1] = hintsLeft; // Update stored hints for the selected mode
                    if (guess < numbersToGuess[0]) {
                        cout << "Hint: The number is higher than " << guess << "\n";
                    } else {
                        cout << "Hint: The number is lower than " << guess << "\n";
                    }
                }
                triesBeforeHint = 2;
            } else {
                triesBeforeHint--;
            }
        }
    }

    if (!won) {
        cout << "You lost! The correct number was ";
        for (int num : numbersToGuess) {
            cout << num << " ";
        }
        cout << ".\n";
        player.lifelines--;

        if (player.lifelines == 0) {
            char refill;
            cout << "You have lost all your lifelines! Do you want to refill them for 2 points? (y/n): ";
            cin >> refill;
            if (refill == 'y' || refill == 'Y') {
                if (player.points >= 2) {
                    player.points -= 2;
                    player.lifelines = 5;
                    cout << "Lifelines refilled. 2 points deducted. Total points: " << player.points << "\n";
                } else {
                    cout << "Insufficient points to refill lifelines. You need 2 points but have only " << player.points << " points.\n";
                }
            } else {
                cout << "Game over. You need to refill lifelines to continue playing.\n";
            }
        }
    }

    // Update leaderboard if the player has won any points or lost a lifeline
    bool found = false;
    for (auto& p : leaderboard) {
        if (p.name == player.name) {
            p = player;
            found = true;
            break;
        }
    }
    if (!found) {
        leaderboard.push_back(player);
    }
    sort(leaderboard.begin(), leaderboard.end());
    saveLeaderboard(leaderboard);
}

void buyHint(Player& player) {
    int mode;
    cout << "Choose mode to buy hint for: 1. Easy 2. Medium 3. Hard: ";
    cin >> mode;

    if (mode < 1 || mode > 3) {
        cout << "Invalid mode selected. Please choose a valid mode.\n";
        return;
    }

    if (player.points >= 30) {
        player.points -= 30;
        player.hints[mode - 1] += 1;
        cout << "You have successfully bought a hint for mode " << mode << "! 30 points deducted.\n";
        cout << "Total points: " << player.points << "\n";
    } else {
        cout << "Insufficient points to buy a hint. You need 30 points but have only " << player.points << " points.\n";
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    vector<Player> leaderboard;
    loadLeaderboard(leaderboard);

    Player currentPlayer;
    int choice;

    cout << "Enter your name: ";
    cin >> currentPlayer.name;

    // Check if the player already exists
    bool existingPlayer = false;
    for (auto& player : leaderboard) {
        if (player.name == currentPlayer.name) {
            currentPlayer = player;
            existingPlayer = true;
            break;
        }
    }

    if (!existingPlayer) {
        currentPlayer.points = 0;
        currentPlayer.hints[0] = getMaxHints(1); // Easy mode
        currentPlayer.hints[1] = getMaxHints(2); // Medium mode
        currentPlayer.hints[2] = getMaxHints(3); // Hard mode
        currentPlayer.lifelines = 5; // Start with 5 lifelines
        leaderboard.push_back(currentPlayer);
    }

    do {
        cout << "\n1. Play Game\n2. Show Leaderboard\n3. Buy Hint\n4. Show Player Stats\n5. Exit\nChoose an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                playGame(currentPlayer, leaderboard);
                break;
            case 2:
                showLeaderboard(leaderboard);
                break;
            case 3:
                buyHint(currentPlayer);
                break;
            case 4:
                showPlayerStats(currentPlayer);
                break;
            case 5:
                saveLeaderboard(leaderboard);
                cout << "Exiting game. Goodbye!\n";
                break;
            default:
                cout << "Invalid option. Please choose again.\n";
        }
    } while (choice != 5);

    return 0;
}
