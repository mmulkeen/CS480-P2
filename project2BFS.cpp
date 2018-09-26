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
  
  vector<Node> Pointers;
  queue<Node> Queue;

  Node start;

  cout << "before loop\n";
  
  for( int i = 0; i < permutation.size(); i++ ) {
    cout << "iteration step: " << i << endl;
    cout << "perm[i] " << permutation[i] << endl;
    start.key.push_back( permutation[i] );
  }

  cout << "after loop\n";
  

  start.parent = -1;

  Pointers.push_back( start );

  start.parent = 0;
  
  Queue.push( start );

  cout << "made it\n";
  
  while( ! Queue.empty() ) {

    
    Node currentNode = Queue.front();
    Queue.pop();

    if( isValid( currentNode.key ) ) {
      //printOutput( Pointers, currentNode.parent );
      return;
    }

    vector<vector<int>> children = findChildren( currentNode.key );

    cout << "done getting children\n";

    for( int j = 0; j < children.size(); j++ ) {
      cout << "child " << j << ' ';
      for( int k = 0; k < children[j].size(); k++ ) {
	cout << children[j][k] << ' ';
      }
      cout << endl;
      
    }
    
    for( auto child = children.begin(); child != children.end(); ++child ) {

      Node tmp;
      tmp.key = *child;
      tmp.parent = currentNode.parent;

      Pointers.push_back( tmp );

      Node tmp2;
      tmp2.key = *child;
      tmp2.parent = Pointers.size() -1;
      cout << "before queue push\n";
      Queue.push( tmp2 );
      cout << "after queue push\n";
      
    }
    
    

  }
  
}

vector<vector<int>> findChildren( vector<int> state ) {

  vector<vector<int>> children;

  int i = 1;

  int count = 0;
  
  while( i < state.size() ) {
    
    for(int j = 0; j < state.size() - i; j++ ) {
      count++;
      children.push_back(reverse(state, j, j+i));
	
      i += 1;
    }
  }

  cout << "total children found is " << count << endl;
  for( int j = 0; j < children.size(); j++ ) {
      cout << "child " << j << ' ';
      for( int k = 0; k < children[j].size(); k++ ) {
        cout << children[j][k] << ' ';
      }
      cout << endl;

    }
  cout << "end find children\n";

  
  return children;
  
  
}

vector<int> reverse ( vector<int> child, int start, int end ) {

  vector<int> newA;

  for( int i = 0; i < child.size(); i++ )
    newA.push_back( child[i] );

  cout << "in reverse\n";


  end -= start;

  if( end % 2 == 0 )
    end /= 2;
  else
    end = end/2 + 1;

  cout << "end = " << end << endl;
  
  for( int i = 0; i < end; i++  ) {

    cout << "iteration " << i << endl;
    
    int tmp = newA[start+i];

    cout << "after tmep\n";
    
    newA[start + i] = newA[start - i];
    cout << "after first equal\n";
    newA[start - 1] = tmp;
    cout << "after second\n";
  }

  cout << "reverse values are ";
  for( int i = 0; i < newA.size(); i++ ) {
    cout << newA[i] << ' ';
  }
  cout << endl;
  
  cout << "finished reverse\n";
  
  return newA;

}

bool isValid( vector<int> state ) {

  for( int i = 0; i < state.size() - 1; i++ )
    if( state[i] > state[i+1] )
      return false;


  return true;
    
  
  
}
