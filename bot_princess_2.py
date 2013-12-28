# https://www.hackerrank.com/challenges/saveprincess2

def nextMove(n,r,c,grid):    
    g = Grid(n, grid)
    g.bot_coord = (r, c)
    g.get_princess_coordinates()

    return g.next_move()

class Grid(object):
    def __init__(self, n, grid):
        self.n = n
        self.matrix = grid
        self.errors = []
        self.princess_marker = 'p'
        self.bot_marker = 'm'
        self.princess_coord = None
        self.bot_coord = None

    def get_coordinates_for(self, val):
        for x, row in enumerate(self.matrix):
            for y, col in enumerate(row):
                if col == val:
                    return (x, y)

    def get_princess_coordinates(self):
        if not self.princess_coord:
            self.princess_coord = self.get_coordinates_for(self.princess_marker)
        return self.princess_coord

    def get_bot_coordinates(self):
        if not self.bot_coord:
            self.bot_coord = self.get_coordinates_for(self.bot_marker)
        return self.bot_coord

    def next_move(self):
        move = None
        row_diff = self.bot_coord[0] - self.princess_coord[0]
        col_diff = self.bot_coord[1] - self.princess_coord[1]
        
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

if __name__ == '__main__':
    # Tail starts here
    n = input()
    r,c = [int(i) for i in raw_input().strip().split()]
    grid = []
    
    for i in xrange(0, n): grid.append(raw_input())
    
    print nextMove(n,r,c,grid)