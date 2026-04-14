// Goat.h

#ifndef GOAT_H
#define GOAT_H
#include <iostream>
using namespace std;

class Goat {
private:
    string name;
    int age;
    string color;
public: 
    Goat()                          { name = ""; age = 0; color = ""; }
    // write three more constructors
    Goat(string n)                  { name = n; age = 0; color = ""; }
    Goat(string n, int a)           { name = n; age = a; color = ""; }
    Goat(string n, int a, string c) { name = n; age = a; color = c; }

    // setters and getters
    void set_name(string n)         { name = n; };
    string get_name() const         { return name; };
    void set_age(int a)             { age = a; };
    int get_age() const             { return age; }
    void set_color(string c)        { color = c; }
    string get_color() const        { return color; }

    // write overloaded < operator for the std::list

    // operator<() compares this to another goat
    // parameters: const Goat &other - the goat to compare to
    // returns: bool - true if this is less than other
    bool operator<(const Goat &other) const {
        // The task never gives any explicit instructions on how to compare goats
        // So I'm following how you did it in the videos, so just the names
        return name < other.name; 
    }

    bool operator==(const Goat &other) const {
        return name == other.name;
    }

    Goat operator+(int num) {
        return Goat(name, age + num, color);
    }

    // Learned this in 200!
    friend int operator+(int sum, const Goat& other) {
        return sum + other.get_age();
    }
};

#endif