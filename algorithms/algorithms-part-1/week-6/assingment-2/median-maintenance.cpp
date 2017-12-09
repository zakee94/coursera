#include <iostream>
#include <queue>
#include <fstream>
#include <string>

using namespace std;

priority_queue<int> qLow;
priority_queue<int, std::vector<int>, std::greater<int> > qHigh;
int size = 0, median = 0, sum = 0;;

void calcMedian() {
    if (size%2 == 0)
        median = qLow.top();
    else {
        if (qLow.size() > qHigh.size())
            median = qLow.top();
        else
            median = qHigh.top();
    }
}

void insert(int n) {
    if (size%2 == 0) {
        if (n < median)
            qLow.push(n);
        else
            qHigh.push(n);
    }
    else {
        if (qLow.size() > qHigh.size()) {
            if (n < median) {
                qHigh.push(qLow.top());
                qLow.pop();
                qLow.push(n);
            }
            else
                qHigh.push(n);
        }
        else {
            if (n < median)
                qLow.push(n);
            else {
                qLow.push(qHigh.top());
                qHigh.pop();
                qHigh.push(n);
            }
        }
    }
    size++;
    calcMedian();
    sum = sum + median;
}

int main() {
    ifstream inFile;
    string word;
    char ch;

	inFile.open("input.txt");

    if (inFile.is_open()) {
		while (inFile.get(ch)) {
            if (ch == '\n') {
                insert(stoi(word));
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

    cout << sum%10000 << "\n";
    return 0;
}
