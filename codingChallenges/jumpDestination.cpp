/*
Given an array of non-negative integers nums, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Determine if you are able to reach the last index.

 

Example 1:

Input: nums = [2,3,1,1,4]
Output: true
Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.
Example 2:

Input: nums = [3,2,1,0,4]
Output: false
Explanation: You will always arrive at index 3 no matter what. Its maximum jump length is 0, which makes it impossible to reach the last index.
 

Constraints:

1 <= nums.length <= 104
0 <= nums[i] <= 105
Accepted
674,889
Submissions
1,886,850
*/


class Solution {
public:
    vector<int> possibleToArriveAt(int pos, vector<int>& nums)
    {
        vector<int> sources;
        for(int i = pos-1; i >= 0; --i)
        {
            if(i + nums[i] >= pos){
                sources.push_back(i);
            }
        }
        return sources;
    }
    
    bool zeroIn(const vector<int>& v)
    {
        for(const auto& el : v)
            if (el == 0)
                return true;
        return false;
    }
    
    bool checkDestination(int dest, vector<int>& nums)
    {
        if(dest==0)
            return true;

        vector<int> sourcesForDest = possibleToArriveAt(dest, nums);
        
        if(sourcesForDest.size() == 0)
            return false;
        
        if(zeroIn(sourcesForDest))
            return true;
        
        for(const int src : sourcesForDest)
        {
            return false || checkDestination(src, nums);
        }
        return false;
    }
    
    bool canJump(vector<int>& nums) {
        int N = nums.size() - 1;
        return checkDestination(N, nums);
    }
};