class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        std::map<int, vector<int>> numsMap;
        for(int i = 0; i < nums.size(); ++i)
        {
            int elem = nums[i];
            if (numsMap.find(elem) != numsMap.end())
            {
                numsMap[elem] = {i};
            }
            else
            {
                numsMap[elem].push_back(i);
            }
        }
        
        vector<int> ret{-1, -1};
        
        for (int i = 0; i < nums.size(); ++i)
        {
            int elem = nums[i];
            int looking_for = target-elem;
         
            const auto searchResult = numsMap.find(looking_for);
            if(searchResult != numsMap.end())
            {
                const auto& locations = searchResult->second;
                for (const auto secondLocation : locations)
                {
                    if(secondLocation != i)
                    {
                        ret[1] = secondLocation;
                        ret[0] = i;
                        break;
                    }
                }
            }
        }
    
        return ret;
    }
};