#include <iomanip>
#include <iostream>
#include <string>


using namespace std;

int main() {
    using VariantType = variant<string, double>;

    unordered_map<string, unordered_map<string, unordered_map<string, VariantType>>> data = {
        { "data", {
                {
                    "interest_rate", {
                        { "placeholder", "Interest rate" },
                        { "value", 3.0 }
                    }
                },
                {
                    "tenure", {
                        { "placeholder", "Tenure" },
                        { "value", 9.0 }
                    }
                },
                {
                    "loan_amount", {
                        { "placeholder", "Loan amount" },
                        { "value", 37800.0 }
                    }
                },
                {
                    "early_settlement_mths",{
                            { "placeholder", "Early settlement after how many months" },
                            { "value", 0.0 }
                    }
                }
        } }
    };


    // Loop to update 'value' entries from user input
    for (auto& field : data["data"]) {
        cout << get<string>(field.second["placeholder"]) << ": ";

        double input;
        cin >> input;
        field.second["value"] = input;

        // cout << field.first << " => " << input << endl;
    }

    // Access and compute
    double loan_amount = get<double>(data["data"]["loan_amount"]["value"]);
    double tenure_in_years = get<double>(data["data"]["tenure"]["value"]);
    double tenure_in_months = get<double>(data["data"]["tenure"]["value"]) *12;
    double interest_rate = get<double>(data["data"]["interest_rate"]["value"]);
    double early_settlement_mths = get<double>(data["data"]["early_settlement_mths"]["value"]);


    // Principal Amount
    //Total Interest for x tenure
    //Total Payment to Bank
    //Monthly Payment
    //Amount Paid-to-Date after 24 months
    double total_interest = loan_amount * (interest_rate/100) * tenure_in_years;
    double principal_plus_interest =  loan_amount + total_interest;
    double monthly_payment = principal_plus_interest / tenure_in_months;
    double amount_paid_to_date = early_settlement_mths * monthly_payment;
    double balance_before_rebate = principal_plus_interest - amount_paid_to_date;
    double balance_tenure = (tenure_in_months - early_settlement_mths);
    double total_rebate = (balance_tenure * (balance_tenure+1)) / (tenure_in_months * (tenure_in_months+1)) * total_interest;
    double balance_after_rebate = balance_before_rebate - total_rebate;
    double total_spent = balance_after_rebate + amount_paid_to_date;

    cout << "==================================================" << endl;
    // cout << "Total Interest: RM " <<
    //     loan_amount * tenure * (interest_rate / 100.0)
    //     << endl;



    cout << "Principal Amount: RM" << loan_amount << endl;
    cout << "Total Interest for " << tenure_in_years << " tenure: RM" << total_interest << endl;
    cout << "Total Payment to Bank: RM" << principal_plus_interest << endl;
    cout << "Monthly Payment: RM" << monthly_payment << endl;
    cout << "Amount Paid-to-Date after " << early_settlement_mths << " months: RM" << amount_paid_to_date << endl;
    cout << "To Pay as Settlement after 24 months before rebate: RM" << balance_before_rebate << endl;
    cout << "Total Rebate from Settlement: RM" << total_rebate << endl;
    cout << "To Pay as Settlement after 24 months after rebate: RM" << balance_after_rebate << endl;
    cout << "Total spent on the car: RM" << total_spent << endl;
    cout << "==================================================" << endl;




    
    return 0;
}
