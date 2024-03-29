#include "stdafx.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <ctime>

using namespace std;

struct Node {
	string word;
	int wordValue;

	struct Node *next;
};

class List {
private:

	struct Node *head = NULL;
	int length = 0; // length shows how many nodes we have in the list in total
public:

	int getLength() {
		return length;
	}

	void addItem(string word, int asciiSum) {
		struct Node *tmp;

		if (head == NULL) { // creation of new node if there are no nodes yet
			head = new Node();
			head->word = word;
			head->wordValue = asciiSum;
			head->next = NULL;
		}
		else { // creation of new node if there is already at least 1 node

			tmp = head;

			while (tmp->next != NULL) {
				tmp = tmp->next;
			}
			tmp->next = new Node();

			tmp->next->word = word;
			tmp->next->wordValue = asciiSum;
			tmp->next->next = NULL;
		}
		length++; 
	}

	Node** getPointersAsArray() 
	{

		Node** nodeArray; // an array of pointers which hold addresses to nodes
		nodeArray = new Node*[length]; 
		int i = 0;                                        

		struct Node *current;
		current = head;
		if (current != NULL)
		{
			while (current != NULL) // this loop is meant for making the pointers inside the nodeArray to point at nodes in the List
			{
				nodeArray[i] = current; 
				current = current->next;
				i++; 
			}
		}
		else {
			printf("The list is empty \n"); 
		}

		return nodeArray; 
	}
};


void printNodeArray(Node *arr[], int length) { 

	for (int i = 0; i < length; i++) { 
		if (arr[i] == nullptr) { 
			break;
		}
		else {
			cout << "#" << i + 1 << ": '" << arr[i]->word << "'-> " << arr[i]->wordValue << endl; 
		}
	}
}


// Utility function for swapping nodes. *a stands for "value pointed by a" etc.
void swap(Node* a, Node* b)
{
	Node t = *a;
	*a = *b;
	*b = t;
}


int leftmostPivotPartition(Node *arr[], int startElement, int endElement)
{
	Node *pivot = arr[startElement];    // pivot
	int i = endElement;

	for (int j = endElement; j >= startElement + 1; j--)
	{
		if (arr[j]->wordValue >= pivot->wordValue)
		{
			swap(arr[i], arr[j]);
			i--;
		}
	}
	swap(arr[i], arr[startElement]);
	return i;
}

void quicksortMiddlePivot(Node *arr[], int left, int right)
{

	int i = left, j = right;
	Node *pivot = arr[(left + right) / 2];

	/* partition */
	while (i <= j) {
		while (arr[i]->wordValue < pivot->wordValue)
			i++;
		while (arr[j]->wordValue > pivot->wordValue)
			j--;
		if (i <= j) {
			swap(arr[i], arr[j]);
			i++;
			j--;
		}
	};
	/* recursion */
	if (left < j)
		quicksortMiddlePivot(arr, left, j);
	if (i < right)
		quicksortMiddlePivot(arr, i, right);
}


int rightmostPivotPartition(Node *arr[], int startElement, int endElement)
{
	Node *pivot = arr[endElement];    
	int i = startElement; 

	for (int j = startElement; j <= endElement - 1; j++)
	{

		if (arr[j]->wordValue <= pivot->wordValue)
		{
			swap(arr[i], arr[j]);
			i++; 
		}
	}

	swap(arr[i], arr[endElement]);
	return i;
}


void quicksortLeftmostPivot(Node *arr[], int low, int high)
{
	//0 1
	if (low < high)
	{
		//pi is partition index - it is the place where the split (partition) happens
		int pi = leftmostPivotPartition(arr, low, high);
		
		quicksortLeftmostPivot(arr, low, pi - 1);
		quicksortLeftmostPivot(arr, pi + 1, high); 
	}
}

void quicksortRightmostPivot(Node *arr[], int low, int high)
{
	//0 1
	if (low < high)
	{
		// pi is partition index - it is the place where the split (partition) happens

		int pi = rightmostPivotPartition(arr, low, high);
		
		quicksortRightmostPivot(arr, low, pi - 1); 
		quicksortRightmostPivot(arr, pi + 1, high);
	}
}


int sumString(string word) { 
	int sum = 0;
	for (int i = 0; i < word.size(); i++) { 
		sum += word[i]; 
	}
	return sum;
}

int main()
{
	ifstream dataFile("text.txt");

	if (!dataFile)
	{
		cout << "Error opening the file" << endl;
		exit(1);
	}

	List words;
	string input;

	while (dataFile >> input)
	{
		words.addItem(input, sumString(input));
	}


	Node** pointerArray = words.getPointersAsArray(); 
													  
													  
	cout << "\n";

	clock_t t;
	t = clock();

	//quicksortLeftmostPivot(pointerArray, 0, words.getLength() - 1); 
	//quicksortRightmostPivot(pointerArray, 0, words.getLength() - 1); 
	quicksortMiddlePivot(pointerArray, 0, words.getLength() - 1); 

	t = clock() - t;
	printf("Running time: %d clicks (%f seconds).\n", t, ((float)t) / CLOCKS_PER_SEC);
	

	cout << "\n";
	printNodeArray(pointerArray, words.getLength()); 

	delete[] pointerArray; 

	return 0;
}


