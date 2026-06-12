#include "ConsoleView.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>

void ConsoleView::showSeparator(char c, int width) {
    std::cout << std::string(width, c) << "\n";
}

void ConsoleView::showMainMenu(int sampleCount, int totalStock,
                                int orderCount, int producingCount) {
    time_t now = time(nullptr);
    struct tm t {};
    localtime_s(&t, &now);
    char dtbuf[32];
    strftime(dtbuf, sizeof(dtbuf), "%Y-%m-%d %H:%M:%S", &t);

    showSeparator();
    std::cout << "   반도체 시료 생산주문관리 시스템\n";
    std::cout << "   " << dtbuf << "\n";
    showSeparator();
    std::cout << "  등록 시료  : " << sampleCount << "종"
              << "   총 재고 : " << totalStock << " ea\n"
              << "  전체 주문  : " << orderCount << "건"
              << "   생산라인: " << producingCount << "건 대기\n";
    showSeparator('-');
    std::cout << "  [1] 시료 관리\n"
              << "  [2] 시료 주문\n"
              << "  [3] 주문 승인/거절\n"
              << "  [4] 모니터링\n"
              << "  [5] 생산라인 조회\n"
              << "  [6] 출고 처리\n"
              << "  [0] 종료\n";
    showSeparator();
}

void ConsoleView::showSamples(const std::vector<Sample>& samples) {
    showSeparator('-');
    std::cout << std::left
              << std::setw(8)  << "ID"
              << std::setw(22) << "시료명"
              << std::setw(12) << "생산시간"
              << std::setw(8)  << "수율"
              << "재고\n";
    showSeparator('-');
    for (const auto& s : samples) {
        std::cout << std::left
                  << std::setw(8)  << s.id
                  << std::setw(22) << s.name
                  << std::setw(12) << (std::to_string(s.avgProductionTimeMin) + "min")
                  << std::setw(8)  << s.yield
                  << s.stock << " ea\n";
    }
}

void ConsoleView::showOrders(const std::vector<Order>& orders) {
    showSeparator('-');
    std::cout << std::left
              << std::setw(6)  << "번호"
              << std::setw(22) << "주문번호"
              << std::setw(8)  << "시료ID"
              << std::setw(16) << "고객명"
              << std::setw(8)  << "수량"
              << "상태\n";
    showSeparator('-');
    for (int i = 0; i < (int)orders.size(); i++) {
        const auto& o = orders[i];
        std::cout << std::left
                  << std::setw(6)  << ("[" + std::to_string(i + 1) + "]")
                  << std::setw(22) << o.orderId
                  << std::setw(8)  << o.sampleId
                  << std::setw(16) << o.customerName
                  << std::setw(8)  << (std::to_string(o.quantity) + "ea")
                  << orderStatusToString(o.status) << "\n";
    }
}

void ConsoleView::showOrdersByStatus(const std::vector<const Order*>& orders,
                                      const std::string& label) {
    std::cout << "[" << label << "] " << orders.size() << "건\n";
    for (const auto* o : orders) {
        std::cout << "  " << o->orderId
                  << " | " << o->customerName
                  << " | " << o->quantity << "ea\n";
    }
}

void ConsoleView::showMessage(const std::string& msg) {
    std::cout << "[OK] " << msg << "\n";
}

void ConsoleView::showError(const std::string& msg) {
    std::cerr << "[ERROR] " << msg << "\n";
}

std::string ConsoleView::promptString(const std::string& label) {
    std::cout << label << " > ";
    std::string input;
    std::getline(std::cin, input);
    return input;
}

int ConsoleView::promptInt(const std::string& label) {
    std::cout << label << " > ";
    int val = 0;
    std::cin >> val;
    std::cin.ignore();
    return val;
}

double ConsoleView::promptDouble(const std::string& label) {
    std::cout << label << " > ";
    double val = 0.0;
    std::cin >> val;
    std::cin.ignore();
    return val;
}
