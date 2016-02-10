using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OrdersDll
{
    public abstract class CardOrderDecorator : OrderDecorator
    {
        protected CardOrderDecorator(AbstractOrderBase inner) : base(inner)
        { }

        public override double GetTotalCost()
        {
            return GetCharge() + base.GetTotalCost();
        }

        public override void PrintOrderItems()
        {
            base.PrintOrderItems();
            Console.WriteLine("Total + {0:C} {1} charge {2:C}", GetCharge(), GetName(), GetTotalCost());
        }

        protected abstract double GetCharge();
        protected abstract string GetName();
    }
}
