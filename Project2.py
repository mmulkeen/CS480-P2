import collections
import math
import queue

def BFS(state):


    array = []
    array.append([state, -1])
    q = queue.Queue()
    q.put([state, len(array)-1])
    visited = []
    visited.append(state)
    while q:
        node = q.get()
        if Valid(node[0]):
            return node[0]

        children = findChildren(node[0])

        for child in children:

            if child != node[0]:
                array.append([child, node[1]])
                q.put([child, len(array) - 1])
                visited.append(child)




def findChildren(state):

    children = []

    i = 1

    while i < len(state):

        for j in range(len(state) - i):
            temp = reverse(state, j, j+i)
            if state != temp:
                children += [reverse(state, j, j+i)]

        i += 1

    return children


def reverse(state, start, end):

    new = []

    for num in state:
        new.append(num)

    for i in range( math.ceil( (end-start)/2 ) ):

        new[start + i], new[end - i] = new[end - i], new[start + i]




    return new

def Valid(state):


    for i in range( len(state) -1 ):

        if( state[i] > state[i+1] ):
            return False

    print("we got it")

    return True



def IDS(state, depth):

    print()



def main():

    state = input("Enter an input permutation P: ")

    try:
        state = [int(i) for i in state.split(" ")]
    except ValueError:
        print("You messed up")
        return


    print(state)

    final = BFS(state)

    print(final)

    #IDS(perm, 0)


main()