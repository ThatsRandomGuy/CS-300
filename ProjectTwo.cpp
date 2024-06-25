#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

//Creating class to store course information
class Course {
public:
    std::string courseNumber;
    std::string courseTitle;
    std::string prerequisites;

    Course(const std::string& number, const std::string& title, const std::string& prereqs)
        : courseNumber(number), courseTitle(title), prerequisites(prereqs) {}
};

//Creating node class for the binary search tree
class CourseNode {
public:
    Course course;
    CourseNode* left;
    CourseNode* right;

    CourseNode(const Course& course) : course(course), left(nullptr), right(nullptr) {}
};

//Creating binary search tree class
class CourseTree {
private:
    CourseNode* root;

    //Creating helper function to insert a course into the tree
    void insertNode(CourseNode*& node, const Course& course) {
        if (node == nullptr) {
            node = new CourseNode(course);
        } else if (course.courseNumber < node->course.courseNumber) {
            insertNode(node->left, course);
        } else {
            insertNode(node->right, course);
        }
    }

    //Creating helper function to perform in-order traversal
    void printInOrder(CourseNode* node) const {
        if (node != nullptr) {
            printInOrder(node->left);
            std::cout << node->course.courseNumber << ", " << node->course.courseTitle << std::endl;
            printInOrder(node->right);
        }
    }

    //Creating helper function to search for a course in the tree
    CourseNode* searchNode(CourseNode* node, const std::string& courseNumber) const {
        if (node == nullptr || node->course.courseNumber == courseNumber) {
            return node;
        } else if (courseNumber < node->course.courseNumber) {
            return searchNode(node->left, courseNumber);
        } else {
            return searchNode(node->right, courseNumber);
        }
    }

public:
    CourseTree() : root(nullptr) {}

    //Creating function to insert a course into the tree
    void insert(const Course& course) {
        insertNode(root, course);
    }

    //Creating function to perform in-order traversal of the tree
    void printAllCourses() const {
        printInOrder(root);
    }

    //Creating function to search for a course in the tree
    CourseNode* search(const std::string& courseNumber) const {
        return searchNode(root, courseNumber);
    }
};

//Creating global binary search tree for courses
CourseTree courseTree;

//Creating function to load courses from a file
bool loadCourses(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    std::string line;
    while (getline(file, line)) {
        std::istringstream ss(line);
        std::string courseNumber, courseTitle, prerequisites;
        getline(ss, courseNumber, ',');
        getline(ss, courseTitle, ',');
        getline(ss, prerequisites);

        Course course(courseNumber, courseTitle, prerequisites);
        courseTree.insert(course);
    }

    std::cout << "Courses loaded successfully!" << std::endl;
    file.close();
    return true;
}

//Creating function to print all courses in alphanumeric order
void printCourses() {
    courseTree.printAllCourses();
}

//Creating function to print detailed information about a specific course
void printCourseInfo(const std::string& courseNumber) {
    CourseNode* node = courseTree.search(courseNumber);
    if (node != nullptr) {
        std::cout << "Course: " << node->course.courseNumber << ", " << node->course.courseTitle << std::endl;
        if (!node->course.prerequisites.empty()) {
            std::cout << "Prerequisites: " << node->course.prerequisites << std::endl;
        } else {
            std::cout << "No prerequisites" << std::endl;
        }
    } else {
        std::cerr << "Course not found: " << courseNumber << std::endl;
    }
}

//Creating function to display the menu
void displayMenu() {
    std::cout << "Menu:" << std::endl;
    std::cout << "1. Load Courses" << std::endl;
    std::cout << "2. Print All Courses" << std::endl;
    std::cout << "3. Print Course Information" << std::endl;
    std::cout << "9. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

//Creating main function
int main() {
    int choice;
    std::string filename, courseNumber;

    while (true) {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1:
                while (true) {
                    std::cout << "Enter filename (or type 'exit' to go back to menu): ";
                    getline(std::cin, filename);
                    if (filename == "exit") {
                        break;
                    }
                    if (loadCourses(filename)) {
                        break;
                    }
                }
                break;
            case 2:
                printCourses();
                break;
            case 3:
                std::cout << "Enter course number: ";
                getline(std::cin, courseNumber);
                printCourseInfo(courseNumber);
                break;
            case 9:
                std::cout << "Exiting program..." << std::endl;
                return 0;
            default:
                std::cerr << "Invalid choice. Please try again." << std::endl;
                break;
        }
    }

    return 0;
}