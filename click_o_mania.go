// https://www.hackerrank.com/challenges/click-o-mania

package main

import (
        "fmt"
        "bufio"
        "time"
        "os"
        "io"
        "strings"
)

type Pos struct {
        x int
        y int
}

func (p * Pos) Print() {
        fmt.Println(p.y, p.x)
}

type World [][]uint8

var neighbors = [4]Pos{
        Pos{-1, 0},
        Pos{ 1, 0},
        Pos{ 0,-1},
        Pos{ 0, 1},
}

func readWorld(stream io.Reader) World {
        reader := bufio.NewReader(stream)
        _, err := reader.ReadString('\n')
        if err != nil { panic(err) }

        eof := false
        cells := make([][]uint8, 0)
        for !eof {
                line, err := reader.ReadString('\n')
                line = strings.TrimSpace(line)
                if err == io.EOF {
                        eof = true
                        if len(line) == 0 {
                                break
                        }
                } else if err != nil {
                        panic(err)
                }
                row := make([]uint8, len(line))
                cells = append(cells, row)
                for x, char := range line {
                        row[x] = uint8(char)
                }
        }
        return cells
}

type Group []Pos

func (w World) ComputeGroups() (groups []Group) {
        groups = make([]Group, 0)
        closedCells := NewWorld(len(w[0]), len(w))
        for y, row := range(w) {
                for x, c := range(row) {
                        if c == '-' || closedCells[y][x] == 1 {
                                continue
                        }
                        g := Group{}
                        openNodes := []Pos{ Pos{x, y} }
                        for len(openNodes) > 0 {
                                // pop openNodes
                                n := openNodes[len(openNodes) - 1]
                                openNodes = openNodes[:len(openNodes) - 1]
                                nodeChar := w[n.y][n.x]
                                if nodeChar == c {
                                        closedCells[n.y][n.x] = 1
                                        g = append(g, n)
                                        // add neighbors to open nodes
                                        for _, p := range(neighbors) {
                                                x2 := n.x + p.x
                                                y2 := n.y + p.y
                                                if x2 >= 0 && x2 < len(row) && y2 >=0 && y2 < len(w) && closedCells[y2][x2] == 0 {
                                                        openNodes = append(openNodes, Pos{x2, y2})
                                                }
                                        }
                                }
                        }
                        groups = append(groups, g)
                }
        }
        return groups
}

type Score struct {
        gameOver bool
        cellsLeft int
}

func (w World) ComputeScore(groups []Group) (score Score) {
        // check if game over
        score.gameOver = true
        for _, g := range(groups) {
                score.cellsLeft += len(g)
                if len(g) >= 2 {
                        score.gameOver = false
                }
        }
        return score
}

func (w World) ComputeBestMove(lookLimit int) (Group, int) {
        groups := w.ComputeGroups()

        // if the game is over, just return the score
        score := w.ComputeScore(groups)
        if score.gameOver {
                return nil, score.cellsLeft
        }
        // shucks, out of time
        if timeOver() && lookLimit <= -3 {
                return nil, score.cellsLeft
        }

        // for each move, compute score for next move
        bestScore := -1 // lower is better and -1 is a special-case
        var bestMove Group
        for _, g := range(groups) {
                if len(g) < 2 {
                        continue
                }
                w2 := w.Step(g, groups)
                _, moveScore := w2.ComputeBestMove(lookLimit - 1)
                if bestScore == -1 || moveScore < bestScore {
                        bestScore = moveScore
                        bestMove = g
                }
                if bestScore == 0 {
                        break
                }
        }

        return bestMove, bestScore
}

func (w World) Step(move Group, groups []Group) (nw World) {
        nw = w.Clone()
        // step 1, remove all the cells from the group
        for _, p := range(move) {
                nw[p.y][p.x] = '-'
        }
        // step 2, shift cells down
        for x := 0; x < len(nw[0]); x++ {
                for y := len(nw) - 1; y >= 1; y-- {
                        if nw[y][x] == '-' {
                                for y2 := y - 1; y2 >= 0; y2-- {
                                        if nw[y2][x] != '-' {
                                                // swap
                                                tmp := nw[y2][x]
                                                nw[y2][x] = nw[y][x]
                                                nw[y][x] = tmp
                                                break
                                        }
                                }
                        }
                }
        }
        // step 3, shift cells left
        for x := 0; x < len(nw[0]) - 1; x++ {
                emptyColumn := true
                for y := 0; y < len(nw); y++ {
                        if nw[y][x] != '-' {
                                emptyColumn = false
                                break
                        }
                }
                if emptyColumn {
                        anythingMoved := false
                        for y2 := 0; y2 < len(nw); y2++ {
                                for x2 := x; x2 < len(nw[0]) - 1; x2++ {
                                        nw[y2][x2] = nw[y2][x2 + 1]
                                        if nw[y2][x2] != '-' {
                                                anythingMoved = true
                                        }
                                }
                                nw[y2][len(nw[0]) - 1] = '-'
                        }
                        if anythingMoved {
                                // check the same column again
                                x--;
                        }
                }
        }
        return nw
}

func (w World) Clone() (nw World) {
        nw = NewWorld(len(w[0]), len(w))
        for y, row := range(w) {
                for x, c := range(row) {
                        nw[y][x] = c
                }
        }
        return nw
}

func (w World) Print() {
        for _, row := range(w) {
                for _, c := range(row) {
                        fmt.Printf("%c", c)
                }
                fmt.Print("\n")
        }
}

func NewWorld(width, height int) (w World) {
        w = make([][]uint8, height)
        for y := range(w) {
                w[y] = make([]uint8, width)
        }
        return w
}

var startTime = time.Now()
const timeLimit = float64(3) //float64(5.0)

func timeOver() bool {
        timePassed := time.Since(startTime)
        return timePassed.Seconds() >= timeLimit
}

func main () {
        w := readWorld(os.Stdin)
        move, _ := w.ComputeBestMove(0)
        move[0].Print()
}