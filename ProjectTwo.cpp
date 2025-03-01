#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

// Course structure to hold course data
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// Function to load course data from file
void loadCourseData(const string& filename, map<string, Course>& courses) {
    ifstream file(filename);
    if (!file) {
        cout << "Error: Unable to open file " << filename << endl;
        return;
    }
    
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string courseNumber, courseTitle, prereq;
        getline(ss, courseNumber, ',');
        getline(ss, courseTitle, ',');
        
        Course course;
        course.courseNumber = courseNumber;
        course.courseTitle = courseTitle;
        
        while (getline(ss, prereq, ',')) {
            course.prerequisites.push_back(prereq);
        }
        
        courses[courseNumber] = course;
    }
    file.close();
    cout << "Course data successfully loaded!" << endl;
}

// Function to print courses in alphanumeric order
void printCourseList(const map<string, Course>& courses) {
    cout << "\nHere is a sample schedule:" << endl;
    for (const auto& pair : courses) {
        cout << pair.second.courseNumber << ", " << pair.second.courseTitle << endl;
    }
}

// Function to print specific course details
void printCourseInfo(const map<string, Course>& courses) {
    string courseNumber;
    cout << "\nWhat course do you want to know about? ";
    cin >> courseNumber;
    
    transform(courseNumber.begin(), courseNumber.end(), courseNumber.begin(), ::toupper);
    
    if (courses.find(courseNumber) != courses.end()) {
        const Course& course = courses.at(courseNumber);
        cout << course.courseNumber << ", " << course.courseTitle << endl;
        cout << "Prerequisites: ";
        if (course.prerequisites.empty()) {
            cout << "None";
        } else {
            for (const string& prereq : course.prerequisites) {
                cout << prereq << " ";
            }
        }
        cout << endl;
    } else {
        cout << "Course not found." << endl;
    }
}

// Main function with menu options
int main() {
    // Load course data from file and store in a map of courses
    map<string, Course> courses; 

    int choice;
    
    string filename;
    
    cout << "Welcome to the course planner." << endl;
    
    while (true) {
        cout << "\n1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << "What would you like to do? ";
        cin >> choice;
        
        if (choice == 1) {

            cout << "Enter the file name: ";
            cin >> filename;
            loadCourseData(filename, courses);
        } else if (choice == 2) {
            if (courses.empty()) {
                cout << "No course data available. Load data first." << endl;
            } else {
                printCourseList(courses);
            }
        } else if (choice == 3) {
            if (courses.empty()) {
                cout << "No course data available. Load data first." << endl;
            } else {
                printCourseInfo(courses);
            }
        } else if (choice == 9) {
            cout << "Thank you for using the course planner!" << endl;
            break;
        } else {
            cout << choice << " is not a valid option." << endl;
        }
    }
    return 0;
}
