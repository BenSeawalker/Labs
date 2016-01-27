using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TemplateAccounts
{
    public class ClassicAccount : AccountTemplate
    {
        const double interestRate = 0.06;
        const double taxRate = 0.25;

        public ClassicAccount()
        {
            balance = 0.0;
        }

        protected override double GetInterestRate()
        {
            return interestRate;
        }

        protected override double GetTaxRate()
        {
            return taxRate;
        }
    }
}
