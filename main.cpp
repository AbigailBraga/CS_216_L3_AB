//ABIGAIL BRAGA
//Lab #3

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cctype>
#include <sstream>

using namespace std;

const string CREATURE_FILE = "creatures.txt";
const int MAX_CREATURES = 100;

enum MainMenuOption {
    PRINT_ORIGINAL = 1,
    SORT_MENU,
    SEARCH_MENU,
    QUIT
};

enum SortOption {
    SORT_NAME = 1,
    SORT_TYPE,
    SORT_HEALTH,
    SORT_STRENGTH,
    BACK_TO_MAIN
};

class Creature {
public:
    string name;
    string type;
    int health;
    int strength;

    string toLower(const string& str) const {
        string result = str;
        for (char& c : result) {
            c = tolower(c);
        }
        return result;
    }

    string toString() const {
        stringstream ss;
        ss << left << setw(15) << name << left << setw(15) << type << right << setw(5) << health << right << setw(5) << strength;
        return ss.str();
    }
};

class Army {
public:
    Creature creatures[MAX_CREATURES];
    int numCreatures = 0;

    void loadCreatures() {
        ifstream file(CREATURE_FILE);
        if (!file.is_open()) {
            cerr << "Error opening creature file." << endl;
            return;
        }

        while (file >> creatures[numCreatures].name >> creatures[numCreatures].type >> creatures[numCreatures].health >> creatures[numCreatures].strength && numCreatures < MAX_CREATURES) {
            numCreatures++;
        }
        file.close();
    }

    void printCreatures() const {
        cout << "\nCreatures:\n";
        cout << left << setw(15) << "Name" << left << setw(15) << "Type" << right << setw(5) << "Health" << right << setw(5) << "Strength" << endl;
        for (int i = 0; i < numCreatures; i++) {
            cout << creatures[i].toString() << endl;
        }
    }

    void sortCreatures(SortOption sortOption) {
        Creature* pointers[numCreatures];
        for (int i = 0; i < numCreatures; i++) {
            pointers[i] = &creatures[i];
        }

        for (int i = 0; i < numCreatures - 1; i++) {
            for (int j = 0; j < numCreatures - i - 1; j++) {
                bool swapNeeded = false;
                switch (sortOption) {
                    case SORT_NAME:
                        swapNeeded = pointers[j]->toLower(pointers[j]->name) > pointers[j + 1]->toLower(pointers[j + 1]->name);
                        break;
                    case SORT_TYPE:
                        swapNeeded = pointers[j]->toLower(pointers[j]->type) > pointers[j + 1]->toLower(pointers[j + 1]->type);
                        break;
                    case SORT_HEALTH:
                        swapNeeded = pointers[j]->health < pointers[j + 1]->health;
                        break;
                    case SORT_STRENGTH:
                        swapNeeded = pointers[j]->strength < pointers[j + 1]->strength;
                        break;
                }
                if (swapNeeded) {
                    Creature* temp = pointers[j];
                    pointers[j] = pointers[j + 1];
                    pointers[j + 1] = temp;
                }
            }
        }

        for(int i = 0; i < numCreatures; i++){
            creatures[i] = *pointers[i];
        }
    }

    void searchCreatures(const string& query) const {
        string lowerQuery = "";
        for (char c : query){
            lowerQuery += tolower(c);
        }
        bool found = false;
        cout << "\nSearch Results:\n";
        cout << left << setw(15) << "Name" << left << setw(15) << "Type" << right << setw(5) << "Health" << right << setw(5) << "Strength" << endl;
        for (int i = 0; i < numCreatures; i++) {
            string lowerName = creatures[i].toLower(creatures[i].name);
            string lowerType = creatures[i].toLower(creatures[i].type);
            if (lowerName.find(lowerQuery) != string::npos || lowerType.find(lowerQuery) != string::npos) {
                cout << creatures[i].toString() << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No matching records found." << endl;
        }
    }
};

int main() {
    Army army;
    army.loadCreatures();

    int choice;
    do {
        cout << "\nMain Menu:\n";
        cout << "1. Print items in original order\n";
        cout << "2. Sort Menu\n";
        cout << "3. Search Menu\n";
        cout << "4. Quit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (static_cast<MainMenuOption>(choice)) {
            case PRINT_ORIGINAL:
                army.printCreatures();
            case SORT_MENU: {
                int sortChoice;
                do {
                    cout << "\nSort Menu:\n";
                    cout << "1. Sort by Name\n";
                    cout << "2. Sort by Type\n";
                    cout << "3. Sort by Health\n";
                    cout << "4. Sort by Strength\n";
                    cout << "5. Back to Main Menu\n";
                    cout << "Enter your choice: ";
                    cin >> sortChoice;

                    switch (static_cast<SortOption>(sortChoice)) {
                        case SORT_NAME:
                        case SORT_TYPE:
                        case SORT_HEALTH:
                        case SORT_STRENGTH:
                            army.sortCreatures(static_cast<SortOption>(sortChoice));
                            army.printCreatures();
                        case BACK_TO_MAIN:
                            cout << "Going back to main menu.\n";
                        default:
                            cout << "Invalid choice. Try again.\n";
                    }
                } while (sortChoice != BACK_TO_MAIN);
            }
            case SEARCH_MENU: {
                string query;
                cout << "Enter search query: ";
                cin.ignore();
                getline(cin, query);
                army.searchCreatures(query);
            }
            case QUIT:
                cout << "Exiting...\n";
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != QUIT);

    return 0;
}

/*Main Menu:
1. Print items in original order
2. Sort Menu
3. Search Menu
4. Quit
Enter your choice: 1

Creatures:
Name           Type           HealthStrength

Sort Menu:
1. Sort by Name
2. Sort by Type
3. Sort by Health
4. Sort by Strength
5. Back to Main Menu
Enter your choice: 5
Going back to main menu.
Invalid choice. Try again.
Enter search query: 1

Search Results:
Name           Type           HealthStrength
No matching records found.
Exiting...
Invalid choice.

Main Menu:
1. Print items in original order
2. Sort Menu
3. Search Menu
4. Quit
Enter your choice: 4
Exiting...
Invalid choice.


...Program finished with exit code 0
Press ENTER to exit console.*/