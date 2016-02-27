using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InternalCompositeIteratorLibrary16
{
    public class CompositeIterator : AbstractIterator
    {
        Stack<AbstractIterator> stack;
        CompanyComponent inner;

        public CompositeIterator(CompanyComponent component)
        {
            inner = component;

            stack = new Stack<AbstractIterator>();
            stack.Push(inner.CreateIterator());
        }

        public void First()
        {
            stack.Peek().First();
        }

        public void MoveNext()
        {
            if (IsDone())
                throw new InvalidOperationException();

            if (stack.Peek().GetCurrent() is CompanyComposite)
            {
                stack.Push(stack.Peek().GetCurrent().CreateIterator());
            }
            else
            {
                stack.Peek().MoveNext();
            }
        }

        public CompanyComponent GetCurrent()
        {
            if (IsDone())
                throw new InvalidOperationException();

            return stack.Peek().GetCurrent();
        }

        public bool IsDone()
        {
            if(stack.Count == 0)
            {
                return true;
            }
            else if(stack.Peek().IsDone())
            {
                stack.Pop();
                if (stack.Count > 0)
                    stack.Peek().MoveNext();

                return IsDone();
            }
            else
            {
                return false;
            }
        }
    }
}
