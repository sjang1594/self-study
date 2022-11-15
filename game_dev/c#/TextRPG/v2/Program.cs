using System;

namespace CSharp
{
    class Program
    {
        static void Main(string[] args)
        {
            Game game = new Game();

            while (true)
            {
                game.Process();
            }
            
        }
    }
    
}
