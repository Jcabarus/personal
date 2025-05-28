// Best Time to Buy and Sell Stock II, solved
#include <iostream>
#include <vector>

using namespace std;

class Solution 
{
    public:
        int maxProfit(vector<int>& prices) 
        {
            bool is_buy = false, is_sell = false;
            int buy_index = 0, sell = 0, sell_index, max_profit = 0;

            for(int i = 1; i < prices.size(); i++) //Buying
            {
                if(prices[i] < prices[buy_index] && i != prices.size() - 1) // current day < initial day, and is not the last day
                {
                    buy_index = i;
                    sell_index = i;
                    is_buy = true;
                }
                else if(is_buy == false)
                {
                    sell_index = buy_index;
                    is_buy = true;
                }
                
                if(prices[i] > prices[sell_index] && is_buy == true) // current day > price at that day, and we have bought
                {
                    sell_index = i;
                    is_sell = true;
                }
                
                if(is_buy && is_sell) // we have bought and sell
                {
                    int current_profit = prices[sell_index] - prices[buy_index];

                    max_profit += current_profit;
                    is_buy = false, is_sell = false, buy_index = i, sell_index = i;
                }
            }   
            
            return max_profit;            
        }
};