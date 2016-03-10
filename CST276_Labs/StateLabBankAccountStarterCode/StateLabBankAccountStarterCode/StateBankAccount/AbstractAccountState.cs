using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;



namespace StateLabBankAccount
{
    internal abstract class AbstractAccountState
    {
        protected StateBankAccount account;

        protected AbstractAccountState(StateBankAccount _account)
        {
            account = _account;
        }

        public virtual void ConfirmIdentity(string pin)
        {
            throw new InvalidOperationException(GetType().Name);
        }

        public virtual void ActivateAccount()
        {
            throw new InvalidOperationException(GetType().Name);
        }

        public virtual void Credit(double amount)
        {
            throw new InvalidOperationException(GetType().Name);
        }

        public virtual void Debit(double amount)
        {
            throw new InvalidOperationException(GetType().Name);
        }

        public virtual void Freeze()
        {
            throw new InvalidOperationException(GetType().Name);
        }

        public virtual void UnFreeze()
        {
            throw new InvalidOperationException(GetType().Name);
        }

        public virtual void Close()
        {
            throw new InvalidOperationException(GetType().Name);
        }
    }
}
