#include <vector>
#include <iostream>
#include <string>
#include <queue>
#include <math.h>
#include <algorithm>
//poop
using namespace std;

void BFS( vector<int> permutation, int n );
vector<vector<int>> findChildren( vector<int> state );
//vector<int> reverse ( vector<int> child, int start, int end );
bool isValid( vector<int> state );

struct Node
{
	vector<int> key;
	int parent;
	Node(vector<int> x, int y){ key = x; parent = y; }
	void PrintNode() { 
       		for (int i = 0; i < key.size(); i++)
			cout<< key[i]<< ' ';
		cout<< endl;
	
	}
	vector<int> getKey() { return key; }
	void SetParent(int x) {
		parent = x;
	}
	void Setkey(vector<int> x) {
		key = x;
	}
};
int main() {	
	cout << "Enter a list of numbers: ";
	string ary;
	getline(cin, ary);
	vector<int> perm;
	string tmp;
	for( int i = 0; i < ary.length(); i++) {
		if( ary[i] == ' ' ) {
			perm.push_back( stoi(tmp) );
			tmp = "";
		}
		tmp += ary[i];
	}
	perm.push_back( stoi(tmp) );
	BFS(perm, perm.size() );
	return 0;
}
void BFS( vector<int> permutation, int n ) {
  	vector<Node*>Pointers;
	queue<Node*> Queue;
	Node* start = new Node(permutation, -1);
	Node* temp = start;
	start->PrintNode();
	Pointers.push_back(start);
	start->SetParent(0);
	Queue.push(start);
	while ( !Queue.empty()){
		Node *currentNode = Queue.front();
		Queue.pop();
		if (isValid(currentNode->key)) {
			cout << "we got it" << endl;
			currentNode->PrintNode();
			return;
		}
		vector<vector<int>> children;
		for ( int i = 0; i < currentNode->key.size(); i++) {
                	for ( int j = i+1; j <= currentNode->key.size(); j++) {
                        	vector<int> temp = currentNode->key;
                        	reverse(temp.begin()+i, temp.begin()+j);
                        	if (temp != currentNode->key){
                                	if (isValid(temp)) {
                        			cout << "we got it" << endl;
                        			currentNode->Setkey(temp);
						currentNode->PrintNode();
                        			return;
                			}

					children.push_back( temp );
				}
                	}
        	}

		for (auto child : children) {
			if ( child != currentNode->key){
				Node* tmp = new Node(child, currentNode->parent);
				Pointers.push_back( tmp );
				tmp->SetParent( Pointers.size()-1);
				Queue.push( tmp );
					
			}
		}
	}
}

vector<vector<int>> findChildren( vector<int> state ) {
	vector<vector<int>> children;
	for ( int i = 0; i < state.size(); i++) {
		for ( int j = i+1; j <=	state.size(); j++) {
			vector<int> temp = state;
			reverse(temp.begin()+i, temp.begin()+j);
			if (temp != state)
				children.push_back( temp );
		}
	}
	/*
	for ( int i = 0; i < children.size(); i++){
		cout << i << ". "<< "First child: "; 
		for ( int j = 0; j < state.size(); j++){
			cout << children[i][j] << ' ';
	
		}
		cout << endl;
	}
	*/
	return children; 
}

bool isValid( vector<int> state ) {

  for( int i = 0; i < state.size() - 1; i++ )
    if( state[i] > state[i+1] )
      return false;


  return true;
    
  
  
}
