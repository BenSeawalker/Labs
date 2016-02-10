using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OrdersDll
{
    public class ExpressDeliveryOrderDecorator : OrderDecorator
    {
        const double _charge = 4.0;

        public ExpressDeliveryOrderDecorator(AbstractOrderBase inner) : base(inner)
        {}

        public override double GetTotalCost()
        {
            return _charge + base.GetTotalCost();
        }

        public override void PrintOrderItems()
        {
            base.PrintOrderItems();
            Console.WriteLine("Grand Total with Shipping {0:C}", GetTotalCost());
        }
    }
}
