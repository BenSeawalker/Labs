using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BankAccountLibrary
{
    public class BankAccount
    {
        const double interestRate = 0.06;
        const double taxRate = 0.25;
        double balance;

        public BankAccount()
        {
            balance = 0;
        }

        public void SetDeposit(double deposit)
        {
            balance += deposit;
        }

        public double GetBalance()
        {
            return balance;
        }

        public void PayYearlyInterest()
        {
            double grossInterestPayment = balance * interestRate;
            double netInterestPayment = grossInterestPayment - grossInterestPayment * taxRate;

            balance += netInterestPayment;
        }
    }
}
