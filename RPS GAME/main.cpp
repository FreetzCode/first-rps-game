#include <iostream>
#include <random>

using namespace std;

void gameLoop(mt19937 &gen, string username);
void battle(int &player_health, int &player_damage, int enemy_health, int enemy_damage, string enemy_name, string username, int &wins, int &losses, int &ties, mt19937 &gen, int level, int base_health);
void displayStats(int level, int player_health, int player_damage, int enemy_health, int enemy_damage, string username, string enemy_name);
int getPlayerChoice();
void levelUpgrade(int &base_health, int &player_damage);
void clearScreen();

int main() {
    string username;
    cout << "Enter your Username: ";
    cin >> username;

    random_device rd;
    mt19937 gen(rd());

    gameLoop(gen, username);

    return 0;
}

void gameLoop(mt19937 &gen, string username) {
    int base_health = 50;
    int player_health = base_health, player_damage = 10;

    string enemy_name[]{"Rat", "Snake", "Dragon"};
    int enemy_health[]{50, 80, 100};
    int enemy_damage[]{10, 15, 20};

    int wins = 0, losses = 0, ties = 0, total_levels = 3;

    for (int i = 0; i < total_levels; i++) {

        battle(player_health, player_damage, enemy_health[i], enemy_damage[i], enemy_name[i], username, wins, losses, ties, gen, i, base_health);

    }

    cout << "\nGame Over! Final Stats:\n";
    cout << "Wins: " << wins << " | Losses: " << losses << " | Ties: " << ties << endl;
    cout << "Thank you for playing, " << username << "!" << endl;
}

void battle(int &player_health, int &player_damage, int enemy_health, int enemy_damage, string enemy_name, string username, int &wins, int &losses, int &ties, mt19937 &gen, int level, int base_health) {
    while (player_health > 0 && enemy_health > 0) {
        clearScreen();
        displayStats(level, player_health, player_damage, enemy_health, enemy_damage, username, enemy_name);

        int player_choice = getPlayerChoice();
        uniform_int_distribution<int> dist(1, 3);
        int enemy_choice = dist(gen);

        if (player_choice == 1 && enemy_choice == 2) {
            cout << "\nYou chose Rock, Enemy chose Paper. You Lose!\n";
            player_health -= enemy_damage;
            losses++;
        } else if (player_choice == 1 && enemy_choice == 3) {
            cout << "\nYou chose Rock, Enemy chose Scissors. You Win!\n";
            enemy_health -= player_damage;
            wins++;
        } else if (player_choice == 1 && enemy_choice == 1) {
            cout << "\nYou both chose Rock. It's a Tie!\n";
            ties++;
        } else if (player_choice == 2 && enemy_choice == 1) {
            cout << "\nYou chose Paper, Enemy chose Rock. You Win!\n";
            enemy_health -= player_damage;
            wins++;
        } else if (player_choice == 2 && enemy_choice == 2) {
            cout << "\nYou both chose Paper. It's a Tie!\n";
            ties++;
        } else if (player_choice == 2 && enemy_choice == 3) {
            cout << "\nYou chose Paper, Enemy chose Scissors. You Lose!\n";
            player_health -= enemy_damage;
            losses++;
        } else if (player_choice == 3 && enemy_choice == 1) {
            cout << "\nYou chose Scissors, Enemy chose Rock. You Lose!\n";
            player_health -= enemy_damage;
            losses++;
        } else if (player_choice == 3 && enemy_choice == 2) {
            cout << "\nYou chose Scissors, Enemy chose Paper. You Win!\n";
            enemy_health -= player_damage;
            wins++;
        } else if (player_choice == 3 && enemy_choice == 3) {
            cout << "\nYou both chose Scissors. It's a Tie!\n";
            ties++;
        } else {
            cout << "\nInvalid Choice! Please select 1, 2, or 3.\n";
        }

        cout << "\nCurrent Stats:\n";
        cout << "Player Health: " << player_health << "\n";
        cout << "Enemy Health: " << enemy_health << "\n";

        if (player_health <= 0) {
            cout << "\nGame Over! You Lost!\n";
        }
        if (enemy_health <= 0) {
            cout << "\nCongratulations! You Defeated the Enemy!\n";
            levelUpgrade(base_health, player_damage);
            player_health = base_health; // Applies the new maximum health
        }

        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }
}

void displayStats(int level, int player_health, int player_damage, int enemy_health, int enemy_damage, string username, string enemy_name) {
    cout << "\nLEVEL " << level + 1 << ": [" << enemy_name << "]" << endl;
    cout << username << " - HP: " << player_health << "  Damage: " << player_damage << endl;
    cout << enemy_name << " - HP: " << enemy_health << "  Damage: " << enemy_damage << endl;
}

int getPlayerChoice() {
    int player_choice;
    while (true) {
        cout << "\nChoose your hand!\n";
        cout << "1. Rock\n";
        cout << "2. Paper\n";
        cout << "3. Scissors\n";
        cout << "Your hand: ";
        cin >> player_choice;

        if  (player_choice < 1 || player_choice > 3) {
            cout << "Invalid choice! Please select 1, 2, or 3.\n";
        } else {
            break;
        }
    }
    return player_choice;
}

void levelUpgrade(int &base_health, int &player_damage) {
    int upgrade;
    while (true) {
        cout << "\nChoose your Upgrade!: ";
        cout << "\n1. Health +50";
        cout << "\n2. Damage +10\n";
        cout << "Your choice: ";
        cin >> upgrade;

        if (upgrade != 1 && upgrade != 2) {
            cout << "Invalid choice! Please select 1 or 2.\n";
        } else {
            if (upgrade == 1) {
                cout << "\nYou chose Health +50\n";
                base_health += 50;
            } else if (upgrade == 2) {
                cout << "\nYou chose Damage +10\n";
                player_damage += 10;
            }
            break;
        }
    }
}

void clearScreen() {
    system("CLS");
}
