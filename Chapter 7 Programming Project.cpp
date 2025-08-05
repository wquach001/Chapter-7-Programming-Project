// Chapter 7 Programming Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
using namespace std;
#include <iostream>
#include <fstream> // For file operations
#include <string> // For string class


char* getAnswers(std::string filename, int& numQuestions);
char* gradeExam(char* answerKey, char* StudentAnswers, int numQuestions
	            , int* wrongAnsNum, char* wrongAns, char* correctAns, int& wrongCnt);
void writeReport ();

int main() {
	int numQuestions = 0; // Variable to hold the number of questions
	int studentQuestions = 0; // Variable to hold the number of questions
	char* wrongAnsQuestNum = nullptr; // Pointer to hold the question numbers of wrong answers
	char* wrongAns = nullptr; // Pointer to hold the wrong answers
	char* correctAns = nullptr; // Pointer to hold the correct answers
	int wrongCnt = 0; // Counter for the number of wrong answers

	char* answerKey = getAnswers("CorrectAnswers.txt", numQuestions);
	char* studentTest = getAnswers("StudentAnswers.txt", studentQuestions);
	//char* report = gradeExam(answerKey, studentTest, numQuestions);
	char* report = gradeExam(answerKey, studentTest, numQuestions, wrongAnsQuestNum, wrongAns, correctAns, wrongCnt);

	return 0; // Indicate successful program execution
}   // END main()

// Function to read the answer key from a file and 
// return it as a character array
char* getAnswers(std::string filename, int& numQuestions) 
{
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Error: Could not open " << filename << std::endl;
		return nullptr;
	}
	cout << "Reading from file: " << filename << endl;	
	std::string line;

	char* answers = new char[50];
	int i = 0;

	while ( getline(file, line) )  {
		if (!line.empty()) {
			answers[i] = line[0];
			cout << answers[i] << " "; // Output each answer for debugging	
			i++;
		}
	}
	cout << endl;
	numQuestions = i; // Set the number of questions from lines read
	cout << "number Questions: " << numQuestions << endl;
	file.close(); // Close the file after reading

	return answers;
}

// Function to grade the exam based on the answer key and student answers
// This function will compare the two arrays and return a score or feedback
char* gradeExam(  char* answerKey,   char* StudentAnswers, int numQuestions
	            , int* wrongAnsNum, char* wrongAns, char* correctAns, int& wrongCnt)
{

	char* result = new char[numQuestions];
	int* wrongAnsNum = new char[numQuestions];
	char* wrongAns = new char[numQuestions];
	char* correctAns = new char[numQuestions];
	wrongCnt = 0;

	for (int i = 0; i < numQuestions; i++) {
		if (StudentAnswers[i] == answerKey[i])
			result[i] = 'C'; // Correct
		else {
			wrongAnsNum[wrongCnt] = i; // Wrong
			wrongAns[wrongCnt] = StudentAnswers[i]; // Wrong
			correctAns[wrongCnt] = answerKey[i]; // Wrong
			wrongCnt++; // Increment wrong answer count
		}
	}
	wrongCnt--
	return result;

	return nullptr; // Placeholder return, replace with actual grading logic


}
