using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Threading;


namespace Command
{
    public class BatchInvoker : IInvoker
    {
        List<ICommand> _commands;
        int _batchSize;

        public BatchInvoker(int batchSize = 5)
        {
            _commands = new List<ICommand>();
            _batchSize = batchSize;
        }

        public void Execute(ICommand command)
        {
            _commands.Add(command);

            if (_commands.Count >= _batchSize)
            {
                foreach (ICommand cmd in _commands)
                    cmd.Execute();

                _commands.Clear();
                Thread.Sleep(500);
            }
        }
    }
}
