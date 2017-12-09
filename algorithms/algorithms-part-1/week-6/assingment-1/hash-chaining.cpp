#include <iostream>
#include <fstream>
#include <list>
#include <iterator>
#include <stdlib.h>
#include <string>

using namespace std;
long long int size = 999091, lLimit = -10000, uLimit = 10000;

// here we shall use an array of only modest size of 997(prime no), and
// for collisions we will be using list implementation.
// so basically we get an adjacency list type of implementation

long long int hashFunction(long long int n) {
    return (abs(n) % size);
}

long long int lookUp(list<long long int> array[], long long int n) {
    list<long long int>::iterator itr;
    long long int i = hashFunction(n);

    for (itr = array[i].begin(); itr != array[i].end(); itr++) {
        if(n == *itr) {
            return 1;
        }
    }
    return 0;
}

long long int compute(list<long long int> array[]) {
    list<long long int>::iterator itr;
    long long int i, sum, y, flag, total = 0;

    for (sum = lLimit; sum <= uLimit; sum++) {
        flag = 0;
        for (i = 0; i < size; i++) {
            if (flag == 1)
                break;
            else {
                for (itr = array[i].begin(); itr != array[i].end(); itr++) {
                    y = sum - (*itr);
                    if (lookUp(array, y) && *itr != y) {
                        //cout << *itr << "," << y << "\n";
                        total++;
                        flag = 1;
                        break;
                    }
                }
            }
        }
    }
    return total;
}

void insert(list<long long int> array[], long long int n) {
    if (!lookUp(array, n))
        array[hashFunction(n)].push_back(n);
}

int main() {
    list<long long int> *array = new list<long long int>[size];
    long long int n = 0;
    ifstream inFile;
    string word;
    char ch;

	inFile.open("input.txt");

    if (inFile.is_open()) {
		while (inFile.get(ch)) {
            if (ch == '\n') {
                insert(array, stoll(word));
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

    cout << compute(array) << "\n";
    return 0;
}
