graph = {'A': set(['B', 'E', 'D']), 
         'B': set(['A', 'F', 'C']),
         'C': set(['B', 'G','D']), 
         'D': set(['C', 'H', 'A']), 
         'E': set(['A']), 
         'F': set(['B']), 
         'G': set(['C']), 
         'H': set(['D'])}

def bfs_paths(graph, start, goal):
  queue = [(start, [start])]
  while queue:
    (vertex, path) = queue.pop(0)
    for next in graph[vertex] - set(path):
      if next == goal:
        yield path + [next]
      else:
        queue.append((next, path + [next]))

def shortest_path(graph, start, goal):
  try:
    return next(bfs_paths(graph, start, goal))
  except StopIteration:
    return None

#Finds shortest path
path = shortest_path(graph, 'G', 'F')

print(path)
#Finds all possible paths
#print(list(bfs_paths(graph, 'A', 'F')))

