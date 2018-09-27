#include <vector>
#include <iostream>
#include <string>
#include <queue>
#include <math.h>
//poop
using namespace std;

void BFS( vector<int> permutation, int n );
vector<vector<int>> findChildren( vector<int*> state );
vector<int> reverse ( vector<int> child, int start, int end );
bool isValid( vector<int> state );

struct Node
{

	vector<int> key;
	int parent;
	Node(vector<int> x, int y){ key = x; parent = y; }
	void PrintNode() { cout << key[0] << endl; }
	vector<int> getKey() { return key; }



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
}

vector<vector<int>> findChildren( vector<int*> state ) {
}

vector<int> reverse ( vector<int> child, int start, int end ) {


}

bool isValid( vector<int> state ) {

  for( int i = 0; i < state.size() - 1; i++ )
    if( state[i] > state[i+1] )
      return false;


  return true;
    
  
  
}
