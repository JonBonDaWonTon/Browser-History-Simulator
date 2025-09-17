// This is Navigation.cpp

#include "NavigationEntry.h"
#include <iostream>

// Default Constructor
NavigationEntry::NavigationEntry() : m_url(""), m_timeStamp(0) {}

// Overloaded Constructor
NavigationEntry::NavigationEntry(const string& url, const int& timestamp)
    : m_url(url), m_timeStamp(timestamp) {}

// Getter for URL
string NavigationEntry::GetURL() const {
    return m_url;
}

// Getter for Timestamp
int NavigationEntry::GetTimeStamp() const {
    return m_timeStamp;
}

// Setter for URL
void NavigationEntry::SetURL(const string& url) {
    m_url = url;
}

// Setter for Timestamp
void NavigationEntry::SetTimeStamp(const int& time) {
    m_timeStamp = time;
}

// Checks if URL is empty
bool NavigationEntry::IsEmpty() const {
    return m_url.empty();
}

// Overloaded << operator for printing NavigationEntry details
ostream& operator<<(ostream& os, NavigationEntry& entry) {
    os << "URL:" << entry.m_url
       << " Visited On: " << entry.DisplayTimeStamp(entry.m_timeStamp);
    return os;
}
