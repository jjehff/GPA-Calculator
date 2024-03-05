#include <iostream>
#include <cmath>
#include <vector>
#include <string>

void AddClass(std::vector<std::string> &classes, std::vector<double> &unit, std::vector<char> &grade) {
	std::string name;
	double inputUnit;
	char inputGrade;
	std::cout << "Name of class? ";
	std::getline(std::cin, name);
	while (true) {
		std::cout << "How many units? ";
		std::cin >> inputUnit;

		if (isdigit(inputUnit) == true) { // FIX USER VALIDATION LATER
			std::cout << "Must be a number!\n";
		}
		else {
			A:
			std::cout << "What is your grade? (A-F Scale, no signs e.g. A+, capitalize letter) ";
			std::cin >> inputGrade;
			if (isalpha(inputGrade)) {
				if (inputGrade != 65 && inputGrade != 66 && inputGrade != 67 && inputGrade != 68 && inputGrade != 70) {
					std::cout << "Invalid grade! Make sure you enter a letter grade without a sign and to capitalize it!\n";
					goto A;
				}
				else {
					classes.push_back(name);		// MAYBE STORE IN FILE?
					unit.push_back(inputUnit);		// Might implement
					grade.push_back(inputGrade);	// Would be beneficial for long term usage
					printf("INPUTTED: %s %.1f unit(s) with grade of %c\n\n", name.c_str(), inputUnit, inputGrade); // FIX LATER
					break;
				}
			}
			else {
				std::cout << "Not a letter grade!\n";
				goto A;
			}
		}
	}
}

void CalculateGPA(std::vector<double> &unit, std::vector<char> &grade) {
	double unitsAttempted = 0, unitsEarned = 0, GPA;
	for (int i = 0; i < unit.size(); i++) {
		unitsAttempted += unit[i];
		if (grade[i] == 'A') {
			unitsEarned += unit[i] * 4;
		}
		else if (grade[i] == 'B') {
			unitsEarned += unit[i] * 3;
		}
		else if (grade[i] == 'C') {
			unitsEarned += unit[i] * 2;
		}
		else if (grade[i] == 'D') {
			unitsEarned += unit[i];
		}
		else {
			continue;
		}
	}
	GPA = unitsEarned / unitsAttempted;
	printf("Your GPA rounded to 5 decimal points is %.5f\n", GPA);
}

int CalculateFutureGPA(std::vector<double> unit, std::vector<char> grade) {
	double reachGPA, holdGPA, unitsAttempted = 0, unitsEarned = 0, GPA;
	for (int i = 0; i < unit.size(); i++) {
		unitsAttempted += unit[i];
		if (grade[i] == 'A') {
			unitsEarned += unit[i] * 4;
		}
		else if (grade[i] == 'B') {
			unitsEarned += unit[i] * 3;
		}
		else if (grade[i] == 'C') {
			unitsEarned += unit[i] * 2;
		}
		else if (grade[i] == 'D') {
			unitsEarned += unit[i];
		}
		else {
			continue;
		}
	}
	GPA = unitsEarned / unitsAttempted;
	while (true) {
		std::cout << "Your current GPA is " << GPA << ". What GPA are you aiming for?\n>> ";
		std::cin >> reachGPA;
		if (GPA == 4 && reachGPA == 4) {
			std::cout << "To maintain a GPA of 4.0, you would need to maintain A's in every course.\n";
		}
		else if (reachGPA <= GPA) {
			std::cout << "The GPA you strive to reach should be higher than your current GPA.\n";
		}
		else {
			std::cout << "What GPA will you be maintaining onwards? (e.g. 4.0 (A's from now on))\n>> ";
			std::cin >> holdGPA;
			if (holdGPA <= reachGPA) {
				std::cout << "Your GPA that you will be maintaining onwards needs to be higher than your reach GPA in order to reach that GPA.\n";
			}
			else {
				double checkReach = unitsEarned / unitsAttempted, count = 0;
				while (true) {
					if (checkReach < reachGPA) {
						unitsEarned += 4;
						unitsAttempted += 1;
						count++;
						checkReach = unitsEarned / unitsAttempted;
					}
					else {
						std::cout << "In order to reach a GPA of " << reachGPA << " while maintaining a GPA of " << holdGPA << " onwards from a GPA of " << GPA << ". You will need to earn " << count << " units which puts you at a " << checkReach << " GPA\n\n";
						return 1;
					}
				}
			}
		}
	}
}

void displayClasses(std::vector<std::string> classes, std::vector<double> unit, std::vector<char> grade) {
	for (int i = 0; i < classes.size(); i++) {
		printf("Class Name: %s\nUnits: %.1f\nGrade Earned: %c\n\n", classes[i].c_str(), unit[i], grade[i]);
	}
}

int main() {
	std::vector<std::string> classes;
	std::vector<double> unit;
	std::vector<char> grade;
	std::cout << "Welcome to GPA Calculator! What can I do for you today?\n";
	while (true) {
		char option;
		std::cout <<"(1) Add a class\n(2) Calculate current GPA for inputted classes\n(3) Grades needed for a certain GPA\n(4) View all classes\n(5) Exit\n >> ";
		std::cin >> option;
		std::cin.ignore();
		if (!isdigit(option)) {
			std::cout << "Please enter a valid choice!\n\n";
		}
		else {
			if (option == '1') {
				AddClass(classes, unit, grade);
			}
			else if (option == '2') {
				CalculateGPA(unit, grade);
			}
			else if (option == '3') {
				CalculateFutureGPA(unit, grade);
			}
			else if (option == '4') {
				displayClasses(classes, unit, grade);
			}
			else if (option == '5') {
				std::cout << "Thanks for using my program!\n";
				break;
			}
		}
	}
}
