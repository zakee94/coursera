#include <iostream>
#include <iterator>
#include <list>
#include <set>
#include <map>
#include <utility>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <limits.h>

using namespace std;

struct edge {
    int v2;
    int length;
};
typedef struct edge edge;

void addEdge(list<edge*> adj_list[], int size, int v1, int v2, int length) {
    edge* E = (edge*)malloc(sizeof(edge));

    if (v2 < size) {
        E->v2 = v2;
        E->length = length;

        adj_list[v1].push_back(E);
    }
    else
        cout << "\nERROR : Vertice value '" << v2 << "' exceeds that of graph size !\n";

    if (v1 < size) {  // The check as mentioned above
        edge* E = (edge*)malloc(sizeof(edge));
        E->v2 = v1;
        E->length = length;

        adj_list[v2].push_back(E);
    }
    else
        cout << "\nERROR : Vertice value '" << v1 << "' exceeds that of graph size !\n";
}

void printGraph(list<edge*> adj_list[], int size) {
    list<edge*>::iterator itr;

    int i;
    for (i = 0; i < size; i++) {
        cout << "\nV : " << i << " || ";
        for (itr = adj_list[i].begin(); itr != adj_list[i].end(); itr++)
            cout << "(" << (*itr)->v2 << ", " << (*itr)->length << ") ; ";
    }
    cout << "\n";
}

void primsMST(list<edge*> adj_list[], int size, int src) {
    multimap < int, int > minMap;
    multimap<int,int>::iterator itrMap, itrMapIn;

    list<edge*>::iterator itrEdge;
    int i, sum = 0;

    for (i = 1; i < size; i++) {
        if (i != src)
            minMap.insert(pair<int,int>(INT_MAX, i));
        else
            minMap.insert(pair<int,int>(0, i));
    }

    while (!minMap.empty()) {
        itrMap = minMap.begin();
        minMap.erase(itrMap);

        sum = sum + itrMap->first;

        for(itrEdge = adj_list[itrMap->second].begin(); itrEdge != adj_list[itrMap->second].end(); itrEdge++) {
            for (itrMapIn = minMap.begin(); itrMapIn != minMap.end(); itrMapIn++) {
                if ( (itrMapIn->second == (*itrEdge)->v2) && ((*itrEdge)->length < itrMapIn->first) ) {
                    minMap.erase(itrMapIn);
                    minMap.insert(pair<int,int>((*itrEdge)->length, (*itrEdge)->v2));
                    break;
                }
            }
        }
    }
    cout << sum << "\n";
}

int main() {
    int size = 501;
    list<edge*>* adj_list = new list<edge*>[size];

	char ch;
	string v1, v2, cost, word;
	ifstream inFile;

	inFile.open("input.txt");

	if (inFile.is_open()) {
		while (inFile.get(ch)) {
			if (ch != ' ' && ch != '\n')
				word = word + ch;
			else if (ch == ' ' && v1.empty() && v2.empty()) {
				v1 = word;
				word.clear();
			}
			else if (ch == ' ' && !v1.empty() && v2.empty()) {
				v2 = word;
				word.clear();
			}
			else if (ch == '\n') {
				cost = word;
				word.clear();
				//cout << v1 << " " << v2 << " " << cost << "\n";
				addEdge(adj_list, size, stoi(v1), stoi(v2), stoi(cost));
				v1.clear();
				v2.clear();
				cost.clear();
			}
		}
	}
	else
		cout << "Error opening file !\n";
	inFile.close();

    //cout << "\nAdjacency List :\n";
    //printGraph(adj_list, size);

    primsMST(adj_list, size, 1);
}
