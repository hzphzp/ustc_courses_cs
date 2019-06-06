#
# @lc app=leetcode id=5 lang=python3
#
# [5] Longest Palindromic Substring
#
# https://leetcode.com/problems/longest-palindromic-substring/description/
#
# algorithms
# Medium (26.74%)
# Total Accepted:    502.4K
# Total Submissions: 1.9M
# Testcase Example:  '"babad"'
#
# Given a string s, find the longest palindromic substring in s. You may assume
# that the maximum length of s is 1000.
# 
# Example 1:
# 
# 
# Input: "babad"
# Output: "bab"
# Note: "aba" is also a valid answer.
# 
# 
# Example 2:
# 
# 
# Input: "cbbd"
# Output: "bb"
# 
# 
#
class Solution:
    def longestPalindrome(self, s: str) -> str:
        maxS = ""
        for index, char in enumerate(s):
            # odd
            i = index - 1
            j = index + 1
            while i >= 0 and j < len(s) and s[i] == s[j]:
                i -= 1
                j += 1
            Odd = s[i+1: j]
            if len(Odd) > len(maxS):
                maxS = Odd

            # Even            
            i = index - 1
            j = index + 2
            if not (index + 1 < len(s) and s[index + 1] == s[index]):
                Even = ''
            else:
                while i >= 0 and j < len(s) and s[i] == s[j]:
                    i -= 1
                    j += 1
                Even = s[i+1: j]
            if len(Even) > len(maxS):
                maxS = Even
        return maxS
            
                
if __name__ == "__main__":
    solution = Solution()
    print(solution.longestPalindrome("bb"))



        

