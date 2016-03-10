using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Windows.Forms;


namespace StateLabBankAccount
{
    public partial class StateBankAccount
    {
        const string valid_pin = "1234";
        double balance;
        double Balance
        {
            get { return balance; }
            set { balance = value; }
        }

        ConfirmingIdentityState confirmingIdentityState;
        ActiveState activeState;
        FrozenState frozenState;
        ClosingState closingState;
        ClosedState closedState;

        AbstractAccountState state;


        public StateBankAccount()
        {
            confirmingIdentityState = new ConfirmingIdentityState(this);
            activeState = new ActiveState(this);
            frozenState = new FrozenState(this);
            closingState = new ClosingState(this);
            closedState = new ClosedState(this);

            state = confirmingIdentityState;
            balance = 0.0;
        }


        public void ConfirmIdentity(string pin)
        {
            try
            {
                state.ConfirmIdentity(pin);
            }
            catch (System.InvalidOperationException ex)
            {
                Console.WriteLine(string.Format("Unable to confirm identity! Invalid state: {0}", ex.Message));
            }
            
        }

        public void Credit(double amount)
        {
            try
            {
                state.Credit(amount);
            }
            catch (System.InvalidOperationException ex)
            {
                Console.WriteLine(string.Format("Unable to credit account! Invalid state: {0}", ex.Message));
            }
        }

        public void Debit(double amount)
        {
            try
            {
                state.Debit(amount);
            }
            catch (System.InvalidOperationException ex)
            {
                Console.WriteLine(string.Format("Unable to debit account! Invalid state: {0}", ex.Message));
            }
        }

        public void Freeze()
        {
            try
            {
                state.Freeze();
            }
            catch (System.InvalidOperationException ex)
            {
                Console.WriteLine(string.Format("Unable to freeze account! Invalid state: {0}", ex.Message));
            }
        }

        public void Unfreeze()
        {
            try
            {
                state.UnFreeze();
            }
            catch (System.InvalidOperationException ex)
            {
                Console.WriteLine(string.Format("Unable to unfreeze account! Invalid state: {0}", ex.Message));
            }
        }

        public void Close()
        {
            try
            {
                state.Close();
            }
            catch (System.InvalidOperationException ex)
            {
                Console.WriteLine(string.Format("Unable to close account! Invalid state: {0}", ex.Message));
            }
        }


        void InternalIdentityConfirmed(string pin)
        {
            if (pin != valid_pin)
            {
                Console.WriteLine("Identity not confirmed, account closing");
                state.Close();
            }
        }

        void InternalCredit(double amount)
        {
            Console.WriteLine("Credit {0:C} current balance is {1:C} ", amount, balance);
        }

        void InternalDebit(double amount)
        {
            Console.WriteLine("Debit {0:C} current balance is {1:C} ", amount, balance);
        }

        void InternalFreeze()
        {
            Console.WriteLine("Freezing Account");
        }

        void InternalUnfreeze()
        {
            Console.WriteLine("Unfreezing Account");
        }

        void InternalClosing()
        {
            if(balance < 0)
            {
                Console.WriteLine("You can't close an overdrawn account, current balance is: {0:C} ", balance);
                //MessageBox.Show(String.Format("You can't close an overdrawn amount, current balance is: {0:C} ", balance));
            }
            else
            {
                Console.WriteLine("Account closing");
                //MessageBox.Show("Account closing");
            }
        }

        void InternalClose()
        {
            if (balance == 0)
            {
                Console.WriteLine("Balance is $0.0, account closed");
                //MessageBox.Show("Balance is $0.0, account closed");
            }
            else if (balance > 0)
            {
                Console.WriteLine("Check for {0:C} is in the mail, account closed", balance);
                //MessageBox.Show(String.Format("Check for {0:C} is in the mail, account closed", balance));
            }
        }
    }
}
