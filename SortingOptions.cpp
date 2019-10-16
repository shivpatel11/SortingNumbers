/***************************************************************
*file: SortingOptions.cpp
*author: Shiv Patel
*class: CS 2560 – C++
*assignment: program 3
*date last modified: 10/4/2019
*
*purpose: This program asks the user to give an input and output file and aks what kind of sort to use.
*Then the program sorts the input file numbers and then puts it in the output file.
*
****************************************************************/
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

//function prototypes
void selectionSort(vector<int>&);
void mergeSort(vector<int>&);
void merge(vector<int>&, vector<int>&, vector<int>&);
void quickSort(vector<int>&, int, int);
int partition(vector<int>&, int, int);
void insertionSort(vector<int>&);

int main()
{
	string inFile;
	string outFile;
	ifstream inputFile;
	ofstream outputFile;
	int number;
	vector<int> numbers;
	int userChoice;
	//ask for files and check if they are valid
    cout << "Sorting options\n";
	cout << "---------------------------------\n";
	cout << "Enter a file for input: ";
	cin >> inFile;
	inputFile.open(inFile);
	while (inputFile.fail())
	{
		cout << "Enter a valid file name: ";
		cin >> inFile;
		inputFile.open(inFile);
	}
	cin.ignore();
	cout << "\nEnter a file for output: ";
	cin >> outFile;
	outputFile.open(outFile);
	while (outputFile.fail())
	{
		cout << "Enter a valid file name: ";
		cin >> outFile;
		outputFile.open(outFile);
	}
	//create a new vector with all the numbers
	while (inputFile >> number)
	{
		numbers.push_back(number);
	}
	//ask user what type of sorting algorithmn to use
	cout << "\n\nWhat sorting algorithmn would you like to use?\n";
	cout << "\t1. Selection Sort\n";
	cout << "\t2. Merge Sort\n";
	cout << "\t3. Quick Sort\n";
	cout << "\t4. Insertion Sort\n";
	cout << "(Enter an integer value for your selection): ";
	cin >> userChoice;
	while (userChoice < 1 || userChoice > 4)
	{
		cout << "\nEnter a valid choice: ";
		cin >> userChoice;
	}
	cout << "\n\nOriginal vector: [";
	for (int i = 0; i < numbers.size(); i++)
	{
		if (i != numbers.size() - 1)
		{
			cout << numbers[i] << ", ";
		}
		else
		{
			cout << numbers[i];
		}
	}
	cout << "]\n\n";
	cout << "Vector is now being sorted:\n\n";
	switch (userChoice)
	{
	case 1:
		selectionSort(numbers);
		break;
	case 2:
		mergeSort(numbers);
		break;
	case 3:
		quickSort(numbers, 0, numbers.size() - 1);
		break;
	case 4:
		insertionSort(numbers);
		break;
	}
	cout << "\n\nVector is now sorted!";
	//print the vector into the output file
	for (int val : numbers)
	{
		outputFile << val << endl;
	}
	inputFile.close();
	outputFile.close();
	return 0;
}
//implement selection sort
void selectionSort(vector<int> &v)
{
	int minIndex = 0;
	int minValue = 0;
	for (int start = 0; start < (v.size() - 1); start++)
	{
		minIndex = start;
		minValue = v[start];
		for (int index = start + 1; index < v.size(); index++)
		{
			if (v[index] < minValue)
			{
				minValue = v[index];
				minIndex = index;
			}
		}
		int temp = v[minIndex];
		v[minIndex] = v[start];
		v[start] = temp;
		cout << "[";
		for (int i = 0; i < v.size(); i++)
		{
			if (i != v.size() - 1)
			{
				cout << v[i] << ", ";
			}
			else
			{
				cout << v[i];
			}
		}
		cout << "] Switched index " << start << " and " << minIndex;
		cout << endl;
	}
}
//implements merge sort with helper method 
void mergeSort(vector<int> &v)
{
	if (v.size() <= 1) 
		return;

	int mid = v.size() / 2;
	vector<int> left;
	vector<int> right;

	for (int j = 0; j < mid; j++)
		left.push_back(v[j]);
	cout << "[";
	for (int i = 0; i < left.size(); i++)
	{
		if (i != left.size() - 1)
		{
			cout << left[i] << ", ";
		}
		else
		{
			cout << left[i];
		}
	}
	cout << "]";
	for (int j = 0; j < (v.size()) - mid; j++)
		right.push_back(v[mid + j]);
	cout << "[";
	for (int i = 0; i < right.size(); i++)
	{
		if (i != right.size() - 1)
		{
			cout << right[i] << ", ";
		}
		else
		{
			cout << right[i];
		}
	}
	cout << "]" << endl;
	mergeSort(left);
	mergeSort(right);
	merge(left, right, v);
}
//helper method for mergeSort that merges two sorted vectors together
void merge(vector<int> &left, vector<int> &right, vector<int> &v)
{
	int newLeft = left.size();
	int newRight = right.size();
	int i = 0;
	int	j = 0; 
	int k = 0;

	while (j < newLeft && k < newRight)
	{
		if (left[j] < right[k]) {
			v[i] = left[j];
			j++;
		}
		else 
		{
			v[i] = right[k];
			k++;
		}
		i++;
	}
	while (j < newLeft) 
	{
		v[i] = left[j];
		j++; i++;
	}
	while (k < newRight) 
	{
		v[i] = right[k];
		k++; i++;
	}
	cout << "[";
	for(int i = 0; i < v.size(); i++)
	{
		if (i != v.size() - 1)
		{
			cout << v[i] << ", ";
		}
		else
		{
			cout << v[i];
		}
	}
	cout << "]" << endl;
}
//implements quickSort with helper method
void quickSort(vector<int> &v, int start, int end)
{
	int pivotPoint;
	if (start < end)
	{
		pivotPoint = partition(v, start, end);
		quickSort(v, start, pivotPoint - 1);
		quickSort(v, pivotPoint + 1, end);
	}
}
//helper method for quickSort which finds the middle point of the vector
int partition(vector<int> &v, int start, int end)
{
	int pivotValue;
	int pivotIndex;
	int mid;
	int temp;
	mid = (start + end) / 2;
	temp = v[start];
	v[start] = v[mid];
	v[mid] = temp;
	cout << "[";
	for (int i = 0; i < v.size(); i++)
	{
		if (i != v.size() - 1)
		{
			cout << v[i] << ", ";
		}
		else
		{
			cout << v[i];
		}
	}
	cout << "] Switched index " << start << " and " << mid;
	cout << endl;
	pivotIndex = start;
	pivotValue = v[start];
	for (int j = start + 1; j <= end; j++)
	{
		if (v[j] < pivotValue)
		{
			pivotIndex++;
			temp = v[pivotIndex];
			v[pivotIndex] = v[j];
			v[j] = temp;
			cout << "[";
			for (int i = 0; i < v.size(); i++)
			{
				if (i != v.size() - 1)
				{
					cout << v[i] << ", ";
				}
				else
				{
					cout << v[i];
				}
			}
			cout << "] Switched index " << j << " and " << pivotIndex;
			cout << endl;
		}
	}
	temp = v[start];
	v[start] = v[pivotIndex];
	v[pivotIndex] = temp;
	cout << "[";
	for (int i = 0; i < v.size(); i++)
	{
		if (i != v.size() - 1)
		{
			cout << v[i] << ", ";
		}
		else
		{
			cout << v[i];
		}
	}
	cout << "] Switched index " << start << " and " << pivotIndex;
	cout << endl;
	return pivotIndex;
}
//implements insertionSort
void insertionSort(vector<int> &v)
{
	int i;
	int j;
	int temp;
	for (i = 1; i < v.size(); i++)
	{
		j = i;
		while (j > 0 && v[j - 1] > v[j])
		{
			temp = v[j];
			v[j] = v[j - 1];
			v[j - 1] = temp;
			j--;
			cout << "[";
			for (int i = 0; i < v.size(); i++)
			{
				if (i != v.size() - 1)
				{
					cout << v[i] << ", ";
				}
				else
				{
					cout << v[i];
				}
			}
			cout << "]" << " Switched index " << (j+1) << " and " << j;
			cout << endl;
		}
	}
}