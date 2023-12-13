#include <iostream>
#include <string>
using namespace std;

const int MAX_PEOPLE = 1;
class Person {
protected:
    string name;
    int age;
    string gender;
    string address;

public:
    Person(string n, int a, string g, string add){
    	name=n;
    	age=a;
    	gender=g;
    	address=add;
	}
     

    virtual void display() const = 0;

    virtual string getName(){
	return name; }
};

class Patient : public Person {
public:
 
      Patient(string n, int a, string g, string add):Person(n, a, g, add) {}

    void display() const  {
        cout << "Name: " <<  name<< "\nAge: " << age << "\nGender: " << gender << "\nAddress: " << address << "\n\n";
    }
};

class Hospital {
private:
    Person* people[MAX_PEOPLE];
    int numPeople;

public:
    Hospital() : numPeople(0) {}

    void addPerson(Person* person) {
        if (numPeople < MAX_PEOPLE) {
            people[numPeople++] = person;
            cout << "Person added successfully!\n";
        } else {
            cout << "Hospital is at full capacity. Cannot add more people.\n";
        }
    }

    void removePerson(const string& personName) {
        for (int i = 0; i < numPeople; ++i) {
            if (people[i]->getName() == personName) {
                delete people[i];
                
                for (int j = i; j < numPeople - 1; ++j) {
                    people[j] = people[j + 1];
                }
                --numPeople;
                cout << "Person removed successfully!\n";
                return;
            }
        }
        cout << "Person not found!\n";
    }

    void displayPeople() const {
        if (numPeople == 0) {
            cout << "No people in the system.\n";
            return;
        }

        cout << "List of People:\n";
        for (int i = 0; i < numPeople; ++i) {
            people[i]->display();
        }
    }

    ~Hospital() {
        for (int i = 0; i < numPeople; ++i) {
            delete people[i];
        }
    }
};

int main() {
    Hospital hospital;

    while (true) {
        cout << "Hospital Management System\n";
        cout << "1. Add Person\n";
        cout << "2. Remove Person\n";
        cout << "3. Display People\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                string name, gender, address;
                int age;

                cout << "Enter person name: ";
                cin.ignore();  
                getline(cin, name);

                cout << "Enter person age: ";
                cin >> age;

                cout << "Enter person gender: ";
                cin >> gender;

                cout << "Enter person address: ";
                cin.ignore();  
                getline(cin, address);

                Person* newPerson = new Patient(name, age, gender, address);
                hospital.addPerson(newPerson);
                break;
            }
            case 2: {
                string name;
                cout << "Enter person name to remove: ";
                cin.ignore();  
                getline(cin, name);
                hospital.removePerson(name);
                break;
            }
            case 3:
                hospital.displayPeople();
                break;
            case 4:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

