#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>

class Person {
private:
    int returned_bottles_cheaper;   // Represents the number of cheaper returned bottles
    int returned_bottles_expensive;  // Represents the number of expensive returned bottles
    int person_id;          // Unique identifier
    std::string name;       // Name of the person
    int bank_account_number; // Bank account number
    int cashout_history;

    // Generates a unique ID by checking existing persons
    int generateUniqueId(const std::vector<Person>& person_list) {
        int id;
        bool unique;

        do {
            id = rand() % 9000 + 1000; // Generates a random number between 1000 and 9999
            unique = false;

            // Check if the generated ID already exists
            for (Person person : person_list) {
                if (person.getPersonId() == id) {
                    unique = false;
                    break;
                }
            }
        } while (unique);

        return id;
    }

public:
    // Constructor
    Person(const std::string& name, int bank_accaunt_number, std::vector<Person>& person_list) {
        this->name = name;                  // Set the name
        returned_bottles_cheaper = 0;              // Default value
        returned_bottles_expensive = 0;             // Default value
        person_id = generateUniqueId(person_list); // Generate unique ID
        this->bank_account_number = bank_accaunt_number;          // Set the bank account number
        cashout_history = 0;

        // Add the new person to the list
        person_list.push_back(*this);
    }

    // Getter for returned_bottles
    int getReturnedBottlesCheaper() const {
        return returned_bottles_cheaper;
    }

    // Setter for returned_bottles
    void setReturnedBottles(int returned_bottles_cheaper) {
        this->returned_bottles_cheaper = returned_bottles_cheaper;
    }

    int getReturnedBottlesExpensive() const {
        return returned_bottles_expensive;
    }

    // Setter for returned_bottles
    void setReturnedBottles(int returned_bottles_expensive) {
        this->returned_bottles_expensive = returned_bottles_expensive;
    }

    // Getter for person_id
    int getPersonId() const {
        return person_id;
    }

    // Getter for name
    std::string getName() const {
        return name;
    }

    // Getter for bank_account_number
    int getBankAccountNumber() const {
        return bank_account_number;
    }

    // Setter for bank_account_number
    void setBankAccountNumber(int bank_account_number) {
        this->bank_account_number = bank_account_number;
    }

    int calculateSum(){
        return 50*returned_bottles_cheaper + 100*returned_bottles_expensive;
    }

    void cashOut(){
        int cash = calculateSum();
        void cashOut_send(int bank_account_number, int cash);
        std::cout << "You cashed out " << cash << " Ft." << std::endl;

        returned_bottles_cheaper = 0;
        returned_bottles_expensive = 0;
        cashout_history += cash;
    }

    int cashoutHistory(){
        return cashout_history;
    }

};


void addBottle(int to_add_Id, int cheaper, int expensive, std::vector<Person>& person_list) {
    // Find the user by ID
    for (Person& person : person_list) {
        if (person.getPersonId() == to_add_Id) {
            // If it found the Person object, it can add the water bottles
            person.setReturnedBottles(cheaper); // assuming this sets cheaper bottles
            person.setReturnedBottles(expensive); // assuming this sets expensive bottles
            std::cout << "Bottles added successfully addet to "<< person.getName() <<"-s accaunt!" << std::endl;
            std::cout << "It worth "<<person.calculateSum()<<" Ft." << std::endl;
            return;
        }
    }
    // Ha nem találta meg a Person objektumot, akkor kiírhat egy hibaüzenetet
    std::cout << "Error: User not found with ID " << to_add_Id << std::endl;
}



void registerUser(std::vector<Person>& person_list){
    std::cout << "Full name:";
    std::string name;
    std::cin >> name;

    std::cout << "Bank account number:";
    int bank_account_number;
    std::cin >> bank_account_number;

    Person person(name, bank_account_number, person_list);
    std::cout << "User registered successfully!" << std::endl;
}

void printAllUsers(std::vector<Person>& person_list){
    for (const Person& person : person_list) {
        std::cout << "Name: " << person.getName() << ", Bank account number: " << person.getBankAccountNumber() <<", cashout history: "<< person.cashoutHistory() << std::endl;
    }
}

void cashOut(int to_send_Id, std::vector<Person>& person_list){
    for (Person& person : person_list) {
        if (person.getPersonId() == to_send_Id) {
            person.cashOut();
            return;
        }
    }
    std::cout << "Error: User not found with ID " << to_send_Id << std::endl;
}

void toplist(std::vector<Person>& person_list) {
    std::vector<Person> sorted = person_list;
    std::sort(sorted.begin(), sorted.end(),[](const Person& a, const Person& b) {return a.getCashOutHistory() > b.getCashOutHistory();});

    int rank = 1;
    for (const auto& person : sorted) {
        std::cout << "Rank " << (rank) << ": " << person.getName()<< " - Cash out history: " << person.getCashOutHistory() << std::endl;
        rank++;
        if (&person - &sorted[0] + 1 == 5) break;
    }
}

int main() {
    // Initialize random seed
    std::srand(std::time(0));

    // To store all persons
    std::vector<Person> person_list;


    // Create persons and add them to the list



    // Display information about each person
    for (const Person& person : person_list) {
        std::cout << "Name: " << person.getName() << ", ID: " << person.getPersonId() << ", Returned Bottles: ";
    }

    return 0;
}
