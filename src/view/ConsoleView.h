#pragma once
#include <string>
#include <vector>
#include "../model/Sample.h"
#include "../model/Order.h"

class ConsoleView {
public:
    void showMainMenu(int sampleCount, int totalStock, int orderCount, int producingCount);
    void showSamples(const std::vector<Sample>& samples);
    void showOrders(const std::vector<Order>& orders);
    void showOrdersByStatus(const std::vector<const Order*>& orders, const std::string& label);
    void showMessage(const std::string& msg);
    void showError(const std::string& msg);
    void showSeparator(char c = '=', int width = 60);

    std::string promptString(const std::string& label);
    int         promptInt(const std::string& label);
    double      promptDouble(const std::string& label);
};
