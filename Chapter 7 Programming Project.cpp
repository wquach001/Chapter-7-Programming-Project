// Chapter 7 Programming Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
using namespace std;
#include <iostream>
#include <fstream> // For file operations
#include <string> // For string class
#include <iomanip>  // for setw

char* getAnswers(std::string filename, int& numQuestions);
int gradeExam(char* answerKey, char* StudentAnswers, int numQuestions
	            , int* wrongAnsNum, char* wrongAns, char* correctAns);
void writeReport (int* wrongAnsNum, char* wrongAns, char* correctAns, int numWrong, int totalQuestions);

int main() {
	int numQuestions = 0; // Variable to hold the number of questions
	int studentQuestions = 0; // Variable to hold the number of questions
	int* wrongAnsQuestNum = nullptr; // Pointer to hold the question numbers of wrong answers
	char* wrongAns = nullptr; // Pointer to hold the wrong answers
	char* correctAns = nullptr; // Pointer to hold the correct answers
	int wrongCnt = 0; // Counter for the number of wrong answers

	char* answerKey = getAnswers("CorrectAnswers.txt", numQuestions);
	char* studentTest = getAnswers("StudentAnswers.txt", studentQuestions);

	//Grade the student's work
	wrongAnsQuestNum = new int[numQuestions];
	wrongAns = new char[numQuestions];
	correctAns = new char[numQuestions];

	wrongCnt = gradeExam(answerKey, studentTest, numQuestions, wrongAnsQuestNum, wrongAns, correctAns);

	// report the results
	cout << "Number of Questions: " << numQuestions << "  Number Wrong: " << wrongCnt << endl;
	writeReport(wrongAnsQuestNum, wrongAns, correctAns, wrongCnt, numQuestions);


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
int gradeExam(  char* answerKey,   char* StudentAnswers, int numQuestions
	            , int* wrongAnsNum, char* wrongAns, char* correctAns)
{

	int wrongCnt = 0;

	for (int i = 0; i < numQuestions; i++) {
		if (StudentAnswers[i] == answerKey[i])
			cout<< StudentAnswers[i] << " = " << answerKey[i] << endl; // Correct
		else {
			wrongAnsNum[wrongCnt] = i; // problem number got Wrong
			wrongAns[wrongCnt] = StudentAnswers[i]; // Wrong answers
			correctAns[wrongCnt] = answerKey[i]; // right answers
			
			cout << StudentAnswers[i] << " != " << answerKey[i] << endl; // Output the wrong answer
			cout << "Question " << i + 1 << " is wrong. Your answer: "
				<< StudentAnswers[i] << ", Correct answer: " << answerKey[i] << endl;
			//cout << "Question " << wrongAnsNum[wrongCnt] + 1 << " is wrong. Your answer: "
			//	<< wrongAns[wrongCnt] << ", Correct answer: " << correctAns[wrongCnt] << endl;


			wrongCnt++; // Increment wrong answer count
		}
	}
	return wrongCnt;

}   // END gradeExam()

// Function to write a report
void writeReport(int* wrongAnsNum, char* wrongAns, char* correctAns, int numWrong, int totalQuestions)
{
	//ofstream reportFile("Report.txt");
	//if (!reportFile.is_open()) {
	//	cerr << "Error: Could not open Report.txt" << endl;
	//	return;
	//}
	cout << "Exam Report Details " << endl;
	cout << "Number of Questions Missed :  " << numWrong << endl;
	cout << "Missed Questions and Correct Answers: " << endl;
	cout << "Question       Correct Answers     Your Answer " << endl;
	cout << "-----------    ---------------     ------------ " << endl;
	for (int i = 0; i < numWrong; i++) {
		cout << "     " << wrongAnsNum[i] + 1 << setw(15) << correctAns[i] << setw(20) << wrongAns[i] << endl;
		//cout << wrongAnsNum[i] + 1 << correctAns[i] << wrongAns[i] << endl;
	}

	double finalScore = (totalQuestions - numWrong) * 100.0 / totalQuestions;
	cout << "Test Score :  " << finalScore << endl;
	if (finalScore > 70) {
		cout << "You PASSED the exam. :-)" << endl;
	} else {
		cout << "You FAILED the exam. :-(" << endl;
	}
}


