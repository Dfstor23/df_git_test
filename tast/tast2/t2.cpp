#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip> // 用于格式化输出
//错误删除痕迹
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

    // 查看所有账单
    void viewAllTransactions() {
        if (transactions.empty()) {
            cout << "暂无账单记录！" << endl;
            return;
        }

        double totalIncome = 0;
        double totalExpense = 0;

        // 打印表头
        cout << endl << "===================== 所有账单记录 =====================" << endl;
        cout << left << setw(12) << "日期" 
             << setw(10) << "类型" 
             << setw(10) << "金额" 
             << setw(15) << "类别" 
             << "备注" << endl;
        cout << "--------------------------------------------------------" << endl;

        // 打印每条记录
        for (const auto& trans : transactions) {
            cout << left << setw(12) << trans.date;
            cout << setw(10) << (trans.isIncome ? "收入" : "支出");
            cout << setw(10) << fixed << setprecision(2) << trans.amount;
            cout << setw(15) << trans.category;
            cout << trans.remarks << endl;

            // 累计收支
            if (trans.isIncome) {
                totalIncome += trans.amount;
            } else {
                totalExpense += trans.amount;
            }
        }

        // 打印汇总信息
        cout << "--------------------------------------------------------" << endl;
        cout << "总收入：" << fixed << setprecision(2) << totalIncome << " 元" << endl;
        cout << "总支出：" << fixed << setprecision(2) << totalExpense << " 元" << endl;
        cout << "结余：" << fixed << setprecision(2) << (totalIncome - totalExpense) << " 元" << endl;
        cout << "========================================================" << endl << endl;
    }

    // 查询账单
    void queryTransactions() {
        if (transactions.empty()) {
            cout << "暂无账单记录可查询！" << endl;
            return;
        }

        int queryOption;
        cout << endl << "查询方式：" << endl;
        cout << "1. 按日期查询" << endl;
        cout << "2. 按类别查询" << endl;
        cout << "请选择查询方式：";
        cin >> queryOption;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        vector<Transaction> results;
        string keyword;

        if (queryOption == 1) {
            cout << "请输入要查询的日期（YYYY-MM-DD）：";
            getline(cin, keyword);
            for (const auto& trans : transactions) {
                if (trans.date == keyword) {
                    results.push_back(trans);
                }
            }
        } else if (queryOption == 2) {
            cout << "请输入要查询的类别：";
            getline(cin, keyword);
            for (const auto& trans : transactions) {
                if (trans.category == keyword) {
                    results.push_back(trans);
                }
            }
        } else {
            cout << "无效的查询方式！" << endl;
            return;
        }

        // 显示查询结果
        if (results.empty()) {
            cout << "未找到匹配的账单记录！" << endl;
            return;
        }

        double totalIncome = 0;
        double totalExpense = 0;

        cout << endl << "===================== 查询结果 =====================" << endl;
        cout << left << setw(12) << "日期" 
             << setw(10) << "类型" 
             << setw(10) << "金额" 
             << setw(15) << "类别" 
             << "备注" << endl;
        cout << "---------------------------------------------------" << endl;

        for (const auto& trans : results) {
            cout << left << setw(12) << trans.date;
            cout << setw(10) << (trans.isIncome ? "收入" : "支出");
            cout << setw(10) << fixed << setprecision(2) << trans.amount;
            cout << setw(15) << trans.category;
            cout << trans.remarks << endl;

            if (trans.isIncome) {
                totalIncome += trans.amount;
            } else {
                totalExpense += trans.amount;
            }
        }

        cout << "---------------------------------------------------" << endl;
        cout << "查询结果总收入：" << fixed << setprecision(2) << totalIncome << " 元" << endl;
        cout << "查询结果总支出：" << fixed << setprecision(2) << totalExpense << " 元" << endl;
        cout << "查询结果结余：" << fixed << setprecision(2) << (totalIncome - totalExpense) << " 元" << endl;
        cout << "===================================================" << endl << endl;
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
        cout << "3. 查看所有账单" << endl;
        cout << "4. 查询账单" << endl;
        cout << "5. 退出系统" << endl;

        cout << "请输入选项序号：";
        cin >> option;

        // 处理输入错误
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "输入错误，请输入数字选项！" << endl;
            continue;
        }

        switch (option) {
        case 1:
            billManager.recordIncome();
            break;
        case 2:
            billManager.recordExpense();
            break;
        case 3:
            billManager.viewAllTransactions();
            break;
        case 4:
            billManager.queryTransactions();
            break;
        case 5:
            cout << "感谢使用个人账单管理系统，再见！" << endl;
            return 0;
        default:
            cout << "无效的选项，请重新选择！" << endl;
        }

        cout << "按任意键返回主菜单...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();  
    }

    return 0;
}
