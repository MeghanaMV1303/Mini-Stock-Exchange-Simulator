#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

using namespace std;

// Maximum number of stocks the simulator can handle
const int MAX_STOCKS = 5;

// --- Global Data (for simplicity) ---
string stockSymbols[MAX_STOCKS];
string stockNames[MAX_STOCKS];
double stockPrices[MAX_STOCKS];

int portfolioShares[MAX_STOCKS]; // How many shares of each stock the user owns
double portfolioAvgCost[MAX_STOCKS]; // Average cost for each stock
double cashBalance = 10000.0; // Starting cash

int numStocks = 0; // Current number of active stocks

// --- Functions ---

void initializeStocks() {
    // Seed the random number generator
    srand(time(0)); 

    // Add some initial stocks
    stockSymbols[0] = "AAPL"; stockNames[0] = "Apple Inc."; stockPrices[0] = 150.0;
    stockSymbols[1] = "GOOG"; stockNames[1] = "Google Inc."; stockPrices[1] = 2800.0;
    stockSymbols[2] = "TSLA"; stockNames[2] = "Tesla Inc."; stockPrices[2] = 700.0;
    numStocks = 3;

    // Initialize portfolio
    for (int i = 0; i < MAX_STOCKS; ++i) {
        portfolioShares[i] = 0;
        portfolioAvgCost[i] = 0.0;
    }
}

void updateStockPrices() {
    for (int i = 0; i < numStocks; ++i) {
        // Simple random change: -5% to +5%
        double change = (rand() % 100 - 49) / 1000.0; // -0.049 to 0.050
        stockPrices[i] *= (1.0 + change);
        if (stockPrices[i] < 0.01) stockPrices[i] = 0.01; // Minimum price
    }
}

void displayMarket() {
    cout << "\n--- Current Market Prices ---" << endl;
    cout << left << setw(10) << "Symbol" << setw(20) << "Name" << setw(15) << "Price" << endl;
    cout << string(45, '-') << endl;

    for (int i = 0; i < numStocks; ++i) {
        cout << left << setw(10) << stockSymbols[i]
             << setw(20) << stockNames[i]
             << "$" << fixed << setprecision(2) << stockPrices[i] << endl;
    }
}

void displayPortfolio() {
    cout << "\n--- Your Portfolio ---" << endl;
    cout << "Cash Balance: $" << fixed << setprecision(2) << cashBalance << endl;
    cout << left << setw(10) << "Symbol" << setw(10) << "Shares" << setw(15) << "Avg Cost" << setw(15) << "Current" << setw(15) << "P/L" << endl;
    cout << string(65, '-') << endl;

    double totalPortfolioValue = cashBalance;
    for (int i = 0; i < numStocks; ++i) {
        if (portfolioShares[i] > 0) {
            double currentPrice = stockPrices[i];
            double cost = portfolioAvgCost[i];
            double pl = (currentPrice - cost) * portfolioShares[i];
            totalPortfolioValue += (currentPrice * portfolioShares[i]);

            cout << left << setw(10) << stockSymbols[i]
                 << setw(10) << portfolioShares[i]
                 << "$" << setw(14) << cost
                 << "$" << setw(14) << currentPrice
                 << (pl >= 0 ? "+" : "") << "$" << setw(14) << pl << endl;
        }
    }
    cout << string(65, '-') << endl;
    cout << "Total Portfolio Value: $" << fixed << setprecision(2) << totalPortfolioValue << endl;
}

void buyStock() {
    string symbol; 
    int quantity;
    cout << "Enter symbol to buy: ";
    cin >> symbol;

    int stockIndex = -1;
    for (int i = 0; i < numStocks; ++i) {
        if (stockSymbols[i] == symbol) {
            stockIndex = i;
            break;
        }
    }

    if (stockIndex == -1) {
        cout << "Stock not found!" << endl;
        return;
    }

    cout << "Enter quantity to buy: ";
    cin >> quantity;

    if (quantity <= 0) {
        cout << "Quantity must be positive!" << endl;
        return;
    }

    double price = stockPrices[stockIndex];
    double totalCost = quantity * price;

    if (cashBalance < totalCost) {
        cout << "Insufficient funds! You need $" << fixed << setprecision(2) << totalCost << endl;
        return;
    }

    cashBalance -= totalCost;

    // Update average cost basis
    double currentTotalCost = portfolioShares[stockIndex] * portfolioAvgCost[stockIndex];
    portfolioShares[stockIndex] += quantity;
    portfolioAvgCost[stockIndex] = (currentTotalCost + totalCost) / portfolioShares[stockIndex];

    cout << "Bought " << quantity << " shares of " << symbol << " for $" << fixed << setprecision(2) << totalCost << endl;
}

void sellStock() {
    string symbol;
    int quantity;
    cout << "Enter symbol to sell: ";
    cin >> symbol;

    int stockIndex = -1;
    for (int i = 0; i < numStocks; ++i) {
        if (stockSymbols[i] == symbol) {
            stockIndex = i;
            break;
        }
    }

    if (stockIndex == -1) {
        cout << "Stock not found!" << endl;
        return;
    }

    cout << "Enter quantity to sell: ";
    cin >> quantity;

    if (quantity <= 0) {
        cout << "Quantity must be positive!" << endl;
        return;
    }

    if (portfolioShares[stockIndex] < quantity) {
        cout << "Not enough shares to sell! You only have " << portfolioShares[stockIndex] << endl;
        return;
    }

    double price = stockPrices[stockIndex];
    double totalGain = quantity * price;

    cashBalance += totalGain;
    portfolioShares[stockIndex] -= quantity;

    // If all shares are sold, reset average cost
    if (portfolioShares[stockIndex] == 0) {
        portfolioAvgCost[stockIndex] = 0.0;
    }

    cout << "Sold " << quantity << " shares of " << symbol << " for $" << fixed << setprecision(2) << totalGain << endl;
}

int main() {
    cout << "========================================" << endl;
    cout << "   SIMPLE STOCK EXCHANGE SIMULATOR      " << endl;
    cout << "========================================" << endl;

    initializeStocks();

    int choice;
    while (true) {
        cout << "\n1. View Market\n2. View Portfolio\n3. Buy Stock\n4. Sell Stock\n5. Next Day\n6. Exit\nChoice: ";
        cin >> choice;

        // Basic input validation
        if (cin.fail()) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear(); // Clear error flags
            cin.ignore(10000, '\n'); // Discard invalid input
            continue;
        }

        switch (choice) {
            case 1:
                displayMarket();
                break;
            case 2:
                displayPortfolio();
                break;
            case 3:
                buyStock();
                break;
            case 4:
                sellStock();
                break;
            case 5:
                updateStockPrices();
                cout << "\nMarket prices updated for the next day!" << endl;
                break;
            case 6:
                cout << "Exiting simulator. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
