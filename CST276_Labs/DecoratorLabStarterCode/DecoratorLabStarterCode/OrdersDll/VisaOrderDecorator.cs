using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OrdersDll
{
    public class VisaOrderDecorator : CardOrderDecorator
    {
        double _charge = 2.0;

        public VisaOrderDecorator(AbstractOrderBase inner) : base(inner)
        { }

        protected override double GetCharge()
        {
            return _charge;
        }

        protected override string GetName()
        {
            return "VISA";
        }
    }
}
