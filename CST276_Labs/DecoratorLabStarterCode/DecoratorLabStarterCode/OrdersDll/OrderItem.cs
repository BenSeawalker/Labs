using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OrdersDll
{
    public class OrderItem
    {
        public OrderItem(string productCode, int quantity, double unitCost, double unitWeight)
        {
            this.productCode = productCode;
            this.quantity = quantity;
            this.unitCost = unitCost;
            this.unitWeight = unitWeight;
        }

        private string productCode;
        public string ProductCode
        {
            get { return productCode; }
        }

        private int quantity;
        public int Quantity
        {
            get { return quantity; }
        }

        private double unitCost;
        public double UnitCost
        {
            get { return unitCost; }
        }

        public double Cost
        {
            get { return unitCost * quantity; }
        }

        private double unitWeight;
        public double UnitWeight
        {
            get { return unitWeight; }
        }

        public double GetWeight
        {
            get { return unitWeight * quantity; }
        }
    }
}
