class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        set<char> uniq(s.begin(), s.end());
        int window = uniq.size();
        while (window > 0){
            for(int i = 0; i + window <= s.size(); i++){
                string s_ = s.substr(i, window);
                set<char> uniq2(s_.begin(), s_.end());
                if(uniq2.size() == window){
                    return window;
                }
            }
            window -= 1;
        }
        return 0;
    }