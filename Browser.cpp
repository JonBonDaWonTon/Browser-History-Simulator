// Name: Browser.cpp
// Project: CMSC 202 Project 5, Fall 2024
// Author: Jonathan Dao
// Date: 12/1/24
// Description: Simulates a Browser History allowing you to go back in history and forwards from sites

// Note: I used the descriptions from header file

#include "Browser.h"

// Overloaded Constructor
Browser::Browser(string filename) : m_backStack(), m_forwardStack(), m_currentPage(nullptr), m_fileName(filename) {}

// Destructor
Browser::~Browser() {
    // Cleans up m_currentPage
    if (m_currentPage) {
        delete m_currentPage;
        m_currentPage = nullptr;
    }

    // Cleans up m_backStack
    while (!m_backStack.IsEmpty()) {
        delete m_backStack.Pop();
    }

    // Cleans up m_forwardStack
    while (!m_forwardStack.IsEmpty()) {
        delete m_forwardStack.Pop();
    }
}

// StartBrowser
void Browser::StartBrowser() {
    // Loads in the browsing history from the file
    LoadFile(); 

    // Displays the initial current page
    if (m_currentPage) {
        cout << "Welcome to the Browser History Simulator\n" << endl;
        cout << "Current Website:" << endl;
        cout << *m_currentPage << endl;
    } else {
        cout << "\nWelcome to the Browser History Simulator\n" << endl;
        cout << "No current page loaded." << endl;
    }

    // Starts the user interaction menu
    Menu(); 
}


// Menu
void Browser::Menu() {
    int choice;
    do {
        // Basic Menu Commands
        cout << "\n--- Browser Menu ---" << endl;
        cout << "1. Display Browser History" << endl;
        cout << "2. Go Back" << endl;
        cout << "3. Go Forward" << endl;
        cout << "4. Visit Site" << endl;
        cout << "5. Quit" << endl;

        // Gets users input for which command to be used
        cin >> choice;
        
        // Switch statement for that corspond to commands based users input
        switch (choice) {
            case 1:
                Display();
                break;
            case 2:
                Back(1); // Go back one site (hard coded 1 page as described in email)
                break;
            case 3:
                Forward(1); // Go forward one site (hard coded 1 page as described in email)
                break;
            case 4:
                NewVisit();
                break;
            case 5:
                cout << "Exiting the browser. Thank you!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);
}

// Visit Function
void Browser::Visit(const string& url, int timestamp) {

    NavigationEntry* newEntry = new NavigationEntry(url, timestamp); // Creates new object

    if (m_currentPage) {
        m_backStack.Push(m_currentPage); // Pushes the current page to the back stack
    }
    m_currentPage = newEntry; // Updates current page
}

// NewVisit Function
void Browser::NewVisit() {
    // Getting the new URL
    string url;
    cout << "Enter the URL of the site: ";
    cin.ignore();
    getline(cin, url);

    // Creating the current timestamp for the new site
    auto now = chrono::system_clock::now();
    time_t nowAsTimeT = chrono::system_clock::to_time_t(now);
    int64_t timestamp = static_cast<int64_t>(nowAsTimeT);

    Visit(url, timestamp); // Calls Visit with the user-entered URL and timestamp (To create the new object)

    cout << "Current Website:" << endl;
    cout << *m_currentPage << endl;

}

// Display Fucntion
void Browser::Display() {

    // Displaying the Back Stack with header
    cout << "\n** Back Stack **" << endl;
    if (m_backStack.IsEmpty()) {
        cout << "Empty" << endl;
    } else {
        Stack<NavigationEntry*> tempStack;
        int count = 1;

        // Reverse the back stack for correct order
        while (!m_backStack.IsEmpty()) {
            NavigationEntry* entry = m_backStack.Pop();
            tempStack.Push(entry);
            cout << count++ << ". " << *entry << endl;
        }

        // Restore the back stack
        while (!tempStack.IsEmpty()) {
            m_backStack.Push(tempStack.Pop());
        }
    }

    // Displaying the Forword Stack with header
    cout << "\n** Forward Stack **" << endl;
    if (m_forwardStack.IsEmpty()) {
        cout << "Empty" << endl;
    } else {
        Stack<NavigationEntry*> tempStack;
        int count = 1;

        // Reverses the forward stack for correct order
        while (!m_forwardStack.IsEmpty()) {
            NavigationEntry* entry = m_forwardStack.Pop();
            tempStack.Push(entry);
        }

        // Displays the reversed stack
        while (!tempStack.IsEmpty()) {
            NavigationEntry* entry = tempStack.Pop();
            cout << count++ << ". " << *entry << endl;
            m_forwardStack.Push(entry);
        }
    }

    cout << "\nCurrent Website:" << endl;
    if (m_currentPage) {
        cout << *m_currentPage << endl;
    } else {
        cout << "No current page." << endl;
    }
}

// Back Function
NavigationEntry Browser::Back(int steps) {
    if (m_backStack.IsEmpty()) {
        cout << "Back stack is empty. Cannot go back." << endl;
        return NavigationEntry();
    }

    for (int i = 0; i < steps && !m_backStack.IsEmpty(); i++) {
        // Pushes the current page onto the forward stack
        m_forwardStack.Push(m_currentPage);

        // Moves the top of the back stack to the current page
        m_currentPage = m_backStack.Pop();
    }

    // Displays the new current page
    cout << "\nCurrent Website:" << endl;
    if (m_currentPage) {
        cout << *m_currentPage << endl;
    } else {
        cout << "No current page." << endl;
    }

    return *m_currentPage;
}

// Forward Function
NavigationEntry Browser::Forward(int steps) {
    if (m_forwardStack.IsEmpty()) {
        cout << "Forward stack is empty. Cannot go forward." << endl;
        return NavigationEntry();
    }

    for (int i = 0; i < steps && !m_forwardStack.IsEmpty(); i++) {
        m_backStack.Push(m_currentPage); // Pushes current page to back stack
        m_currentPage = m_forwardStack.Pop(); // Pops from forward stack to current page
    }

    // Displays the new current page
    cout << "\nCurrent Website:" << endl;
    if (m_currentPage) {
        cout << *m_currentPage << endl;
    }

    return *m_currentPage;
}

// GetCurrentPage Function
NavigationEntry Browser::GetCurrentPage() const {
    
    return *m_currentPage;
}

// LoadFile Function
void Browser::LoadFile() {
    ifstream inputFile(m_fileName); // Will open and read the file

    // Will print an error message if file cannot be opened (if opened it continues)
    if (!inputFile.is_open()) {
        cout << "Error: Unable to open browsing history file." << endl;
        return;
    }

    string url, timestampStr;

    // Will read and set info from the file using getline (using DELIMITER as a delimiter)
    while (getline(inputFile, url, DELIMITER) && getline(inputFile, timestampStr, '\n')) {
        int timestamp = stoi(timestampStr); // Convert timestamp string to integer

        // Will create a new NavigationEntry object and push it to the back stack
        NavigationEntry* newEntry = new NavigationEntry(url, timestamp);
        m_backStack.Push(newEntry);
    }

    // Setting the current page to the most recent entry (if available)
    if (!m_backStack.IsEmpty()) {
        m_currentPage = m_backStack.Pop();
    } else {
        cout << "No valid entries found in the file." << endl;
        m_currentPage = nullptr;
    }

    inputFile.close(); // Closes the file after loading all entries
}

