#include <iostream>
#include <windows.h>
#include "src/controller/SampleController.h"
#include "src/controller/OrderController.h"
#include "src/view/ConsoleView.h"

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    SampleController sampleCtrl;
    OrderController  orderCtrl;
    ConsoleView      view;

    // --- Seed sample data (Model layer) ---
    sampleCtrl.addSample({"S-001", "실리콘 웨이퍼-8인치", 0.5, 0.92, 100});
    sampleCtrl.addSample({"S-002", "GaN 에피택셜-4인치",  0.3, 0.78,  50});
    sampleCtrl.addSample({"S-003", "SiC 파워기판-6인치",  0.8, 0.92,  30});

    // --- Place orders (Controller layer: creates RESERVED orders) ---
    Order o1 = orderCtrl.placeOrder("S-001", "삼성전자 파운드리", 30);
    Order o2 = orderCtrl.placeOrder("S-003", "LG이노텍",          200); // stock insufficient
    Order o3 = orderCtrl.placeOrder("S-002", "SK하이닉스",         20);

    // --- View renders current state (View layer) ---
    view.showMainMenu(sampleCtrl.getSampleCount(),
                      sampleCtrl.getTotalStock(),
                      orderCtrl.getTotalOrderCount(),
                      static_cast<int>(orderCtrl.getByStatus(OrderStatus::PRODUCING).size()));

    std::cout << "\n[시료 목록]\n";
    view.showSamples(sampleCtrl.getAll());

    std::cout << "\n[주문 접수 직후 상태]\n";
    view.showOrders(orderCtrl.getAll());

    // --- Approve/reject (Controller layer: transitions order status) ---
    orderCtrl.approveOrder(o1.orderId, sampleCtrl.getAll()); // CONFIRMED (재고 충분)
    orderCtrl.approveOrder(o2.orderId, sampleCtrl.getAll()); // PRODUCING (재고 부족)
    orderCtrl.rejectOrder(o3.orderId);                       // REJECTED

    // --- View renders updated state ---
    std::cout << "\n[승인/거절 처리 후 상태]\n";
    view.showOrders(orderCtrl.getAll());

    std::cout << "\n[상태별 현황]\n";
    view.showOrdersByStatus(orderCtrl.getByStatus(OrderStatus::CONFIRMED), "CONFIRMED");
    view.showOrdersByStatus(orderCtrl.getByStatus(OrderStatus::PRODUCING), "PRODUCING");
    view.showOrdersByStatus(orderCtrl.getByStatus(OrderStatus::REJECTED),  "REJECTED");

    return 0;
}
