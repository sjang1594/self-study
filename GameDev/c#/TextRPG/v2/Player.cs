using System;

namespace CSharp
{
    public enum PlayerType
    {
        None = 0,
        Knight = 1,
        Archer = 2,
        Mage = 3
    }

    class Player : Creature
    {
        protected PlayerType _type = PlayerType.None;

        // Take the type as argument
        protected Player(PlayerType type) : base(CreatureType.Player)
        {
            _type = type;
        }

        public PlayerType GetPlayerType() { return _type; }

    }

    class Knight : Player
    {
        public Knight() : base(PlayerType.Knight)
        {
            SetInfo(100, 10);
        }
    }

    class Archer : Player
    {
        public Archer() : base(PlayerType.Archer)
        {
            SetInfo(75, 12);
        }
    }

    class Mage : Player
    {
        public Mage() : base(PlayerType.Archer)
        {
            SetInfo(50, 15);
        }
    }
}
