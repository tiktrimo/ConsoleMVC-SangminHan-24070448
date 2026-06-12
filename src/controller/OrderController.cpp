#include "OrderController.h"
#include <ctime>
#include <sstream>
#include <iomanip>
#include <cmath>

std::string OrderController::generateOrderId() {
    std::time_t t = std::time(nullptr);
    std::tm tm{};
    localtime_s(&tm, &t);
    std::ostringstream oss;
    oss << "ORD-"
        << std::put_time(&tm, "%Y%m%d")
        << "-" << std::setw(4) << std::setfill('0') << nextOrderNum_++;
    return oss.str();
}

Order OrderController::placeOrder(const std::string& sampleId,
                                   const std::string& customer, int qty) {
    Order order;
    order.orderId = generateOrderId();
    order.sampleId = sampleId;
    order.customerName = customer;
    order.quantity = qty;
    order.status = OrderStatus::RESERVED;
    orders_.push_back(order);
    return orders_.back();
}

bool OrderController::approveOrder(const std::string& orderId,
                                    std::vector<Sample>& samples) {
    for (auto& order : orders_) {
        if (order.orderId != orderId) continue;
        if (order.status != OrderStatus::RESERVED) return false;

        for (auto& sample : samples) {
            if (sample.id != order.sampleId) continue;
            if (sample.stock >= order.quantity) {
                sample.stock -= order.quantity;
                order.status = OrderStatus::CONFIRMED;
            } else {
                order.status = OrderStatus::PRODUCING;
            }
            return true;
        }
        return false;
    }
    return false;
}

bool OrderController::rejectOrder(const std::string& orderId) {
    for (auto& order : orders_) {
        if (order.orderId == orderId &&
            order.status == OrderStatus::RESERVED) {
            order.status = OrderStatus::REJECTED;
            return true;
        }
    }
    return false;
}

bool OrderController::releaseOrder(const std::string& orderId) {
    for (auto& order : orders_) {
        if (order.orderId == orderId &&
            order.status == OrderStatus::CONFIRMED) {
            order.status = OrderStatus::RELEASE;
            return true;
        }
    }
    return false;
}

const std::vector<Order>& OrderController::getAll() const {
    return orders_;
}

std::vector<const Order*> OrderController::getByStatus(OrderStatus status) const {
    std::vector<const Order*> result;
    for (const auto& o : orders_) {
        if (o.status == status) result.push_back(&o);
    }
    return result;
}

int OrderController::getTotalOrderCount() const {
    return static_cast<int>(orders_.size());
}
