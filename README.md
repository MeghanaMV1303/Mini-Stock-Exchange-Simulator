# Simple Mini Stock Exchange Simulator (C++)

This is a basic command-line application written in C++ that simulates a mini stock exchange. It's designed to be simple and easy to understand, making it suitable for beginners learning C++ or those who want a straightforward simulation of stock trading.

## Features

*   **Virtual Trading:** Start with a virtual cash balance of $10,000 to buy and sell stocks.
*   **Dynamic Market:** Stock prices fluctuate randomly each 
Manus AI
"day" or "turn".
*   **Portfolio Management:** Track your owned shares, average purchase cost, current value, and profit/loss for each stock.
*   **Market Overview:** View current stock symbols, names, and prices.
*   **User-Friendly Interface:** Simple menu-driven interaction for easy navigation.

## How to Compile and Run

To compile and run this simulator, you will need a C++ compiler (like g++).

1.  **Save the code:** Save the provided C++ source code as `simple_stock_simulator.cpp`.

2.  **Open a terminal:** Navigate to the directory where you saved the file.

3.  **Compile the code:** Use the following command to compile the source code:
    ```bash
    g++ simple_stock_simulator.cpp -o simple_stock_simulator
    ```

4.  **Run the simulator:** Execute the compiled program:
    ```bash
    ./simple_stock_simulator
    ```

## Usage

Once the simulator is running, you will be presented with a menu of options:

*   **1. View Market:** Displays the current prices of all available stocks.
*   **2. View Portfolio:** Shows your current cash balance, owned stocks, the number of shares, average cost, current price, and your profit/loss.
*   **3. Buy Stock:** Allows you to purchase shares of a selected stock. You will need to enter the stock symbol and the quantity.
*   **4. Sell Stock:** Allows you to sell shares of a selected stock. You will need to enter the stock symbol and the quantity.
*   **5. Next Day:** Advances the simulation to the next day, updating all stock prices randomly.
*   **6. Exit:** Quits the simulator.

### Example Interaction

```
========================================
   SIMPLE STOCK EXCHANGE SIMULATOR      
========================================

1. View Market
2. View Portfolio
3. Buy Stock
4. Sell Stock
5. Next Day
6. Exit
Choice: 1

--- Current Market Prices ---
Symbol    Name                Price          
---------------------------------------------
AAPL      Apple Inc.          $150.00
GOOG      Google Inc.         $2800.00
TSLA      Tesla Inc.          $700.00

1. View Market
2. View Portfolio
3. Buy Stock
4. Sell Stock
5. Next Day
6. Exit
Choice: 3
Enter symbol to buy: AAPL
Enter quantity to buy: 10
Bought 10 shares of AAPL for $1500.00

1. View Market
2. View Portfolio
3. Buy Stock
4. Sell Stock
5. Next Day
6. Exit
Choice: 2

--- Your Portfolio ---
Cash Balance: $8500.00
Symbol    Shares    Avg Cost       Current        P/L            
-----------------------------------------------------------------
AAPL      10        $150.00        $150.00        +$0.00          
-----------------------------------------------------------------
Total Portfolio Value: $10000.00

...
```

## Author

Meghana M V 
