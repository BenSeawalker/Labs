using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TemplateAccounts
{
    public class VariableInterestAccount : AccountTemplate
    {
        const double lowInterestRate = 0.05;
        const double midInterestRate = 0.06;
        const double highInterestRate = 0.08;
        const double taxRate = 0.0;

        public VariableInterestAccount()
        {
            balance = 0.0;
        }

        protected override double GetInterestRate()
        {
            double interestRate = lowInterestRate;
            if (balance >= 6000)
                interestRate = highInterestRate;
            else if (balance > 1000)
                interestRate = midInterestRate;

            return interestRate;
        }

        protected override double GetTaxRate()
        {
            return taxRate;
        }
    }
}
