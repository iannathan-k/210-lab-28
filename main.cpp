#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <numeric>
#include <algorithm>
#include "Goat.h"
using namespace std;

// COMSC-210 | Lab 28 | Ian Kusmiantoro
const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;
const int ADD = 1, DELETE = 2, LIST = 3, QUIT = 4;

int select_goat(const list<Goat>& trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(const list<Goat>& trip);
void accumulate_ages(const list<Goat>& trip);
void clear_goats(list<Goat>& trip);
void find_goat(const list<Goat>& trip);
void age_goats(list<Goat>& trip);
void sort_goats(list<Goat>& trip);
int main_menu();

int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    list<Goat> trip; // the actual list
    int choice = -1;
    while (choice != QUIT) { // Loop till the user quits
        choice = main_menu();

        if (choice == ADD) {
            add_goat(trip, names, colors);
        }
        else if (choice == DELETE) {
            delete_goat(trip);
        }
        else if (choice == LIST) {
            display_trip(trip);
        } else if (choice == 5) {
            accumulate_ages(trip);
        } else if (choice == 6) {
            clear_goats(trip);
        } else if (choice == 7) {
            find_goat(trip);
        } else if (choice == 8) {
            age_goats(trip);
        } else if (choice == 9) {
            sort_goats(trip);
        }
        cout << endl; // Just to fix formatting stuff
    }

    return 0;
}

// main_menu() displays the menu, obtains, validates and returns the user's choice
// parameters: none
// returns: int - user's validated choice
int main_menu() {
    cout << "*** GOAT MANAGER 3003 ***" << endl;
    cout << " [1] Add a goat" << endl;
    cout << " [2] Delete a goat" << endl;
    cout << " [3] List goats" << endl;
    cout << " [4] Quit" << endl;
    cout << " [5] Accumulate Ages" << endl;
    cout << " [6] Clear Goats" << endl;
    cout << " [7] Find a Goat" << endl;
    cout << " [8] Age Goats" << endl;
    cout << " [9] Sort Goats" << endl;
    cout << "[10] Change Age" << endl;
    cout << "[11] Re-roll Color" << endl;
    cout << "[12] Has Oldest Goat" << endl;
    cout << "Choice --> ";


    int choice;
    cin >> choice;

    while (choice < 1 || choice > 12) {
        cout << "Invalid choice, try again --> ";
        cin >> choice;
    }

    return choice;
}

// add_goat() creates a new goat and pushes it to the back of the trip list
// parameters: list<Goat> &trip - list to append to
// returns: void
void add_goat(list<Goat> &trip, string names[], string colors[]) {
    string name = names[rand() % SZ_NAMES]; // Select random name and color
    string color = colors[rand() % SZ_COLORS];
    int age = rand() % (MAX_AGE + 1); // Random age between 0 and MAX_AGE inclusive
    // As modulo MAX_AGE would only give you 0 to MAX_AGE - 1

    trip.push_back(Goat(name, age, color));
}

// select_goat() displays the trip, prompts and validates user for a goat choice
// parameters: list<Goat> trip - list to choose from
// returns: int - index of the chosen goat
int select_goat(const list<Goat>& trip) {
    if (trip.empty()) { // Guard Clause
        cout << "List is empty" << endl;
        return -1; // -1 is just a dummy number to indicate an error
        // But theoretically it'll never be accessed since the calling function
        // delete_goat() already has its own guard clause
    }

    display_trip(trip); // Reuse display trip for efficiency
    cout << "Choice --> ";

    int choice;
    cin >> choice;

    while (choice < 1 || choice > trip.size()) { // User input is 1-based
        cout << "Invalid choice, try again --> ";
        cin >> choice;
    }

    return choice - 1; // Adjusted to 0 based index to work with lists
}

// delete_goat() removes goat from index inputted by user
// parameters: list<Goat> &trip - list to delete from
// returns: void
void delete_goat(list<Goat> &trip) {
    if (trip.empty()) {
        cout << "List is empty" << endl;
        return;
    }

    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index);
    trip.erase(it);
}

// display_trip() displays the goats on the trip list
// parameters: list<Goat> trip - list to display
// returns: void
void display_trip(const list<Goat>& trip) {
    if (trip.empty()) {
        cout << "List is empty" << endl;
        return;
    }

    int i = 1; // Starting with 1 for human counting system
    for (Goat goat : trip) {
        cout << "[" << i << "] ";
        cout << goat.get_name();
        cout << " (" << goat.get_age() << ", ";
        cout << goat.get_color() << ")" << endl;
        i++;
    }
}

void accumulate_ages(const list<Goat>& trip) {
    int total_age = accumulate(trip.begin(), trip.end(), 0);
    cout << "Total age: " << total_age;
}

void clear_goats(list<Goat>& trip) {
    trip.clear();
    cout << "Trip cleared" << endl;
}

void find_goat(const list<Goat>& trip) {
    string name;
    cout << "Name of Goat: ";
    cin >> name;

    auto it = find(trip.begin(), trip.end(), Goat(name));
    if (it != trip.end()) {
        cout << "Goat found: ";
        cout << it->get_name();
        cout << " (" << it->get_age() << ", ";
        cout << it->get_color() << ")" << endl;
    } else {
        cout << "Goat not found";
    }
}

void age_goats(list<Goat>& trip) {
    for_each(trip.begin(), trip.end(), [](Goat& n){n = n + 2;});
    cout << "Aged all goats by 2 years" << endl;
}

void sort_goats(list<Goat>& trip) {
    trip.sort();
}