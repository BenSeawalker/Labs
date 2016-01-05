using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TextUtils
{
    public static class TextCounter
    {
        private const string WhiteSpace = " ,.?!;:\"-\n\r";

        //////////////////////////////////////////////////////////////////////
        // PUBLIC
        //////

        public static int CountCharacters(string text)
        {
            return text.Length;
        }

        public static int CountWords(string text)
        {
            string[] words = GetWords(text);

            return words.Length;
        }

        public static double GetAverageWordLength(string text)
        {
            string[] words = GetWords(text);
            string wordCharacters = String.Concat(words);

            return (double)wordCharacters.Length / (double)words.Length;
        }


        public static int CountMatchingWords(string text, string targetWord)
        {
            int matchCount = 0;
            string[] words = GetWords(text);
            
            foreach (string word in words)
                if (word == targetWord)
                    matchCount++;

            return matchCount;
        }


        //////
        // END PUBLIC
        //////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////
        // PRIVATE
        //////

        private static string[] GetWords(string text)
        {
            string[] words = text.Split(WhiteSpace.ToCharArray());
            return words;
        }

        //////
        // END PRIVATE
        //////////////////////////////////////////////////////////////////////

    }
}
