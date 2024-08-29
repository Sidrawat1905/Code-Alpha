#include <iostream>
#include <vector>
#include <string>
#include <limits>

class Course {
public:
    Course(const std::string& name, int credits, double gradePoint)
        : name(name), credits(credits), gradePoint(gradePoint) {}

    std::string name;
    int credits;
    double gradePoint;
};

class CGPACalculator {
private:
    std::vector<Course> courses;

public:
    void addCourse(const std::string& name, int credits, double gradePoint) {
        courses.emplace_back(name, credits, gradePoint);
    }

    double calculateCGPA() const {
        double totalPoints = 0.0;
        int totalCredits = 0;
        for (const auto& course : courses) {
            totalPoints += course.gradePoint * course.credits;
            totalCredits += course.credits;
        }
        return (totalCredits == 0) ? 0.0 : totalPoints / totalCredits;
    }

    void displayResults() const {
        std::cout << "CGPA Calculation Results:\n";
        std::cout << "-------------------------\n";
        std::cout << "Course Details:\n";
        for (const auto& course : courses) {
            std::cout << "Course: " << course.name << ", Credits: " << course.credits
                      << ", Grade Point: " << course.gradePoint << '\n';
        }
        std::cout << "-------------------------\n";
        std::cout << "Your CGPA is: " << calculateCGPA() << '\n';
    }
};

bool getPositiveDouble(const std::string& prompt, double& value) {
    std::cout << prompt;
    while (!(std::cin >> value) || value < 0) {
        std::cin.clear(); // Clear error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        std::cout << "Invalid input. Please enter a positive number: ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard remaining input
    return true;
}

bool getPositiveInt(const std::string& prompt, int& value) {
    std::cout << prompt;
    while (!(std::cin >> value) || value < 0) {
        std::cin.clear(); // Clear error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        std::cout << "Invalid input. Please enter a positive integer: ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard remaining input
    return true;
}

int main() {
    CGPACalculator calculator;
    int numCourses;

    std::cout << "Enter number of courses: ";
    getPositiveInt("", numCourses);

    for (int i = 0; i < numCourses; ++i) {
        std::string name;
        int credits;
        double gradePoint;

        std::cout << "Enter course name: ";
        std::getline(std::cin, name);

        getPositiveInt("Enter number of credits: ", credits);
        getPositiveDouble("Enter grade point: ", gradePoint);

        calculator.addCourse(name, credits, gradePoint);
    }

    calculator.displayResults();
    return 0;
}
