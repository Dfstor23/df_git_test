#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

struct Transaction {
    string date;
    double amount;
    string category;
    string remarks;
    bool isIncome;  // true = income, false = expense
};

class BillManager {
private:
    vector<Transaction> transactions;

public:
    void recordIncome() {
        Transaction trans;
        trans.isIncome = true;
        cout << "请输入收入信息：" << endl;
        cout << "日期（YYYY-MM-DD）：";
        cin >> trans.date;
        cout << "金额：";
        cin >> trans.amount;
        while (trans.amount <= 0) {
            cout << "收入金额必须为正数，请重新输入金额：";
            cin >> trans.amount;
        }
        cout << "类别（如工资、奖金等）：";
        cin >> trans.category;
        cout << "备注：";
        cin.ignore();
        getline(cin, trans.remarks);
        transactions.push_back(trans);
        cout << "收入已成功记录！" << endl;
    }

    void recordExpense() {
        Transaction trans;
        trans.isIncome = false;
        cout << "请输入支出信息：" << endl;
        cout << "日期（YYYY-MM-DD）：";
        cin >> trans.date;
        cout << "金额：";
        cin >> trans.amount;
        while (trans.amount <= 0) {
            cout << "支出金额必须为正数，请重新输入金额：";
            cin >> trans.amount;
        }
        cout << "类别（如餐饮、交通、购物等）：";
        cin >> trans.category;
        cout << "备注：";
        cin.ignore();
        getline(cin, trans.remarks);
        transactions.push_back(trans);
        cout << "支出已成功记录！" << endl;
    }
};

int main() {
    BillManager billManager;
    int option;

    while (true) {
        cout << "=================================" << endl;
        cout << "欢迎使用个人账单管理系统" << endl;
        cout << "=================================" << endl;
        cout << "请选择操作：" << endl;
        cout << "1. 记录收入" << endl;
        cout << "2. 记录支出" << endl;
        cout << "3. 退出系统" << endl;

        cout << "请输入选项序号：";
        cin >> option;

        switch (option) {
        case 1:
            billManager.recordIncome();
            break;
        case 2:
            billManager.recordExpense();
            break;
        case 3:
            cout << "感谢使用个人账单管理系统，再见！" << endl;
            return 0;
        default:
            cout << "无效的选项，请重新选择！" << endl;
        }

        cout << "按任意键返回主菜单...";
        cin.ignore();
        cin.get();  // Wait for user to press any key
    }

    return 0;
}
