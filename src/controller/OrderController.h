#pragma once
#include <vector>
#include <string>
#include "../model/Order.h"
#include "../model/Sample.h"

class OrderController {
public:
    Order placeOrder(const std::string& sampleId, const std::string& customer, int qty);
    bool approveOrder(const std::string& orderId, std::vector<Sample>& samples);
    bool rejectOrder(const std::string& orderId);
    bool releaseOrder(const std::string& orderId);
    const std::vector<Order>& getAll() const;
    std::vector<const Order*> getByStatus(OrderStatus status) const;
    int getTotalOrderCount() const;

private:
    std::vector<Order> orders_;
    int nextOrderNum_ = 1;
    std::string generateOrderId();
};
