using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

using TextUtils;

namespace Architecture
{
    class Program
    {
        static void Main(string[] args)
        {
            StreamReader reader = new StreamReader(@"..\..\..\hamlet.txt");
            string text = reader.ReadToEnd();
            reader.Close();

            TextStatistics stats = new TextStatistics(text);

            Console.WriteLine("\nThe number of characters is: {0}\n", stats.CharacterCount);
            Console.WriteLine("The number of words is: {0}\n", stats.WordCount);
            Console.WriteLine("The average word length is: {0}\n", stats.AverageWordLength);
            Console.WriteLine("The number of instances of \"the\" is: {0}\n", stats.InstancesOf("the"));
        }
    }
}
