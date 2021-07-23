#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

int DEFAULT_SIDES = 20;

// Prints the options menu
void print_menu() {
    cout << "a. Dice Roll" << endl;
    cout << "b. Skill Check" << endl;
    cout << "c. Attack Roll" << endl;
    cout << "q. Quit" << endl;
    cout << "Select an option: ";
}

// Returns a random number within a given constraint
size_t roll_die(size_t sides) {
    return (rand() % sides) + 1;
}

// Asks the user for the number of dice and number of sides and prints the resulting rolls
void dice_roll() {
    size_t num = 0;
    cout << "How many dice do you want to roll? ";
    cin >> num;
    size_t sides = 0;
    cout << "How many sides do the dice have? ";
    cin >> sides;
    unsigned long total = 0;
    for (size_t iter = 0; iter < num; iter++) {
        size_t roll = roll_die(sides);
        cout << roll << " ";
    }
    cout << endl;
    cin.get();
    cin.get();
}

// Returns the max of two numbers
size_t max(size_t a, size_t b) {
    if (a > b) {
        return a;
    }
    return b;
}

// Returns the min of two numbers
size_t min(size_t a, size_t b) {
    if (a < b) {
        return a;
    }
    return b;
}

// Returns true or false based on yes or no
bool check_bool() {
    string value = "";
    cin >> value;
    if (value == "yes") {
        return true;
    } else if (value == "no") {
        return false;
    } else {
        cout << "Please input 'yes' or 'no': ";
        cin >> value;
    }
}

// Asks user if rolling with advantage or disadvantage and returns values accordingly
size_t roll_check(size_t sides = DEFAULT_SIDES) {
    bool adv = false, dis = false;
    cout << "Roll with advantage? ";
    adv = check_bool();
    cout << "Roll with disadvantage? ";
    dis = check_bool();
    if (adv & !dis) {
        return max(roll_die(sides), roll_die(sides));
    } else if (dis & !adv) {
        return min(roll_die(sides), roll_die(sides));
    } else {
        return roll_die(sides);
    }
}

// Asks for ability modifier, rolls dice, and outputs the result
void skill_check() {
    int mod = 0;
    size_t roll = 0;
    cout << "What is the ability modifier? ";
    cin >> mod;
    roll = roll_check();
    cout << roll << " + " << mod << " = " << roll + mod << endl;
    cin.get();
    cin.get();
}

// Rolls damage based on the ability modifier, crit status, and number of dice and sides
void damage_roll(size_t crit) {
    size_t num = 0, sides = 0, mod = 0, total = 0, roll = 0;
    cout << "How many damage dice do you roll? ";
    cin >> num;
    cout << "How many sides do the dice have? ";
    cin >> sides;
    cout << "What is your damage modifier? ";
    cin >> mod;
    for (size_t if_crit = 0; if_crit < crit; if_crit++) {
        roll = roll_die(sides);
        total += roll;
        cout << roll;
        for (size_t iter = 1; iter < num; iter++) {
            roll = roll_die(sides);
            total += roll;
            cout << " + " << roll;
        }
    }
    total += mod;
    cout << " + " << mod << " = " << total << endl;
}

// Rolls dice to see if attack hits then rolls for appropriate damage
void attack_roll() {
    int mod = 0;
    size_t roll = 0;
    cout << "What is your attack modifier? ";
    cin >> mod;
    roll = roll_check();
    cout << roll << " + " << mod << " = " << roll + mod << endl;
    if (roll == 20) {
        damage_roll(2);
    } else {
        bool hits = false;
        cout << "Does the attack hit? ";
        hits = check_bool();
        if (hits) {
            damage_roll(1);
        }
    }
    cin.get();
    cin.get();
}

// Controls operation of the program
int main() {
    char input = '\0';
    srand(time(0));
    cout << "Welcome to D&D dice roller." << endl << endl;
    while (input != 'q') {
        print_menu();
        cin >> input;
        switch (input) {
            case 'a':
                dice_roll();
                break;
            case 'b':
                skill_check();
                break;
            case 'c':
                attack_roll();
                break;
            default:
                cout << "Please try again." << endl;
        }
    }
    return 0;
}
