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

    // Generates a unique ID by checking existing persons
    int generateUniqueId(const std::vector<Person>& person_list) {
        int id;
        bool unique;

        do {
            id = rand() % 9000 + 1000; // Generates a random number between 1000 and 9999
            unique = true;

            // Check if the generated ID already exists
            for (const Person& person : person_list) {
                if (person.getPersonId() == id) {
                    unique = false;
                    break;
                }
            }
        } while (!unique);

        return id;
    }

public:
    // Constructor
    Person(const std::string& name, int bank_account_number, std::vector<Person>& person_list) {
        this->name = name;                  // Set the name
        returned_bottles_cheaper = 0;              // Default value
        returned_bottles_expensive = 0;             // Default value
        person_id = generateUniqueId(person_list); // Generate unique ID
        this->bank_account_number = bank_account_number;          // Set the bank account number

        // Add the new person to the list
        person_list.push_back(*this);
    }

    // Getter for returned_bottles
    int getReturnedBottlesCheaper() const {
        return returned_bottles_cheaper;
    }

    // Getter for returned_bottles
    int getReturnedBottlesExpensive() const {
        return returned_bottles_expensive;
    }

    // Setter for returned_bottles
    void setReturnedBottlesCheaper(int returned_bottles_cheaper) {
        this->returned_bottles_cheaper = returned_bottles_cheaper;
    }

    void setReturnedBottlesExpensive(int returned_bottles_expensive){
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

    int calculateSum() const {
        return 50 * returned_bottles_cheaper + 100 * returned_bottles_expensive;
    }


    std::string cashoutHistory() const {
        return std::to_string(returned_bottles_cheaper) + " cheaper bottles and " + std::to_string(returned_bottles_expensive) + " expensive bottles";
    }
};

void addBottle(int to_add_Id, int cheaper, int expensive, std::vector<Person>& person_list) {
    // Find the user by ID
    for (Person& person : person_list) {
        if (person.getPersonId() == to_add_Id) {
            // If it found the Person object, it can add the water bottles
            person.setReturnedBottlesCheaper(person.getReturnedBottlesCheaper() + cheaper);
            person.setReturnedBottlesExpensive(person.getReturnedBottlesExpensive() + expensive);
            std::cout << "Bottles added successfully to " << person.getName() << "'s account!" << std::endl;
            std::cout << "It worth " << person.calculateSum() << " Ft." << std::endl;
            return;
        }
    }
    // If it didn't find the Person object, it can print an error message
    std::cout << "Error: User not found with ID " << to_add_Id << std::endl;
}

void registerUser(std::vector<Person>& person_list){
    std::cout << "Full name: ";
    std::string name;
    std::cin >> name;

    std::cout << "(12345678-12345678-12345678) Bank account number: ";
    int bank_account_number;
    std::cin >> bank_account_number;

    Person person(name, bank_account_number, person_list);
    std::cout << "User registered successfully!" << std::endl;
}

void printAllUsers(const std::vector<Person>& person_list){
    for (const Person& person : person_list) {
        std::cout << "Name: " << person.getName() << ", Bank account number: " << person.getBankAccountNumber() << ", cashout history: " << person.cashoutHistory() << std::endl;
    }
}

void toplist(const std::vector<Person>& person_list) {
    std::vector<Person> sorted = person_list;
    std::sort(sorted.begin(), sorted.end(), [](const Person& a, const Person& b) { return a.calculateSum() > b.calculateSum(); });

    int rank = 1;
    for (const auto& person : sorted) {
        std::cout << "Rank " << rank << ": " << person.getName() << " - Cash out history: " << person.calculateSum() << " Ft. - " << std::endl;
        rank++;
        if (rank > 5) break;
    }
}

void use_the_repont(std::vector<Person>& person_list){
    int input_id;
    bool valid_id = false;

    do{
        std::cout << "What is your ID?: " << std::endl;
        std::cin >> input_id;

        for (Person& person : person_list) {
            if (person.getPersonId() == input_id) {
                valid_id = true;
                break;
            }
        }
        if(!valid_id){
            std::cout << "Invalid ID!" << std::endl;
        }
    } while(!valid_id);

    std::cout << "How many cheaper bottles did you return?: " << std::endl;
    int cheaper;
    std::cin >> cheaper;

    std::cout << "How many expensive bottles did you return?: " << std::endl;
    int expensive;
    std::cin >> expensive;

    addBottle(input_id, cheaper, expensive, person_list);

    //sendMoney(int person.getBankAccountNumber(), int cheaper * 50 + expensive * 100);
}

void sendMoney(int from, int to, int amount){

    //send money

    std::cout << "Money sent successfully!" << std::endl;
}

int main() {
    while(true){
        std::cout << "welcome to the Repont!" << std::endl;
        std::cout << "1. Register user" << std::endl;
        std::cout << "2. Use the Repont" << std::endl;
        std::cout << "3. Print all users" << std::endl;
        std::cout << "4. Toplist" << std::endl;
        std::cout << "5. Exit" << std::endl;

        std::vector<Person> person_list;

        int choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                registerUser(person_list);
                break;
            case 2:
                use_the_repont(person_list);
                break;
            case 3:
                printAllUsers(person_list);
                break;
            case 4:
                toplist(person_list);
                break;
            case 5:
                return 0;
            default:
                std::cout << "Invalid choice!" << std::endl;
                break;
        }
    }
}
