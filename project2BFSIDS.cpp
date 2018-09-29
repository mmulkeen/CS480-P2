#include <vector>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <algorithm>
#include <time.h>
using namespace std;

void BFS( vector<int> permutation, int n );
bool DFS( vector<int> permutation, int d, int &count );
vector<vector<int>> findChildren( vector<int> state );
vector<int> reverse ( vector<int> child, int start, int end );
bool isValid( vector<int> state );

struct Node
{
  vector<int> key;
  int parent;
};

struct NodeS
{
    vector<int> key;
    int parent;
    int depth;
};

void printOutput( vector<Node> Pointers, int idx );
void printOutput( vector<NodeS> Pointers, int idx );


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

    cout << "BFS\n";
  BFS(perm, perm.size() );
    
    
    
    int depth = 0;
    int IDScount = 0;
    cout << "IDS\n";
    
    time_t tstart = clock();
    
    while( ! DFS(perm, depth++, IDScount) ) {}

    printf("Time taken: %.5fs\n", (double)(clock() - tstart)/CLOCKS_PER_SEC);
    //cout << "total nodes checked: " << IDScount << endl;

  return 0;

}

void BFS( vector<int> permutation, int n ) {
  
  vector<Node> Pointers;
  queue<Node> Queue;
  int max = 0;
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
  max = Queue.size();
  int count = 0;

  
  while( ! Queue.empty() ) {
 
    Node currentNode = Queue.front();
    Queue.pop();
    //cout << "Size of Queue: " << max << endl;    

    if( isValid( currentNode.key ) ) {
      cout << endl << "Steps:" << endl;
      printOutput( Pointers, currentNode.parent );
      cout << "Total nodes checked: " << count << endl;
      cout << "Max size of Queue: " << max << endl;
      printf("Time taken: %.5fs\n", (double)(clock() - tstart)/CLOCKS_PER_SEC);
      return;
    }

    vector<vector<int>> children = findChildren( currentNode.key );    
    for( auto child = children.begin(); child != children.end(); ++child ) {

      Node tmp;
      tmp.key = *child;
      tmp.parent = currentNode.parent;

      Pointers.push_back( tmp );

      Node tmp2;
      tmp2.key = *child;
      tmp2.parent = Pointers.size() -1;
      Queue.push( tmp2 );
      if (Queue.size() > max) {
      	max = Queue.size();
      }
      count++;
      //cout << "Size of Queue: " << max << endl;
      if( isValid( tmp2.key ) ) {
	      /*
	printf("Time taken: %.5fs\n", (double)(clock() - tstart)/CLOCKS_PER_SEC);
	cout << "Total nodes checked: " << count << endl;
	cout << "Max size of Queue: " << max << endl;*/
	cout << "steps:\n";
	printOutput( Pointers, tmp2.parent );
        cout << "Total nodes checked: " << count << endl;
        cout << "Max size of Queue: " << max << endl;
	printf("Time taken: %.5fs\n", (double)(clock() - tstart)/CLOCKS_PER_SEC);
	return;
      } 
    }
  }
}

bool DFS( vector<int> permutation, int d, int &IDScount ) {
    
    vector<NodeS> Pointers;
    stack<NodeS> Stk;
    int max = Stk.size();
    NodeS start;
    
    for( int i = 0; i < permutation.size(); i++ ) {
        start.key.push_back( permutation[i] );
    }
    // Set up base case condition for printing out solution
    start.parent = -1;
    start.depth = 0;
    // Push initial state
    Pointers.push_back( start );
    // Set up index for current node
    start.parent = 0;
    
    
    
    Stk.push( start );
    
    max = Stk.size(); 
    
    while( ! Stk.empty() ) {
        
        
        
        NodeS currentNode = Stk.top();
        Stk.pop();
        
        
        
        if( isValid( currentNode.key ) ) {
            cout << endl << "Steps:" << endl;
	    printOutput( Pointers, currentNode.parent );
	    cout << "Total nodes checked: " << IDScount << endl;
            cout << "Max size of stack: " << max << endl;
	    return true;
        }
        
        if( currentNode.depth < d ) {
           
        
        vector<vector<int>> children = findChildren( currentNode.key );
        
        
        for( auto child = children.begin(); child != children.end(); ++child ) {
            
            NodeS tmp;
            tmp.key = *child;
            tmp.parent = currentNode.parent;
            tmp.depth = currentNode.depth;
            
            Pointers.push_back( tmp );
            
            NodeS tmp2;
            tmp2.key = *child;
            tmp2.parent = Pointers.size() -1;
            tmp2.depth = currentNode.depth+1;
            Stk.push( tmp2 );
            if (Stk.size() > max)
		    max = Stk.size();
            IDScount++;
            //cout << "Size of Queue: " << max << endl;
            if( isValid( tmp2.key ) ) {
		cout << "steps:\n";
                printOutput( Pointers, tmp2.parent );
		cout << "Total nodes checked: " << IDScount << endl;
                cout << "Max size of stack: " << max << endl;
		return true;
            }
            
        }
        }
        
        
    }
    
    return false;
    
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


  
  return children;
  
  
}

vector<int> reverse ( vector<int> child, int start, int end ) {

  vector<int> newA;

  for( int i = 0; i < child.size(); i++ )
    newA.push_back( child[i] );


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

   
  vector<vector<int>> Q;
  
  while( idx != -1 ) {

    Q.push_back(Pointers[idx].key);
    idx = Pointers[idx].parent;
    
  }
  //cout << "Queue Size is: " << Q.size() << endl;
  vector<int> it;
  for ( int i = Q.size()-1; i >= 0; i--) {
    it = Q[i];
    for ( int j = 0; j < it.size(); j++) {
    	cout<< it[j] << ' ';
    }
    cout << endl;
  }
  //printOutput( Pointers, Pointers[idx].parent );

}

void printOutput( vector<NodeS> Pointers, int idx ) {
   
  vector<vector<int>> Q;

  while( idx != -1 ) {

    Q.push_back(Pointers[idx].key);
    idx = Pointers[idx].parent;

  }
  //cout << "Queue Size is: " << Q.size() << endl;
  vector<int> it;
  for ( int i = Q.size()-1; i >= 0; i--) {
    it = Q[i];
    for ( int j = 0; j < it.size(); j++) {
        cout<< it[j] << ' ';
    }
    cout << endl;
  }
}
	
	
	
	/* 
    if( idx == -1 )
        return;
    
    for( int i = 0; i < Pointers[idx].key.size(); i++ ) {
        cout << Pointers[idx].key[i] << ' ';
    }
    cout << endl;
    
    printOutput( Pointers, Pointers[idx].parent );
    */

