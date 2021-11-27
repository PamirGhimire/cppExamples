class Solution {
public:
    int maximumScore(vector<int>& nums, int k) {
        const auto minInRange = [](vector<int>& v, int i, int j)
        {
            int min = v[i];
            for (int n = i; n <= j; ++n)
                if(v[n] < min)
                    min = v[n];
            return min;
        };
        
        const auto min = [](int a, int b){ return a<b?a:b;};
        
        std::map<int, int> imap;
        int blockMin(std::numeric_limits<int>::max());
        for (int i = 0; i <= k; ++i)
        {
            if(blockMin == std::numeric_limits<int>::max() || (i > 0 && blockMin == nums[i-1]) )
                blockMin = minInRange(nums, i, k);
            imap[i] = blockMin;
        }
    
        std::map<int, int> jmap;
        blockMin = std::numeric_limits<int>::max();
        for (int j = k; j < nums.size(); ++j)
        {
            if(nums[j] < blockMin)
                blockMin = nums[j];
            jmap[j] = blockMin;
        }
    
        int max_score = std::numeric_limits<int>::min();
        for(auto i = imap.begin(); i != imap.end(); ++i)
        {
            for(auto j = jmap.begin(); j != jmap.end(); ++j)
            {
                int score = (j->first - i->first + 1) * min(i->second, j->second);
                if(score > max_score)
                    max_score = score;
            }
        }
        
        return max_score;
    }
};