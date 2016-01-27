using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TemplateAccounts
{
    public abstract class AccountTemplate
    {
        protected double balance;

        public double GetBalance()
        {
            return balance;
        }

        public void SetDeposit(double deposit)
        {
            balance += deposit;
        }

        public void PayYearlyInterest()
        {
            double grossInterestPayment = balance * GetInterestRate();
            double netInterestPayment = grossInterestPayment - grossInterestPayment * GetTaxRate();

            balance += netInterestPayment;
        }


        protected abstract double GetInterestRate();
        protected abstract double GetTaxRate();
    }
}
