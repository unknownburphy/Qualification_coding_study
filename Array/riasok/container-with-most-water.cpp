class Solution {
public:
    int maxArea(vector<int>& height) {
        int area = 0;
        int l = 0;
        int r = height.size()-1;
        
        while(r>l){
            area = max(area, (r-l)*min(height[r],height[l]));
            if(height[l] > height[r])
                r--;
            else
                l++;
        }   
        return area;
    }
};