class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int index = 0;
        for (int i = 0; i < nums.size(); ++i)
        {
            int prev = i-1 >= 0 ? nums[i-1] : std::numeric_limits<int>::min();
            int next = i+1 < nums.size() ? nums[i+1] : std::numeric_limits<int>::min();
            if(prev < nums[i] && nums[i] > next)
            {
                index = i;
                break;
            }
        }
        
        return index;
    }
};