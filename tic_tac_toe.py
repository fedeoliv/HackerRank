# https://www.hackerrank.com/challenges/tic-tac-toe

import copy, sys

class Board(object):
    MARK_EMTPY = '_'
    WINNING_MOVES = (
        ((0,0),(0,1),(0,2)), ((1,0),(1,1),(1,2)), ((2,0),(2,1),(2,2)),
        ((0,0),(1,0),(2,0)), ((0,1),(1,1),(2,1)), ((0,2),(1,2),(2,2)),
        ((0,0),(1,1),(2,2)), ((0,2),(1,1),(2,0))
    )

    def __init__(self, player, squares):
        self.squares = squares
        self.moves = []

    def is_empty(self):
        for row in self.squares:
            if any(('X' in row, 'O' in row)):
                return False
        return True

    def dump(self):
        for row in self.squares:
            print ''.join(row)


    def score(self, is_max_player):
        for w in Board.WINNING_MOVES:
            winner = list(self.squares[coord[0]][coord[1]] for coord in w)
            if '_' not in winner and _thesame(winner):
                return 1 if winner[0] == ('X' if is_max_player else 'O') else -1

        for row in self.squares:
            if '_' in row:
                return None

        return 0

    def possible_children(self, is_max_player=True):
        for i in range(0,3):
            for j in range(0,3):
                if self.squares[i][j] == Board.MARK_EMTPY:
                    child = copy.deepcopy(self)
                    child.make_move((i,j), is_max_player)
                    yield child

    def make_move(self, move, is_max_player):
        self.moves.append(move)
        i,j = move
        self.squares[i][j] = 'X' if is_max_player else 'O'


    def negamax(self, depth, is_max_player, weight=1.0):
        best, chosen = -sys.maxint-1, None

        score = self.score(is_max_player)
        if depth == 0:
            score = 0
        if score is not None:
            return score, self.moves[0]

        for cur in self.possible_children(is_max_player):
            score, move = cur.negamax(depth - 1,not is_max_player, weight/2.0)
            score = -score*weight
            if score > best:
                best,chosen = score, move

        return best,chosen

    def next_move(self, is_max_player):
        _, move = self.negamax(10, is_max_player)
        return move


def _thesame(items):
    return len(set(items)) == 1

if __name__ == "__main__":
    #If player is X, I'm the first player.
    #If player is O, I'm the second player.
    player = raw_input()
    
    #Read the board now. The board is a 3x3 array filled with X, O or _.
    squares = []
    
    for i in xrange(0, 3):
        squares.append(list(raw_input()))
    
    board = Board(player,squares)
    if board.is_empty():
        print '1 1'
    else:
        move = board.next_move(player == 'X')
        print ' '.join(map(str, move))