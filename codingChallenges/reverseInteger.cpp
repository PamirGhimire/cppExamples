class Solution {
public:
    int reverse(int x) {
        long int ret = 0;
                
        while (x != 0)
        {
            int last_digit = x % 10;
            ret = 10*ret + last_digit;
            x = x/10;
            
            if(ret > std::numeric_limits<int>::max() ||
              ret < std::numeric_limits<int>::min())
                return 0;
        }
        
        return ret;
    }
};