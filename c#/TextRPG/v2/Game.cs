using System;
namespace CSharp
{
    public enum GameMode
    {
        None,
        Lobby,
        Town,
        Field
    }
    class Game
    {
        private GameMode _mode = GameMode.Lobby;
        private Player player = null;
        private Monster monster = null;
        private Random rand = new Random();

        public void Process()
        {
            switch (_mode)
            {
                case GameMode.Lobby:
                    ProcessLobby();
                    break;
                case GameMode.Town:
                    ProcessTown();
                    break;
                case GameMode.Field:
                    ProcessField();
                    break;
            }
        }

        private void ProcessLobby()
        {
            Console.WriteLine("Choose the Class");
            Console.WriteLine("[1] Knight");
            Console.WriteLine("[2] Archer");
            Console.WriteLine("[3] Mage");

            string input = Console.ReadLine();
            switch (input)
            {
                case "1":
                    player = new Knight();
                    _mode = GameMode.Town;
                    break;

                case "2":
                    player = new Archer();
                    _mode = GameMode.Town;
                    break;

                case "3":
                    player = new Mage();
                    _mode = GameMode.Town;
                    break;

            }
        }

        private void ProcessTown()
        {
            Console.WriteLine("Welcome to Town");
            Console.WriteLine("[1] Go to Field");
            Console.WriteLine("[2] Go to Lobby");

            string input = Console.ReadLine();
            switch (input)
            {
                case "1":
                    _mode = GameMode.Field;
                    break;

                case "2":
                    _mode = GameMode.Lobby;
                    break;
            }
        }

        private void ProcessField()
        {
            Console.WriteLine("Welcome to Field");
            Console.WriteLine("[1] Battle");
            Console.WriteLine("[2] Go to town with certain percentage");
            CreateRandomMonster();

            string input = Console.ReadLine();
            switch(input)
            {
                case "1":
                    ProcessFight();
                    break;
                case "2":
                    TryEscape();
                    break;
            }    
        }

        private void CreateRandomMonster()
        {
            int randVal = rand.Next(0, 3);
            switch (randVal)
            {
                case 0:
                    monster = new Slime();
                    Console.WriteLine("Slime Spawned");
                    break;
                case 1:
                    monster = new Orc();
                    Console.WriteLine("Orc Spawned");
                    break;
                case 2:
                    monster = new Skeleton();
                    Console.WriteLine("Skeleton Spawned");
                    break;
            }
        }

        private void ProcessFight()
        {
            while(true)
            {
                int damage = player.GetAttack();
                monster.OnDamaged(damage);
                if (monster.isDead())
                {
                    Console.WriteLine("Player won");
                    Console.WriteLine($"Player hp : {player.GetHP()}");
                    break;
                }

                damage = monster.GetAttack();
                player.OnDamaged(damage);
                if (player.isDead())
                {
                    Console.WriteLine("Monster won");
                    Console.WriteLine($"Player hp : {player.GetHP()}");
                    _mode = GameMode.Lobby;
                    break;
                }
            }
        }

        private void TryEscape()
        {
            int randVal = rand.Next(0, 101);
            if(randVal < 33)
            {
                _mode = GameMode.Town;
            }
            else
            {
                ProcessFight();
            }
        }
    }
}
