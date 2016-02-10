using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OrdersDll
{
    public abstract class AbstractOrderBase
    {
        protected List<OrderItem> items = new List<OrderItem>();

        public abstract double GetTotalCost();

        public abstract void PrintOrderItems();

        public abstract void AddItem(string productCode, int quantity, double cost, double weight);
    }
}
