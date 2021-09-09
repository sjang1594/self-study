using System;

namespace CSharp
{
    class Program
    {
        enum PlayerType
        {
            None = 0,
            Knight = 1,
            Archer = 2,
            Mage = 3
        }

        enum MonsterType
        {
            None = 0,
            Slime = 1,
            Orc = 2,
            Skeleton = 3
        }

        struct Player
        {
            public int hp;
            public int attack;
        }

        struct Monster
        {
            public int hp;
            public int attack;
        }

        
        static PlayerType ChooseClass()
        {
            PlayerType classType = PlayerType.None;

            Console.WriteLine("What's class ?");
            Console.WriteLine("[1] Knight");
            Console.WriteLine("[2] Archer");
            Console.WriteLine("[3] Mage");

            string input = Console.ReadLine();

            switch (input)
            {
                case "1":
                    classType = PlayerType.Knight;
                    break;
                case "2":
                    classType = PlayerType.Archer;
                    break;
                case "3":
                    classType = PlayerType.Mage;
                    break;
            }

            return classType;
        }

        static void CreatePlayer(PlayerType choice, out Player player)
        {

            switch (choice)
            {
                case PlayerType.Knight:
                    player.hp = 100;
                    player.attack = 10;
                    break;
                case PlayerType.Archer:
                    player.hp = 75;
                    player.attack = 12;
                    break;
                case PlayerType.Mage:
                    player.hp = 50;
                    player.attack = 15;
                    break;
                default:
                    player.hp = 0;
                    player.attack = 0;
                    break;
            }
        }

        static void CreateRandomMonster(out Monster monster)
        {
            Random rand = new Random();
            int randMonster = rand.Next(1, 4);
            switch(randMonster)
            {
                case (int)MonsterType.Slime:
                    Console.WriteLine("Spawning the Slime...");
                    monster.hp = 20;
                    monster.attack = 2;
                    break;
                case (int)MonsterType.Orc:
                    Console.WriteLine("Spawning the Orc...");
                    monster.hp = 40;
                    monster.attack = 4;
                    break;
                case (int)MonsterType.Skeleton:
                    Console.WriteLine("Spawning the Skeleton");
                    monster.hp = 30;
                    monster.attack = 3;
                    break;
                default:
                    monster.hp = 0;
                    monster.attack = 0;
                    break;
            }
        }

        // Since player/monster object does not affect on the "player" object in
        // in main, have to use "ref"
        static void Fight(ref Player player, ref Monster monster)
        {
            while(true)
            {
                monster.hp -= player.attack;
                if(monster.hp <= 0)
                {
                    Console.WriteLine("You killed the monster");
                    Console.WriteLine($"Current HP : {player.hp}");
                    break;
                }

                player.hp -= monster.attack;
                if(player.hp <= 0)
                {
                    Console.WriteLine("You were Killed by the monster");
                    break;  
                }
            }
        }

        static void EnterField(ref Player player)
        {

            // Respawn one or three monster
            // [1] Combat mode
            // [2] Going back to village with certain percentage
            while (true)
            {
                Monster monster;
                CreateRandomMonster(out monster);

                Console.WriteLine("[1] Combat Mode");
                Console.WriteLine("[2] Going back to village");

                string input = Console.ReadLine();
                if(input == "1")
                {
                    Fight(ref player, ref monster);
                }
                else if(input == "2")
                {
                    // 33%
                    Random rand = new Random();
                    int randVal = rand.Next(0, 101);
                    if (randVal <= 33)
                    {
                        Console.WriteLine("Going back to village");
                        break;
                    }
                    else
                    {
                        Fight(ref player, ref monster);
                    }

                }
            }
        }

        static void EnterGame(ref Player player)
        {
            while (true) {
                Console.WriteLine("Entering the World");
                Console.WriteLine("[1] Going to Field");
                Console.WriteLine("[2] Going Back to Lobby");

                string input = Console.ReadLine();
                if(input == "1")
                {
                    //Enter Field
                    EnterField(ref player);
                }
                else if(input == "2")
                {
                    break;
                }
            }
        }

        static void Main(string[] args)
        {

            while (true)
            {
                PlayerType choice = ChooseClass();
                if (choice == PlayerType.None)
                    continue;
                    // Create a Character
                 Player player;

                 CreatePlayer(choice, out player);
                 Console.WriteLine($"HP: {player.hp} Attack: {player.attack}");

                 // Create a Monster
                 Monster monster;
                 CreateRandomMonster(out monster);
                 EnterGame(ref player);

            }
        }
    }
}
