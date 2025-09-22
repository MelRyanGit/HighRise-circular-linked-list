#include <iostream>

using namespace std;

template <typename T>
class Node {
   public:
    T resident;
    int floor;
    string job;

    Node<T>* pNext;

    Node(T resident, int floor, string job, Node<T>* current) {
        this->resident = resident;
        this->floor = floor;
        this->job = job;
        this->pNext = current;
    }
    ~Node() {
        cout << "\nDEATH NOTICE: " << resident << " from Floor " << floor
             << " (" << job << ") has been eaten\n";
    }
};

// I had AI help with the wording for dramatic effect
template <typename T>
class HighRise {
   public:
    int size = 0;
    Node<T>* current = nullptr;

    // pause for dramatic effect
    void pause() {
        cout << "\n[Press Enter to continue...]\n";
        cin.get();
    }

    void printResidence() {
        pause();
        cout << "\nCurrent survivors in the High-Rise: (" << size << ")\n";

        if (current == nullptr) {
            return;
        }
        Node<T>* tmp = current;
        for (int i = 0; i < size; i++) {
            // cout << tmp->resident << endl;
            cout << "- " << tmp->resident << " | Floor " << tmp->floor
                 << " | Job: " << tmp->job << endl;

            tmp = tmp->pNext;
        }
        cout << endl;
    }

    void addResident(T resident, int floor, string job) {
        if (floor > 0) {
            if (current == nullptr) {
                current = new Node<T>(resident, floor, job, nullptr);
                current->pNext = current;
            } else {
                Node<T>* newNode =
                    new Node<T>(resident, floor, job, current->pNext);
                current->pNext = newNode;
                newNode = current;
            }
            size++;
        } else {
            cerr << "\033[31mFloor Invalid, you are not permitted to "
                    "stay.\033[0m";
            return;
        }
    }

    void welcome() {
        cout << "——————————————————————————————————————————————————\n";
        cout << "🏙️  WELCOME TO THE HIGH-RISE 🏙️\n";
        cout << "——————————————————————————————————————————————————\n";
        cout << "Luxury. Isolation. Hierarchy.\n";
        cout << "The Architect, Mr. Royal, welcomes you.\n";
        cout << "As chaos brews behind closed doors...\n\n";
        cout << "[SYSTEM] Initializing residents...\n";
        exsistingResidents();
        printResidence();
        cout << "But one more dares to enter...\n\n";

        T name;
        int floor;
        string job;
        cout << "What is your name: ";
        cin >> name;
        cout << "Which floor will you occupy? ";
        cin >> floor;
        cout << "And your current occupation? ";
        cin >> job;
        addResident(name, floor, job);
        cout << "\nMay your stay be... enlightening.\n";
    }

    void exsistingResidents() {
        addResident("Robert", 25, "Physiologist");
        addResident("Anthony", 40, "Architect");
        addResident("Richard", 14, "Film Maker");
        addResident("Charlotte", 26, "Toby's Mom");
        addResident("Helen", 14, "Pregnat Mom");
    }

    void killResident(Node<T>* goner) {
        if (!goner || size <= 1) return;
        Node<T>* tmp = goner;
        while (tmp->pNext != goner) {
            tmp = tmp->pNext;
        }
        // I forgot this check, AI helped
        if (goner == current) {
            current = current->pNext;
        }

        tmp->pNext = goner->pNext;
        delete goner;
        goner = nullptr;
        size--;
    }

    void goCrazy(int k) {
        cout << "\nDESCENT INTO MADNESS BEGINS\n";
        cout << "\n🔪 Madness spreads. The walls echo with screams.\n";
        cout << "Residents turn on each other. Blood stains the elevators.\n";

        if (size == 0) {
            cerr << "\033[31mThe building is abandoned...\033[0m";
            return;
        }
        while (size > 1) {
            for (int i = 0; i < k - 1; i++) {
                current = current->pNext;
            }
            Node<T>* goner = current;
            current = current->pNext;
            killResident(goner);

            printResidence();
        }

        cout << "\n——————————————————————————————————————————\n";
        cout << "\n"
             << current->resident << " stands alone on floor " << current->floor
             << ".\n";
        cout << "The cat watches, full and satisfied.\n";
        cout << "The High-Rise is quiet now.\n";
        cout << "——————————————————————————————————————————\n";
        delete current;
        current = nullptr;
    }
};

bool testFullHouse() {
    HighRise<string> test;
    test.welcome();
    test.goCrazy(5);
    return test.size == 0;
}
bool testSingleResident() {
    HighRise<string> test;
    test.addResident("Laing", 25, "Doctor");
    test.goCrazy(2);
    return test.size == 0;
}

bool testEmptyBuilding() {
    HighRise<string> test;
    test.goCrazy(4);
    return test.size == 0;
}
bool testInvalidInput() {
    HighRise<string> test;
    test.addResident("Ghost", -7, "Undefined");
    test.goCrazy(8);
    return test.size == 0;
}
bool testKValue8() {
    HighRise<string> test;
    test.exsistingResidents();
    test.goCrazy(8);
    return test.size == 0;
}
bool testKValue3() {
    HighRise<string> test;
    test.exsistingResidents();
    test.goCrazy(3);
    return test.size == 0;
}

int main() {
    cout << "\n--- Test 1: Full House ---\n";
    cout << (testFullHouse() ? "Passed" : "Failed") << "\n";

    cout << "\n--- Test 2: Single Resident ---\n";
    cout << (testSingleResident() ? "Passed" : "Failed") << "\n";

    cout << "\n--- Test 3: Empty Building ---\n";
    cout << (testEmptyBuilding() ? "Passed" : "Failed") << "\n";

    cout << "\n--- Test 4: Invalid Input ---\n";
    cout << (testInvalidInput() ? "Passed" : "Failed") << "\n";

    cout << "\n--- Test 5: k = 8 ---\n";
    cout << (testKValue8() ? "Passed" : "Failed") << "\n";

    cout << "\n--- Test 6: k = 3 ---\n";
    cout << (testKValue3() ? "Passed" : "Failed") << "\n";
    return 0;
}
