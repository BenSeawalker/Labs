using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OrdersDll
{
    public class Order : AbstractOrderBase
    {
        public override void AddItem(string productCode, int quantity, double cost, double weight)
        {
            items.Add(new OrderItem(productCode, quantity, cost, weight));
        }        

        public override void PrintOrderItems()
        {
            foreach (OrderItem item in items)
            {
                Console.WriteLine("{0,-20:S} x {1,-5} @ {2,8:C} = {3,8:C}", item.ProductCode, item.Quantity, item.UnitCost, item.Cost);
            }
            Console.WriteLine();
            Console.WriteLine("Total Cost of Items {0:C}", GetTotalCost());
            Console.WriteLine();
        }

        public override double GetTotalCost() 
        {
            double total = 0;
            
            foreach (OrderItem item in items)
                total += item.Cost;

            return total;
        }
    }
}
