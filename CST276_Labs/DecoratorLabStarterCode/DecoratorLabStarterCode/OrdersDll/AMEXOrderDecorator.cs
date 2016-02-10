using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OrdersDll
{
    public class AMEXOrderDecorator : CardOrderDecorator
    {
        double _charge = 5.0;

        public AMEXOrderDecorator(AbstractOrderBase inner) : base(inner)
        { }

        protected override double GetCharge()
        {
            return _charge;
        }

        protected override string GetName()
        {
            return "AMEX";
        }
    }
}
