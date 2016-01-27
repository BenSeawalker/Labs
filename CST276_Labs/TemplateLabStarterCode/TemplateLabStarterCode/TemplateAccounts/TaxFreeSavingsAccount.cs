using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TemplateAccounts
{
    public class TaxFreeSavingsAccount : AccountTemplate
    {
        const double interestRate = 0.06;
        const double taxRate = 0.0;

        public TaxFreeSavingsAccount()
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
