#include <iostream>
#include <iterator>
#include <stdlib.h>
#include <time.h>
#include <list>
#include <fstream>
#include <string>

using namespace std;

void printArray(int arr[], int size) {
    int i;

    for (i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << "\n";
}

void swap(int *a, int *b) {
    int temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

void addEdge(list<int> adj_list[], int firstV, int secondV) {
    adj_list[firstV].push_back(secondV);
    adj_list[secondV].push_back(firstV);
}

void printGraph(list<int> adj_list[], int size) {
    list<int>::iterator itr;

    int i;
    for (i = 1; i < size; i++) {
        cout << "\nV : " << i << " || ";
        for (itr = adj_list[i].begin(); itr != adj_list[i].end(); itr++) {
            cout << *itr << " ";
        }
    }
    cout << "\n";
}

void initVertices(int vertices[], int size) {
    int i;
    for (i = 0; i < size-1; i++)
        vertices[i] = i + 1;
}

void shrink(list<int> adj_list[], int vertice1, int vertice2) {
    //cout << "\nMerging ( " << vertice1 << ", " << vertice2 << " ) together !\n";

    // vertice1 is getting out of the graph i.e. it is being disconnected
    // make sure that all the vertices it(vertice1) was being connected get
    // updated properly
    list<int>::iterator itr;
    for (itr = adj_list[vertice1].begin(); itr != adj_list[vertice1].end(); itr++) {
        if (*itr != vertice2) {
            adj_list[*itr].remove(vertice1);
            adj_list[*itr].push_back(vertice2);
        }
    }

    adj_list[vertice2].merge(adj_list[vertice1]);

    // Remove self loops
    adj_list[vertice2].remove(vertice1);
    adj_list[vertice2].remove(vertice2);
}

void randomize(int vertices[], list<int> adj_list[], int size) {
    list<int>::iterator itr;
    int no_of_vertices = size - 2;

    //printArray(vertices, no_of_vertices+1);
    int vertice1, vertice2;

    while (no_of_vertices >= 2) {
        int vertice_pos = rand() % no_of_vertices;
        vertice1 = vertices[vertice_pos];

        if (adj_list[vertice1].size() > 1) { // if-else is necessary to ensure that
                                             // "rand() % 0" does not accidently happen
            int list_pos = rand()%(adj_list[vertice1].size() - 1);

            //cout << list_pos << "\n";
            int i;
            for (itr = adj_list[vertice1].begin(), i = 0; i <= list_pos; itr++, i++)
                vertice2 = *itr;
            }
        else
            vertice2 = *adj_list[vertice1].begin();

        // get vertice1 & vertice2 => the random edge is selected !
        shrink(adj_list, vertice1, vertice2);

        // Fisher-Yates
        swap(&vertices[no_of_vertices], &vertices[vertice_pos]);
        no_of_vertices--;
        //printArray(vertices, no_of_vertices+1);

        //cout << "\nAdjacency Lists : \n";
        //printGraph(adj_list, size);
    }

    cout << adj_list[vertices[0]].size() << "\n";
}

int main() {
    int size = 201;
    list<int> *adj_list = new list<int>[size];

    int *vertices = (int *)malloc(sizeof(int) * size);

    initVertices(vertices, size);
    srand(time(NULL));

    char ch;
    int j = 1;
    string word;
	ifstream inFile;

	inFile.open("input.txt");

	if (inFile.is_open()) {
		while (inFile.get(ch)) {
            if (ch == '\n') {
                adj_list[j].push_back(stoi(word));
                word.clear();

                while (inFile.get(ch)) {
                    if (ch == ' ')
                    break;
                }
                j++;
            }
            else {
                if (ch != ' ')
                    word = word + ch;
                else {
                    adj_list[j].push_back(stoi(word));
                    word.clear();
                }
            }
        }
    }
	else
		cout << "Error opening file !\n";
	inFile.close();


    randomize(vertices, adj_list, size);

    //&adj_list[3]

    //cout << "\nAdjacency Lists : \n";
    //printGraph(adj_list, size);
}
