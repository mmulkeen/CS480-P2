#include <vector>
#include <iostream>
#include <string>
#include <queue>
#include <math.h>
using namespace std;

void BFS( vector<int> permutation, int n );
vector<vector<int>> findChildren( vector<int> state );
vector<int> reverse ( vector<int> child, int start, int end );
bool isValid( vector<int> state );

struct Node
{
  vector<int> key;
  int parent;
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
  
  vector<Node*> Pointers;
  queue<Node*> Queue;

  Node *start;

  for( int i = 0; i < permutation.size(); i++ ) {
    start->key.push_back( permutation[i] );
  }

  start->parent = -1;

  Pointers.push_back( start );

  start->parent = 0;
  
  Queue.push( start );

  while( ! Queue.empty() ) {

    
    Node *currentNode = Queue.front();
    Queue.pop();

    if( isValid( currentNode->key ) ) {
      //printOutput( Pointers, currentNode.parent );
      return;
    }

    vector<vector<int>> children = findChildren( currentNode->key );

    for( auto child = children.begin(); child != children.end(); ++child ) {

      Node *tmp;
      tmp->key = *child;
      tmp->parent = currentNode->parent;

      Pointers.push_back( tmp );

      Node *tmp2;
      tmp2->key = *child;
      tmp2->parent = Pointers.size() -1;
      Queue.push( tmp2 );
      
    }
    


  }
  
}

vector<vector<int>> findChildren( vector<int> state ) {

  vector<vector<int>> children;

  int i = 1;

  while( i < state.size() ) {
    
    for(int j = 0; j < state.size() - i; j++ ) {
    
      children.push_back(reverse(state, j, j+i));
	
      i += 1;
    }
  }

  return children;
  
  
}

vector<int> reverse ( vector<int> child, int start, int end ) {

  vector<int> newA;


  for( int i = 0; i < (int)ceil( (end-start)/2.0); i++  ) {

    int tmp = newA[start+i];

    newA[start + i] = newA[start - i];
    newA[start - 1] = tmp;
  }
      
  return newA;

}

bool isValid( vector<int> state ) {

  for( int i = 0; i < state.size() - 1; i++ )
    if( state[i] > state[i+1] )
      return false;


  return true;
    
  
  
}
