/*
Given an integer array nums, return all the different possible increasing subsequences of the given array with at least two elements. You may return the answer in any order.

The given array may contain duplicates, and two equal integers should also be considered a special case of increasing sequence.

 

Example 1:

Input: nums = [4,6,7,7]
Output: [[4,6],[4,6,7],[4,6,7,7],[4,7],[4,7,7],[6,7],[6,7,7],[7,7]]
Example 2:

Input: nums = [4,4,3,2,1]
Output: [[4,4]]
 

Constraints:

1 <= nums.length <= 15
-100 <= nums[i] <= 100
Accepted
60,596
Submissions
124,684
*/

class Solution {
public:
    
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        vector<vector<int>> prevSequences;
        set<vector<int>> uniqueSequences;
        
        for (int i = 1; i < nums.size(); ++i)
        {
            auto prevSequencesCopy = prevSequences;
            for(vector<int> sequence : prevSequences)
            {
                if(nums[i] >= sequence.back())
                {
                    sequence.push_back(nums[i]);
                    const auto insertionResult = uniqueSequences.insert(sequence);
                    if(insertionResult.second == true)
                        prevSequencesCopy.push_back(sequence);
                }
            }
            prevSequences = prevSequencesCopy;
            
            
            for(int j = 0; j < i; ++j)
            {
                if(nums[i] >= nums[j]){
                    vector<int> newSequence{nums[j], nums[i]};
                    const auto insertionResult = uniqueSequences.insert(newSequence);
                    if(insertionResult.second == true)
                        prevSequences.push_back(newSequence);
                }
            }
        }
    
        return prevSequences;
    }
};