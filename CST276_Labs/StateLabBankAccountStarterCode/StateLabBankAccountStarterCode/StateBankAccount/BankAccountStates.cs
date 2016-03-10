using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace StateLabBankAccount
{
    partial class StateBankAccount
    {
        class ConfirmingIdentityState : AbstractAccountState
        {
            public ConfirmingIdentityState(StateBankAccount account) : base(account)
            {}

            public override void ConfirmIdentity(string pin)
            {
                if(pin == valid_pin)
                    account.state = account.activeState;

                account.InternalIdentityConfirmed(pin);
            }

            public override void Close()
            {
                account.state = account.closedState;
            }
        }

        class ActiveState : AbstractAccountState
        {
            public ActiveState(StateBankAccount account) : base(account)
            {}

            public override void Credit(double amount)
            {
                account.balance += amount;
                account.InternalCredit(amount);
            }

            public override void Debit(double amount)
            {
                account.balance -= amount;
                account.InternalDebit(amount);
            }

            public override void Freeze()
            {
                account.state = account.frozenState;
                account.InternalFreeze();
            }

            public override void Close()
            {
                if (account.balance < 0)
                {
                    account.state = account.closingState;
                    account.InternalClosing();
                }
                else
                {
                    account.state = account.closedState;
                    account.InternalClose();
                }
            }
        }

        class FrozenState : AbstractAccountState
        {
            public FrozenState(StateBankAccount account) : base(account)
            {}

            public override void UnFreeze()
            {
                account.state = account.activeState;
                account.InternalUnfreeze();
            }
        }

        class ClosingState : AbstractAccountState
        {
            public ClosingState(StateBankAccount account) : base(account)
            {}

            public override void Credit(double amount)
            {
                account.balance += amount;
                account.InternalCredit(amount);
            }

            public override void Close()
            {
                if (account.balance >= 0)
                {
                    account.state = account.closedState;
                    account.InternalClose();
                }
                else
                {
                    account.InternalClosing();
                }
            }
        }

        class ClosedState : AbstractAccountState
        {
            public ClosedState(StateBankAccount account) : base(account)
            {}
        }
    }
}
