using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TemplateAccounts
{
    public class AccountTemplate
    {
        double _balance;


        public double GetBalance()
        {
            return _balance;
        }
        public void SetDeposit(double deposit)
        {
            _balance += deposit;
        }
    }
}
