#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
using namespace std;

class Person {
protected:
    string name;
    int age;
public:
    void setDetails(string& person_name, int person_age) {
        name = person_name;
        age = person_age;
    }
    void showDetails() {
        cout << "NAME: " << name << endl;
        cout << "AGE: " << age << endl;
    }
    virtual void showData() = 0;
};

class Passenger : public Person {
protected:
    string ph_no;
    string passenger_address;
public:
    void putData(string& address) {
        passenger_address = address;
    }
    void inputPhone() {
        cout << "Enter phone number: ";
        getline(cin, ph_no);
    }
    void showData1() {
        cout << "ADDRESS: " << passenger_address << endl;
        cout << "PHONE NUMBER: " << setfill('*') << setw(10) << ph_no.substr(ph_no.length() - 4) << endl;
    }
};

class Employee : public Person {
protected:
    int id;
    string job;
public:
    Employee(int a = 24682, string b = "worker") {
        id = a;
        job = b;
    }
    void showData() override {
        cout << "ID: " << id << ", Job: " << job << endl;
    }
};

class TicketBooking : public Passenger {
public:
    int pnr;
    int fare;
    string date;
    int dept;
    string city;
    int seat;
    string coachType;

    void setJourneyDate(string& journey_date) {
        date = journey_date;
    }

    void travel() {
        cout << "Departure from CITY G\n";
        cout << "Available destinations:\n";
        cout << "1. CITY A: (150 RS)\n";
        cout << "2. CITY B: (200 RS)\n";
        cout << "3. CITY C: (250 RS)\n";
        cout << "4. CITY D: (300 RS)\n";

        bool validInput = false;
        while (!validInput) {
            cout << "Enter a number between 1 and 4: ";
            try {
                cin >> dept;
                if (dept < 0 || dept > 4) {
                    throw (dept);
                }
                validInput = true;
            }
            catch (int) {
                cout << "Invalid destination! Please enter a number between 1 and 4." << endl;
            }
        }

        switch (dept) {
        case 1: fare = 150; city = "CITY A"; break;
        case 2: fare = 200; city = "CITY B"; break;
        case 3: fare = 250; city = "CITY C"; break;
        case 4: fare = 300; city = "CITY D"; break;
        }
        cout << "Fare to " << city << " is RS " << fare << endl;
        chooseCoach();
    }

    void chooseCoach() {
        cout << "THE AVAILABLE COACHES ARE:\n";
        cout << "1. GENERAL: (RS 100)\n";
        cout << "2. SLEEPER: (RS 700)\n";
        cout << "3. 3AC: (RS 2500)\n";
        cout << "4. 2AC: (RS 3000)\n";
        cout << "5. 1AC: (RS 7000)\n";
        cout << "Enter the number of coach: ";
        cin >> seat;

        while (seat < 1 || seat > 5) {
            cout << "Invalid coach selection! Please enter a number between 1 and 5: ";
            cin >> seat;
        }

        switch (seat) {
        case 1: fare += 100; coachType = "GENERAL"; break;
        case 2: fare += 700; coachType = "SLEEPER"; break;
        case 3: fare += 2500; coachType = "3AC"; break;
        case 4: fare += 3000; coachType = "2AC"; break;
        case 5: fare += 7000; coachType = "1AC"; break;
        }
    }

    void showData() {
        //cout << "PNR: " << pnr << endl;
        cout << "Date of journey: " << date << endl;
        cout << "Destination: " << city << endl;
        cout << "Fare: " << fare << endl;
        cout << "Coach: " << coachType << endl;
        cout << "TICKET IS BOOKED" << endl;
    }

    friend class TicketCancelling;
};

class TicketCancelling {
public:
    void showData(TicketBooking& b) {
        cout << "Cancelling ticket of PNR: " << b.pnr << endl;
        cout << "TICKET IS SUCCESSFULLY CANCELLED" << endl;
    }
};

class RailMadad : public TicketBooking, public Employee {
public:
    void reportIssue() {
        int pnr_dup;
        string issue;
        cout << "Describe the issue: " << endl;
        cin >> issue;
        cout << "Enter PNR: " << endl;
        cin >> pnr_dup;
        cout << "The employee has informed" << endl << "id:-" << id << ", job:-" << job << endl;
    }
};

int main() {
    int choice;
    int n;

    cout << "\nWelcome to IRCTC!" << endl;
    cout << "How many passengers? ";
    cin >> n;

    TicketBooking* tickets = new TicketBooking[n];
    TicketCancelling cancelling;
    Employee emp1;

    for (int i = 0; i < n; i++) {
        cout << "\nBooking ticket for passenger " << i + 1 << endl;
        string name;
        int age;
        string address, date;

        cout << "Enter name: ";
        cin >> name;
        cout << "Enter age: ";
        cin >> age;
        cin.ignore();
        cout << "Enter address: ";
        getline(cin, address);
        cout << "Enter date of journey (YYYY-MM-DD): ";
        getline(cin, date);

        tickets[i].setDetails(name, age);
        tickets[i].setJourneyDate(date);
        tickets[i].putData(address);
        tickets[i].inputPhone();
        tickets[i].travel();

        int pnr = (rand() % 300000 + 100000000) * 100000000;
        cout << "pnr: " << pnr << endl;

        tickets[i].showData1();
        tickets[i].showData();
    }

    do {
        cout << "\nWelcome to IRCTC!" << endl;
        cout << "1. Cancel Ticket" << endl;
        cout << "2. Report an Issue" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int pnr_to_cancel;
            cout << "Enter PNR to cancel: ";
            cin >> pnr_to_cancel;
            bool found = false;

            for (int i = 0; i < n; i++) {
                if (tickets[i].pnr == pnr_to_cancel) {
                    cancelling.showData(tickets[i]);
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Ticket with PNR " << pnr_to_cancel << " not found." << endl;
            }
            break;
        }
        case 2: {
            RailMadad employee;
            employee.reportIssue();
            break;
        }
        case 3:
            cout << "Thank you for using IRCTC!" << endl;

			break;
		default:
			cout << "Invalid choice! Please try again." << endl;
		}
	} while (choice != 3);

	return 0;
}