from enum import Enum

class SearchType(Enum):
    BreadthFirst=1
    DepthFirst=2

class Node:
    """
    Dummy class for descriptive purposes
    """
    pass

class GraphSearch:
    """
    Depthfirst/breadth first traversal utility
    """

    def __init__(self, init_queue : list[Node],
                       search_type : SearchType = SearchType.DepthFirst):
        self.queue = init_queue
        self.search_type = search_type
        self.i = 0
        self.terminated = False

    def early_stop(self):
        return False

    def next(self, node : Node):
        return []

    def iteration(self):
        self.i+=1

        if self.search_type == SearchType.DepthFirst:
            node = self.queue.pop()
        else:
            node = self.queue.pop(0)

        self.queue += self.next(node)

    def iterate(self, N):
        for i in range(N):
            if not self.early_stop():
                self.iteration()
            else:
                self.terminated=True
                return

    def full_search(self):
        while len(self.queue)>0 and not self.early_stop():
            self.iteration()

class FullLevels(GraphSearch):
    """
    Breadth first, with all equal depth nodes processed at once
    """

    def iteration(self):
        self.i+=1
        self.layer_sizes .append(len(self.queue))

        new_queue = []

        while len(self.queue)>0:
                node = self.queue.pop()
                new_queue += self.next(node)

        self.queue = new_queue


if __name__=="__main__":

    class BTN(Node):
        """Binary Tree Node"""

        def __init__(self, data, left=None, right=None):
            self.data = data
            self.left = left
            self.right = right

    class BTNT(GraphSearch):

        def __init__(self, root, **kwargs):
            self.root = root
            super().__init__([root], **kwargs)
        
        def next(self, node):
            print(node.data)
            neighbours = []
            if node.left is not None:
                neighbours.append(node.left)
            if node.right is not None:
                neighbours.append(node.right)
            return neighbours

    root = BTN(1)
    root.left = BTN(2); root.right = BTN(3)
    root.left.left = BTN(4); root.left.right = BTN(5)
    root.right.left = BTN(6); root.right.right = BTN(7)

    btnt = BTNT(root)
    btnt.full_search()
    print()

    btnt = BTNT(root, search_type=SearchType.BreadthFirst)
    btnt.full_search()

