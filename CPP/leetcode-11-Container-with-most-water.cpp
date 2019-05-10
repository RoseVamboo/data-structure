/*

Given n non-negative integers a1, a2, ..., an , 
where each represents a point at coordinate (i, ai). 
n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). 
Find two lines, which together with x-axis forms a container, 
such that the container contains the most water.

Note: You may not slant the container and n is at least 2.

*/
/*
4.解题思路：
1).这里的容器装最多水问题，其实由最短的那块板决定。
2).通过左右游标移动，哪个游标指向的板短，则该游标就朝后移动
（如果是从左向右移动的游标，则向右移，如果是从右向左西东的游标则向左移）
*/
#include<iostream>
#include<algorithm>
using namespace std;
int getMaxArea(int *height,int n){
	
	int leftPos = 0;
	int rightPos = n - 1;
	int max = 0;
	int currentArea = 0;
	while (leftPos < rightPos){
		currentArea = abs(leftPos - rightPos)*min(height[leftPos], height[rightPos]);
		if (currentArea>max){
			max = currentArea;
		}
		if (height[leftPos] < height[rightPos]){
			leftPos++;
		}
		else{
			rightPos--;
		}
	}
	return max;
}

int main(){
	
	int array[] = { 1, 8, 6, 2, 5, 4, 8, 3, 7 };
	int arrLen = sizeof(array) / sizeof(array[0]);
	
	int max = getMaxArea(array, arrLen);
	cout << "max=" << max << endl;
	
	return 0;
}