#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

// Implementation based on slides at:
// https://www.cs.cmu.edu/~motionplanning/lecture/AppH-astar-dstar_howie.pdf

struct Position{
  Position() = default;
  Position(int row, int col) : r(row), c(col){}
  int r; //row
  int c; //col
  int g;

  Position* parent{nullptr};  
    
  bool operator == (const Position& other)
  {
      return (r == other.r && c == other.c);
  }
    
    
  friend std::ostream& operator << (std::ostream& o, const Position& p)
  {
    o << p.r << ", " << p.c;
    return o; 
  }
};

struct Comp
{
    Comp(Position& dest) : dest_(dest){}
    Position dest_;
    
    bool operator()(const Position& p1, const Position& p2)
    {
        const int h_p1 = std::abs(p1.r - dest_.r) + std::abs(p1.c - dest_.c);
        const int h_p2 = std::abs(p2.r - dest_.r) + std::abs(p2.c - dest_.c);

        const int f_p1 = p1.g + h_p1;
        const int f_p2 = p2.g + h_p2;

        return f_p1 > f_p2; //lower f-score should have higher priority       
    }
};

void readInput(Position& pcmanPos, Position& foodPos, Position& boardSize, std::vector<std::string>& board)
{
    std::cin >> pcmanPos.r;
    std::cin >> std::ws;
    std::cin >> pcmanPos.c;

    
    std::cin >> std::ws;
    std::cin >> foodPos.r;
    std::cin >> std::ws;
    std::cin >> foodPos.c;
    std::cin >> std::ws;
    
    std::cin >> boardSize.r;
    std::cin >> std::ws;
    std::cin >> boardSize.c;
    std::cin >> std::ws;
    
    
    for(int row = 0; row < boardSize.r; ++row)
    {
        std::string boardRow{};
        std::getline(std::cin, boardRow);
        board.push_back(boardRow);        
    }
    
}

void addToOpenListOrUpdateParent(Position& childNode,
                                std::priority_queue<Position, std::vector<Position>, Comp>& open, 
                                Position* parent,
                                Position foodPos,
                                const std::vector<std::string>& board)
{
    std::priority_queue<Position, std::vector<Position>, Comp> openCopy{foodPos};
    const char wallCharInBoard = '%';

    if(open.empty())
    {
        childNode.parent = parent;
        if(board[childNode.r][childNode.c] != wallCharInBoard)
        {
            childNode.g = parent->g+1;
            openCopy.push(childNode);
        }
    }
    else
    {
        bool childNodeInOpenList = false;
        while(!open.empty())
        {
            Position nodeInOpenList = open.top();
            open.pop();
            if(nodeInOpenList == childNode)
            {
                childNodeInOpenList = true;

                //update parent conditionally
                if(nodeInOpenList.g+1 > parent->g+1)
                {
                    nodeInOpenList.parent = parent;
                    nodeInOpenList.g = parent->g + 1;
                }
            }
            openCopy.push(nodeInOpenList);
        }

        if(!childNodeInOpenList)
        {
            childNode.parent = parent;
            if(board[childNode.r][childNode.c]!=wallCharInBoard)
            {
                childNode.g = parent->g+1;
                openCopy.push(childNode);
            }
        }
    
    }
    open = openCopy;
}
    
bool isNodeInList(Position& pos, std::vector<Position*>& closed)
{
    for(Position* p : closed)
    {
        if((*p) == pos)
            return true;
    }
    return false;
}
    
Position* findFood(std::priority_queue<Position, std::vector<Position>, Comp>& open, 
             std::vector<Position*>& closed, 
             const std::vector<string>& board,
             const Position& foodPos)
{
    int nRows = board.size();
    int nCols = board[0].size();
    
    while(!open.empty())
    {
        Position* bestOpenNode = new Position(open.top());
        open.pop();
        closed.push_back(bestOpenNode);
        
        if((*bestOpenNode) == foodPos)
            return bestOpenNode;
        
        if(bestOpenNode->r-1 >= 0)//up
        {
          Position up(bestOpenNode->r-1, bestOpenNode->c); 
          if(!isNodeInList(up, closed))
              addToOpenListOrUpdateParent(up, open, bestOpenNode, foodPos, board);
        }

        if(bestOpenNode->c -1 >= 0)//left
        {
          Position left(bestOpenNode->r, bestOpenNode->c-1);
          if(!isNodeInList(left, closed))
              addToOpenListOrUpdateParent(left, open, bestOpenNode, foodPos, board);
        }

        if(bestOpenNode->c + 1 < nCols)//right
        {
          Position right(bestOpenNode->r, bestOpenNode->c+1);
          if(!isNodeInList(right, closed))
              addToOpenListOrUpdateParent(right, open, bestOpenNode, foodPos, board);              
        }

        if(bestOpenNode->r + 1 < nRows)//down
        {
          Position down(bestOpenNode->r+1, bestOpenNode->c);
          if(!isNodeInList(down, closed))
              addToOpenListOrUpdateParent(down, open, bestOpenNode, foodPos, board);              
        }
    }
    
    return nullptr;
}



int main(void) {
    /*Read input from STDIN. Print output to STDOUT */
    /*Or pipe in input from a file : cat wellKnownAlgorithms/astarInput.txt | ./a.exe > astaroutput.txt*/
    Position pcmanPos, foodPos, boardSize;
    std::vector<string> board;
    readInput(pcmanPos, foodPos, boardSize, board);

    
    pcmanPos.g = 0; //set traversed cost of starting position to zero

    // positions should be prioritised in the open list according to <traversed cost> + <heuristic = distance from goal>
    std::priority_queue<Position, std::vector<Position>, Comp> open{foodPos};
    open.push(pcmanPos);
    std::vector<Position*> closed;
    
    Position* result = findFood(open, closed, board, foodPos); 

    if(result == nullptr)
    {
        std::cout << "No path found!" << std::endl;
    }
    else
    {
        while(result != nullptr)
        {
            int row = result->r;
            int col = result->c;
            board[row][col] = '@';
            result = result->parent;
        }
    }
    
    for(const auto& row : board)
        std::cout << row << std::endl;
    
    return 0;
}