#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct Student {
    std::string name;
    int bioMarks;
    int physicsMarks;
    int chemMarks;
    int totalMarks;
    int rank;
};

const int NUM_BIO_CLASSES = 3;
const int NUM_MATH_CLASSES = 5;
const int STUDENTS_PER_CLASS = 40;

// Function to read marks from the file
void readMarks(std::vector<Student>& students) {
    std::ifstream infile("marks.txt");
    if (!infile) {
        std::cerr << "Error: Unable to open marks.txt file." << std::endl;
        exit(EXIT_FAILURE);
    }

    while (infile >> students.emplace_back().name >> students.back().bioMarks >> students.back().physicsMarks >> students.back().chemMarks);
}

// Function to calculate total marks and rank students
void calculateRanks(std::vector<Student>& students) {
    for (auto& student : students) {
        student.totalMarks = student.bioMarks + student.physicsMarks + student.chemMarks;
    }

    std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.totalMarks > b.totalMarks;
    });

    int rank = 1;
    for (auto& student : students) {
        student.rank = rank++;
    }
}

// Function to print and write ranks to a file
void printAndWriteRanks(const std::vector<Student>& students) {
    std::ofstream outfile("rankings.txt");
    if (!outfile) {
        std::cerr << "Error: Unable to open rankings.txt file." << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Name\t\tTotal Marks\tSchool Rank\tClass Rank" << std::endl;
    outfile << "Name\t\tTotal Marks\tSchool Rank\tClass Rank" << std::endl;

    for (const auto& student : students) {
        std::cout << student.name << "\t\t" << student.totalMarks << "\t\t" << student.rank << "\t\t";

        int classRank = (student.rank - 1) % STUDENTS_PER_CLASS + 1;
        int streamSize = (student.rank <= NUM_BIO_CLASSES * STUDENTS_PER_CLASS) ? NUM_BIO_CLASSES : NUM_MATH_CLASSES;

        std::cout << classRank << " of " << streamSize << std::endl;
        outfile << student.name << "\t\t" << student.totalMarks << "\t\t" << student.rank << "\t\t" << classRank << " of " << streamSize << std::endl;
    }
}

int main() {
    std::vector<Student> students;

    // Read marks from the file
    readMarks(students);

    // Calculate total marks and rank students
    calculateRanks(students);

    // Print and write ranks to a file
    printAndWriteRanks(students);

    return 0;
}
