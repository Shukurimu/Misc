#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
using namespace std;

template<typename T>
struct Parser {
	const string number = "0123456789+-";
	vector<T> toVector(string s) {
		vector<T> v;
		size_t found = 0;
		while ((found = s.find_first_of(number, found)) != string::npos) {
			s = s.substr(found);
			v.emplace_back(stoi(s, &found));
		}
		return v;
	}
	
	vector<vector<T>> toMatrix(string s) {
		vector<vector<T>> m;
		size_t found = 0;
		while ((found = s.find_first_of("[", found + 1)) != string::npos) {
			size_t token = s.find_first_of("]", found + 1);
			m.emplace_back(toVector(s.substr(found, token - found)));
		}
		return m;
	}
	
	string toString(vector<T> v) {
		string s = "[ ";
		for (T& i: v)
			s += to_string(i) + " ";
		s += "]";
		return s;
	}
	
	string toString(vector<vector<T>> m) {
		string s = "[ \n";
		for (vector<T>& v: m)
			s += "  " + vector2string(v) + "\n";
		s += "]";
		return s;
	}
	
};

class Solution {
public:
	int lengthOfLIS(vector<int>& nums) {
		const int&& size = static_cast<int>(nums.size());
		if (size == 0)	return 0;
		vector<int> dp(nums.size(), 1);
		int ans = 1;
		for (int i = 0; i < size; ++i) {
			for (int j = i - 1; j >= 0; --j) {
				if (nums[j] < nums[i])
					ans = max(ans, dp[i] = max(dp[i], dp[j] + 1));
			}
		}
		return ans;
	}
};

int main(void) {
	auto input = Parser<int>().toVector("[10]");
	// cout << Parser<int>().toString(input) << endl;
	cout << Solution().lengthOfLIS(input) << endl;
	return 0;
}
