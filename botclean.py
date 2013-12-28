from Queue import Queue

class Node(object):    
    def __init__(self, posx, posy, value):
        self.x = posx
        self.y = posy
        self.value = value
        self.state = None

    def __repr__(self):
        return self.value

class BreadthFirstSearchMixin(object):
    QUEUED = 0
    EXAMINED = 1
    
    def setup_bfs(self, node):
        ''' Enqueue the root node before starting BFS. '''
        self.q = Queue()
        self.root = node
        self._enqueue(node)

    def _adjacent_nodes_iter(self, node):
        ''' Implement this method to define how to get the list of adjacent nodes. '''
        raise Exception("Missing method implementation: _adjacent_nodes_iter")

    def _enqueue(self, node):
        self.q.put(node)
        node.state = self.QUEUED

    def _dequeue(self):
        node = self.q.get()
        node.state = self.EXAMINED
        return node

    def bfs_iter(self):
        # Make sure we've enqueued the root.
        assert self.root

        while not self.q.empty():
            # Grab a node to inspect.
            node = self._dequeue()
            
            # Examine it to see if that's what you're looking for.
            yield node

            # If not, enqueue adjacent nodes that have not yet been discovered.
            for n in self._adjacent_nodes_iter(node):
                if not n.state in [self.EXAMINED, self.QUEUED]:
                    self._enqueue(n)
    

class Grid(object):
    def __init__(self, grid):
        self.grid = grid

    def __repr__(self):
        return "\n".join([str(i) for i in self.grid]) + "\n"

    def set(self, x, y, value):
        self.grid[x][y] = value

    def get(self, x, y):
        return self.grid[x][y]

    def iter_with_coord(self):
        for x, row in enumerate(self.grid):
            for y, item in enumerate(row):
                yield (x, y, item)


class BFSGrid(Grid, BreadthFirstSearchMixin):
    def __init__(self, grid):
        super(eval(self.__class__.__name__), self).__init__(grid)
        # Convert to a Node type so we can mark it as queued and examined.
        for x, y, value in self.iter_with_coord():
            self.set(x, y, Node(x, y, value))

    def _adjacent_nodes_iter(self, node):
        x = node.x
        y = node.y

        coord_to_try = [
            (x - 1, y - 1),
            (x - 1, y),
            (x - 1, y + 1),
            (x, y - 1),
            (x, y + 1),
            (x + 1, y - 1),
            (x + 1, y),
            (x + 1, y + 1),
            ]

        # Filter out invalid coordinates.
        coord_to_try = [(i, j) for i, j in coord_to_try if i >= 0 and j >= 0]

        for i, j in coord_to_try:
            try:
                yield self.get(i, j)
            except IndexError as _:
                # Invalid node; we must be on a boundary of the grid.
                pass
        

class Bot(object):
    DUST = 'd'

    def __init__(self, posx, posy, board):
        self.x = posx
        self.y = posy
        self.board = BFSGrid(board)

    def _get_direction_from(self, start, end):
        ''' Get the next move if we want to travel from `start` to `end`. '''
        row_diff = start.x - end.x
        col_diff = start.y - end.y
        
        if not row_diff == 0:
            if row_diff > 0:
                move = 'UP'
            else:
                move = 'DOWN'
        elif not col_diff == 0:
            if col_diff > 0:
                move = 'LEFT'
            else:
                move = 'RIGHT'

        return move

    def next_move(self):
        move = None

        # Clean the dust if we're on it.
        current_node = self.board.get(self.x, self.y)
        if current_node.value == self.DUST:
            move = 'CLEAN'

        # Otherwise, go looking for some dust.
        if not move:
            self.board.setup_bfs(current_node)
            for i in self.board.bfs_iter():
                if i.value == self.DUST:
                    move = self._get_direction_from(current_node, i)
                    break

        return move
    
def next_move(posx, posy, board):
    b = Bot(posx, posy, board)
    print b.next_move()

# Tail starts here
if __name__ == "__main__":
    pos = [int(i) for i in raw_input().strip().split()]
    board = [[j for j in raw_input().strip()] for i in range(5)]
    next_move(pos[0], pos[1], board)