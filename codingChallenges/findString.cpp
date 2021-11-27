class Solution {
public:
    vector<string> findOcurrences(string text, string first, string second) {
        std::stringstream ss(text);
        std::istream_iterator<std::string> begin(ss);
        std::istream_iterator<std::string> end;
        std::vector<std::string> vstrings(begin, end);
        
        vector<string> ret;
        for(int i = 0; i < vstrings.size() - 1; ++i)
        {
            if(vstrings[i] == first && vstrings[i+1] == second)
            {
                if(i+2 < vstrings.size())   
                    ret.push_back(vstrings[i+2]);
            }
        }
    
        return ret;
    }
};