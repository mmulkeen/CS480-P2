#include <vector>
#include <iostream>
#include <string>
#include <queue>
//#include <math.h>
#include <algorithm>
#include <time.h>
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

void printOutput( vector<Node> Pointers, int idx );


int main() {

  cout << "Enter a list of numbers: ";
  
  string ary;
  getline(cin, ary);
  vector<int> perm;
  
  

  // Convert string array to int vector
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

  
  for( int i = 0; i < permutation.size(); i++ ) {
    start.key.push_back( permutation[i] );
  }

  time_t tstart = clock();
  

  // Set up base case condition for printing out solution
  start.parent = -1;
  // Push initial state
  Pointers.push_back( start );
  // Set up index for current node
  start.parent = 0;
  
  Queue.push( start );

  int count = 0;

  
  while( ! Queue.empty() ) {

    /*
    cout << endl;
    cout << "Current Queue" << endl;
    
    queue<Node> qtemp = Queue;
    while( ! qtemp.empty() ) {

      Node qnode = qtemp.front();
      qtemp.pop();
      for( int i = 0; i < qnode.key.size(); i++ )
	cout << qnode.key[i] << ' ';
      cout << endl;
    }
    */
    
    
    Node currentNode = Queue.front();
    Queue.pop();

    

    if( isValid( currentNode.key ) ) {
      cout << "we made it\n";
      cout << endl << "Steps:" << endl;
      printOutput( Pointers, currentNode.parent );
      return;
    }

    vector<vector<int>> children = findChildren( currentNode.key );

    /*
    cout << "done getting children\n";

    for( int j = 0; j < children.size(); j++ ) {
      cout << "child " << j << ' ';
      for( int k = 0; k < children[j].size(); k++ ) {
	cout << children[j][k] << ' ';
      }
      cout << endl;
      
    }
    */
    
    
    for( auto child = children.begin(); child != children.end(); ++child ) {

      Node tmp;
      tmp.key = *child;
      tmp.parent = currentNode.parent;

      Pointers.push_back( tmp );

      Node tmp2;
      tmp2.key = *child;
      tmp2.parent = Pointers.size() -1;
      Queue.push( tmp2 );

      count++;
      
      if( isValid( tmp2.key ) ) {
	cout << "we made it\n";
	printf("Time taken: %.5fs\n", (double)(clock() - tstart)/CLOCKS_PER_SEC);
	cout << "Total nodes checked: " << count << endl;
	cout << "steps:\n";
	printOutput( Pointers, tmp2.parent );
	return;
      }
      
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
    }	
    i += 1;
    
  }

  /*
  cout << "total children found is " << count << endl;
  for( int j = 0; j < children.size(); j++ ) {
      cout << "child " << j << ' ';
      for( int k = 0; k < children[j].size(); k++ ) {
        cout << children[j][k] << ' ';
      }
      cout << endl;

    }
  */
  
  return children;
  
  
}

vector<int> reverse ( vector<int> child, int start, int end ) {

  vector<int> newA;

  for( int i = 0; i < child.size(); i++ )
    newA.push_back( child[i] );

  /*
  cout << "parent state ";

  for( int i = 0; i < newA.size(); i++ ) {
    cout << newA[i] << ' ';
  }
  cout << endl;
  cout << "start = " << start << "; end = " << end << endl;
  
  /*
  int mid = start - end;

  if( mid % 2 == 0 )
    mid /= 2;
  else
    mid = mid/2 + 1;

  cout << "mid = " << mid << endl;
  
  
  for( int i = 0; i < mid; i++  ) {
    
    int tmp = newA[start+i];

    newA[start + i] = newA[end - i];
    newA[end - i] = tmp;

  }
  */
  reverse(newA.begin()+start, newA.begin()+end+1);

  /*
  cout << "reverse values are ";
  for( int i = 0; i < newA.size(); i++ ) {
    cout << newA[i] << ' ';
  }
  cout << endl;
  */
  
  return newA;

}

bool isValid( vector<int> state ) {

  for( int i = 0; i < state.size() - 1; i++ )
    if( state[i] > state[i+1] )
      return false;


  return true;
  
  
}


void printOutput( vector<Node> Pointers, int idx ) {

  if( idx == -1 )
    return;

  for( int i = 0; i < Pointers[idx].key.size(); i++ ) {
    cout << Pointers[idx].key[i] << ' ';
  }
  cout << endl;

  printOutput( Pointers, Pointers[idx].parent );

}
