using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TextUtils
{
    public class TextStatistics
    {
        //////////////////////////////////////////////////////////////////////
        // PROPERTIES
        //////

        public int WordCount { get; private set; }
        public int CharacterCount { get; private set; }
        //public int InstancesOfThe { get; private set; }
        public double AverageWordLength { get; private set; }

        private string Text;

        //////
        // END PROPERTIES
        //////////////////////////////////////////////////////////////////////

        public TextStatistics(string text)
        {
            Text = text;
            WordCount = TextCounter.CountWords(text);
            CharacterCount = TextCounter.CountCharacters(text);
            //InstancesOfThe = TextCounter.CountMatchingWords(text, "the");
            AverageWordLength = TextCounter.GetAverageWordLength(text);
        }

        public int InstancesOf(string matching)
        {
            return TextCounter.CountMatchingWords(Text, matching);
        }

    }
}
