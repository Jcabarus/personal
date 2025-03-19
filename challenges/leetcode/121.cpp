// Best Time to Buy and Sell Stock

#include <iostream>
#include <vector>

using namespace std;

class Solution 
{
    public:
        int maxProfit(vector<int>& prices) 
        {
            
        }
};

// int maxProfit(vector<int>& prices) 
// {
//     int buy_index = 0, sell_index = 0, market_value = 0;

//     if(prices.size() > 1)
//     {
//         while(market_value == 0)
//         {
//             for(int i = 1 + market_value; i < prices.size(); i++) // Finds the maximum value for sell_index
//             {
//                 if(prices[market_value] <= prices[i])
//                 {
//                     market_value = i;
//                 }
//                 else if(market_value == 0)
//                 {
//                     market_value++;
//                 }
//             }

//             sell_index = market_value;
//         }
//     }

//     market_value = 0;

//     for(int i = 1; i < prices.size() - (prices.size() - (sell_index + 1)); i++) // Finds the minimum value for buy_index
//     {
//         if(prices[market_value] > prices[i])
//         {
//             market_value = i;
//         }
//     }

//     buy_index = market_value;

//     return prices[sell_index] - prices[buy_index];
// }
    
// int maxProfit(vector<int>& prices) 
// {
//     int buy_index = 0, sell_index = 0, market_value = 0;

//     for(int i = 1; i < prices.size() - (); i++) // Finds the minimum value for buy_index
//     {
//         if(prices[market_value] > prices[i])
//         {
//             market_value = i;
//         }
//     }

//     buy_index = market_value;

//     for(int i = market_value; i < prices.size(); i++) // Finds the maximum value for sell_index
//     {
//         if(prices[market_value] < prices[i])
//         {
//             market_value = i;
//         }
//     }

//     sell_index = market_value;
    
//     return prices[sell_index] - prices[buy_index];
// }