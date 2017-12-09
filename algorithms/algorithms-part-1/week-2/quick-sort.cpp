#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

#define MAX 10000

int median(int a, int b, int c) {
    if ( (b > a && b < c) || (b > c && b < a) )
        return b;
    else if ( (c > a && c < b) || (c > b && c < a) )
        return c;
    else if ( (a > b && a < c) || (a > c && a < b) )
        return a;
}

int middle(int arr[], int start, int end) {
    int middle, size = end-start+1;

    if (size%2 == 0)
        middle = start+(size/2)-1;
    else
        middle = start+(size/2);

    int medianElement = median(arr[start], arr[middle], arr[end]);

    if (medianElement == arr[start])
        return start;
    else if (medianElement == arr[middle])
        return middle;
    else if (medianElement == arr[end])
        return end;
}

int choosePivot(int arr[], int start, int end, int choice) {
    int piv_index;

    switch(choice) {
        case 0 :
        piv_index = rand()%(end-start) + start;
        break;
        //
        case 1 :
        piv_index = start;
        break;
        //
        case 2 :
        piv_index = end;
        break;
        //
        case 3 :
        piv_index = middle(arr, start, end);
        break;
        //
        default :
        cout << "Wrong choice for choosePivot !\nSelect an int form [0 to 3].\n";
        piv_index = -1;
    }
    return piv_index;
}

int partition(int arr[], int start, int end) {
    if (start >= end)
        return 0;

    int comparisons = end-start;
    int piv_index = choosePivot(arr, start, end, 3);
    swap(arr[piv_index], arr[start]);

    int j, i = start+1;
    for (j = start+1; j <= end; j++) {
        if (arr[j] < arr[start]) {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[start], arr[i-1]);

    comparisons = comparisons + partition(arr, start, i-2) + partition(arr, i, end);
    return comparisons;
}

int main(int argc, char const *argv[]) {
    ifstream inFile;
    string word;
    char ch;
    int i = 0, arr[MAX];

	inFile.open("input.txt");

    if (inFile.is_open()) {
		while (inFile.get(ch)) {
            if (ch == '\n') {
                arr[i] = stoi(word);
                i++;
                word.clear();
            }
            else {
                word = word + ch;
            }
        }
    }
    else
		cout << "Error opening file !\n";
	inFile.close();

    srand(time(NULL));
    cout << partition(arr, 0, MAX-1) << "\n";
    return 0;
}
