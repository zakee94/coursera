#include <iostream>
#include <iterator>
#include <stdlib.h>
#include <time.h>
#include <list>
#include <fstream>
#include <string>

using namespace std;
typedef long long unsigned int integer;

void addEdge(list<integer> adj_list[], integer firstV, integer secondV) {
    adj_list[firstV].push_back(secondV);
}

void printGraph(list<integer> adj_list[], integer size) {
    list<integer>::iterator itr;

    integer i;
    for (i = 1; i < size; i++) {
        cout << "\nV : " << i << " || ";
        for (itr = adj_list[i].begin(); itr != adj_list[i].end(); itr++) {
            cout << *itr << " ";
        }
    }
    cout << "\n";
}

// We use recursion as means of stack, since recursion by itself is an stack operaton
int DFTUtil(list<integer> adj_list[], bool visited[], integer size, integer start) {
    list<integer>::iterator itr;
    int sum = 0;

    visited[start] = true;
    //cout << start << " ";
    sum = sum + 1;

    for (itr = adj_list[start].begin(); itr != adj_list[start].end(); itr++) {
        if (visited[*itr] == false)
            sum = sum + DFTUtil(adj_list, visited, size, *itr);
    }
    return sum;
}

void DFT(list<integer> adj_list[], integer size, integer start) {
    integer i;
    bool* visited = (bool*)malloc(sizeof(bool)*size);

    for (i = 0; i < size; i++)
        visited[i] = false;

    DFTUtil(adj_list, visited, size, start);
}

list<integer>* reverseGraph(list<integer> adj_list[], integer size) {
    list<integer> *rev_adj_list = new list<integer>[size];
    list<integer>::iterator itr;
    integer i;

    for (i = 1; i < size; i++) {
        for (itr = adj_list[i].begin(); itr != adj_list[i].end(); itr++) {
            rev_adj_list[*itr].push_back(i);
        }
    }

    return rev_adj_list;
}

// Store in stack in order of finishing time
void firstPass(list<integer> adj_list[], list<integer> &stack, bool visited[], integer size, integer start) {
    list<integer>::iterator itr;

    visited[start] = true;

    for (itr = adj_list[start].begin(); itr != adj_list[start].end(); itr++) {
        if (visited[*itr] == false)
            firstPass(adj_list, stack, visited, size, *itr);
    }

    stack.push_front(start);
}

void secondPass(list<integer> adj_list[], integer size) {
    integer i;
    list<integer> stack;
    bool* visited = (bool*)malloc(sizeof(bool)*size);

    for (i = 0; i < size; i++)
        visited[i] = false;

    // Call for first pass, here we store in stack
    for (i = 1; i < size; i++) {
        if (visited[i] == false)
            firstPass(adj_list, stack, visited, size, i);
        }

    // Now reverse the graph so that source becomes sink
    adj_list = reverseGraph(adj_list, size);

    // Rsest the visited cache for second round of DFS
    for (i = 0; i < size; i++)
        visited[i] = false;

    // Now once reversal happens, then we can pop the stack and accordingly
    // use the sinks stored in stack for DFS and print them
    while (stack.size() > 0) {
        integer vertex = stack.front();
        stack.pop_front();

        if (visited[vertex] == false) {
            int ans = DFTUtil(adj_list, visited, size, vertex);
            if (ans != 1) {
                cout << ans;
                cout << "\n";
            }
        }
    }
}

int main() {
    integer size = 875715;
    list<integer> *adj_list = new list<integer>[size];

    char ch;
    integer j;
    bool flag = false;
    string word;
	ifstream inFile;

	inFile.open("input.txt");

	if (inFile.is_open()) {
        while (inFile >> word) {
            if (!flag) {
                j = (integer)stoi(word);
                flag = true;
            }
            else {
                //adj_list[(integer)stoi(word)].push_back(j);
                adj_list[j].push_back((integer)stoi(word));
                flag = false;
            }
        }
    }
	else
		cout << "Error opening file !\n";
	inFile.close();

    //cout << "\nAdjacency Lists : \n";
    //printGraph(adj_list, size);

    //cout << "\nStrongly Conncted Components : \n";
    secondPass(adj_list, size);
}
