// Example program
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int solution(vector<int> &A) {
    // write your code in C++14 (g++ 6.2.0)
    if (A.size() < 3)
        return 0;

    vector<int> highestBlockToLeft(A.size(), 0);
    vector<int> highestBlockToRight(A.size(), 0);

    int highestToLeft = 0;
    for (size_t i = 1; i < A.size(); ++i)
    {
        if(A[i-1] > highestToLeft)
            highestToLeft = A[i-1];
        highestBlockToLeft[i] = highestToLeft;
    }

    int highestToRight = 0;
    for(int i = A.size()-2; i >= 0; --i)
    {
        if(A[i+1] > highestToRight)
            highestToRight = A[i+1];
        highestBlockToRight[i] = highestToRight;
    }

    int maxDepth = 0;
    for(size_t i = 1; i < A.size(); ++i)
    {
        bool existsHigherBlockToLeft = highestBlockToLeft[i] > A[i];
        bool existsHigherBlockToRight = A[i] < highestBlockToRight[i];

        if(existsHigherBlockToLeft && existsHigherBlockToRight)
        {
            int lowestHigherBlock = std::min(
                                    highestBlockToLeft[i], 
                                    highestBlockToRight[i]
                                    );
            int depthAti = lowestHigherBlock - A[i];
            if(depthAti > maxDepth)
                maxDepth = depthAti;
        }        

    }

    return maxDepth;
}


int main(int argc, char* argv[])
{
    vector<int> A = {1, 3, 2, 1, 2, 1, 5, 3, 3, 4, 2};
    std::cout << solution(A) << std::endl;

    return 0;
}