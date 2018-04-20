# Code for Breadth-First search and shortest path finder used from: 
# http://eddmann.com/posts/depth-first-search-and-breadth-first-search-in-python/

# Code for Queue Class from:
# http://interactivepython.org/runestone/static/pythonds/BasicDS/ImplementingaQueueinPython.html

from random import *

graph = {'A': set(['B', 'E', 'D']), 
         'B': set(['A', 'F', 'C']),
         'C': set(['B', 'G','D']), 
         'D': set(['C', 'H', 'A']), 
         'E': set(['A']), 
         'F': set(['B']), 
         'G': set(['C']), 
         'H': set(['D'])}

class Queue:
    def __init__(self):
        self.items = []

    def isEmpty(self):
        return self.items == []

    def enqueue(self, item):
        self.items.insert(0,item)

    def dequeue(self):
        return self.items.pop()

    def size(self):
        return len(self.items)

#Selects random node from graph list  
def random_node_One():
  random_node = sample(graph,  1)
  return random_node[0] 

#Breadth-First Search
def bfs_paths(graph, start, goal):
  queue = [(start, [start])]
  while queue:
    (vertex, path) = queue.pop(0)
    for next in graph[vertex] - set(path):
      if next == goal:
        yield path + [next]
      else:
        queue.append((next, path + [next]))

#Finds shortest path
def shortest_path(graph, start, goal):
  try:
    return next(bfs_paths(graph, start, goal))
  except StopIteration:
    return None

#Converts Path into Motion Queue THEPROJECT.PY
def motionPlan(path):
  q1 = Queue()
  for node in range(0,len(path)-1):
    # print (node)
    cur = path[node]
    nex = path[node + 1]
    # print (cur, nex)

    #Inner to Outer
    if ((cur == 'E' and nex == 'A') or 
      (cur == 'F' and nex == 'B') or 
      (cur == 'G' and nex == 'C') or 
      (cur == 'H' and nex == 'D')):
        
        q1.enqueue(2)
        q1.enqueue(0)

    #Outer too Inner
    elif ((cur == 'A' and nex == 'E') or 
      (cur == 'B' and nex == 'F') or 
      (cur == 'C' and nex == 'G') or 
      (cur == 'D' and nex == 'H')):

        q1.enqueue(1)
        q1.enqueue(0)
    
    #Clockwise
    elif ((cur == 'A' and nex == 'B') or 
      (cur == 'B' and nex == 'C') or 
      (cur == 'C' and nex == 'D') or 
      (cur == 'D' and nex == 'A')):

        q1.enqueue(3)
        q1.enqueue(1)
        q1.enqueue(4)
        q1.enqueue(0)

    #Counter-Clockwise
    elif ((cur == 'B' and nex == 'A') or 
      (cur == 'C' and nex == 'B') or 
      (cur == 'D' and nex == 'C') or 
      (cur == 'A' and nex == 'D')):

        q1.enqueue(4)
        q1.enqueue(1)
        q1.enqueue(3)
        q1.enqueue(0)

    #Default
    else :
      q1.enqueue(0)
    #end For loop
  return q1


starting_node = 'E'
ending_node = random_node_One()

#Picks nodes 1 times
for x in range(0, 1):
  print("Starting Node")
  print(starting_node)
  print("Ending Node")
  print(ending_node)
  

  #Valid path check (Start /= End)
  path = shortest_path(graph, starting_node, ending_node)
  while(True):
    #HERE GIVE INFORMATION TO ROBOT, PARSE THROUGH NODES
    # print (len(path))
    if not path:
      ending_node = random_node_One()
      path = shortest_path(graph, starting_node, ending_node)
      print("Empty Path")
      print("Starting Node")
      print(starting_node)
      print("Ending Node")
      print(ending_node)
    else:
      break

  #create Queue for Arduino
  q2 = Queue()
  q2 = motionPlan(path)   

  # print(path)
  starting_node = ending_node
  ending_node = random_node_One()
  
  motionPlan(path)
  print("\n\n")

  #for for printing queue
  for stuff in range (0, q2.size()):
    print(q2.dequeue())

#Returns "None" when in same spot
#Finds shortest path
#path = shortest_path(graph, 'G', 'F')



#prints randomly selected node
#print(random_node_One())

#prints path
#print(path)

