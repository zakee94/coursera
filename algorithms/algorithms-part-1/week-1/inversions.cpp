#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>

using namespace std;
typedef long long unsigned int integer;

#define MAX 100000

integer merge(integer left[], integer l, integer right[], integer r, integer arr[]) {
    integer i = 0, j = 0, k = 0, count = 0;

    while (i < l && j < r) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        }
        else {
            arr[k] = right[j];
            j++;
            // Note Carefully ->
            count = count + (l-i); // The only differnece between merge sort and this !
        }
        k++;
    }

    while (i < l) {
        arr[k] = left[i];
        k++;
        i++;
    }

    while (j < r) {
        arr[k] = right[j];
        k++;
        j++;
    }

    return count;
}

integer split(integer arr[], integer n) {
    integer i, left[n], j, right[n], k = 0, x, y, z;

    if (n == 1)
    return 0;

    for (i = 0; i < n/2; i++) {
        left[i] = arr[i];
    }

    for (j = n/2; j < n; j++) {
        right[k] = arr[j];
        k++;
    }

    return split(left, i) + split(right, k) + merge(left, i, right, k, arr);
}

int main(int argc, char const *argv[]) {
    ifstream inFile;
    string word;
    char ch;
    integer i = 0, arr[MAX];

	inFile.open("input.txt");

    if (inFile.is_open()) {
		while (inFile.get(ch)) {
            if (ch == '\n') {
                arr[i] = stoll(word);
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

    cout << split(arr, MAX) << "\n";
    return 0;
}
