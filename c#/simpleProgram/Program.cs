using System;

namespace c_
{
    class Program
    {
        static void Main(string[] args)
        {
            int multiplier = 1;
            int multiplicand = 2;

            for(int i = multiplicand; i <= 9; i++){
                for(int j = multiplier; j <= 9; j++){
                    System.Console.WriteLine($" {i} * {j} = {i*j}");
                }
            }
        }
    }
}
