/**
 * @param {number[][]} triangle
 * @return {number}
 */
let minimumTotal = function(triangle) {
    let sz = triangle.length;
    let dp = triangle[sz-1];
    for (r=sz-2; r>=0; r--)
        for (c=0; c<=r; c++)
            dp[c] = triangle[r][c] + Math.min(dp[c], dp[c+1]);
    return dp[0];
};
