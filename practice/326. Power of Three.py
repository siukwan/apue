﻿class Solution(object):
    def isPowerOfThree(self, n):
        """
        :type n: int
        :rtype: bool
        """
        if n>0:
            return not (1162261467 % n)
        else :
            return False
        