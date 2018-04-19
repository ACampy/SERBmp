# Code for Breadth-First search and shortest path finder used from: 
# http://eddmann.com/posts/depth-first-search-and-breadth-first-search-in-python/
from random import *

graph = {'A': set(['B', 'E', 'D']), 
         'B': set(['A', 'F', 'C']),
         'C': set(['B', 'G','D']), 
         'D': set(['C', 'H', 'A']), 
         'E': set(['A']), 
         'F': set(['B']), 
         'G': set(['C']), 
         'H': set(['D'])}

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

starting_node = 'A'
ending_node = random_node_One()

#Picks nodes 10 times
for x in range(0, 10):
  print("Starting Node")
  print(starting_node)
  print("Ending Node")
  print(ending_node)
  
  path = shortest_path(graph, starting_node, ending_node)
  
  #HERE GIVE INFORMATION TO ROBOT, PARSE THROUGH NODES
  
  print(path)
  starting_node = ending_node
  ending_node = random_node_One()
  
  print("\n\n")


#Returns "None" when in same spot
#Finds shortest path
#path = shortest_path(graph, 'G', 'F')



#prints randomly selected node
#print(random_node_One())

#prints path
#print(path)

