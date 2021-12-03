from abc import *

class Weapon(metaclass=ABCMeta):
  name = "weapon name"
  att_dmg = 0
  durability = 100

  @abstractmethod
  def attack(self):
    pass


# Gun
class Gun(Weapon):
  def __init__(self, name, att_dmg):
    self.name = name
    self.att_dmg = att_dmg

  def attack(self):
    self.durability -= 2
    print("%s %d %d" %(self.name, self.att_dmg, self.durability))


# Sword
class Sword(Weapon):
  def __init__(self, name, att_dmg):
    self.name = name
    self.att_dmg = att_dmg

  def attack(self):
    self.durability -= 5
    print("%s %d %d" %(self.name, self.att_dmg, self.durability))


# Bow
class Bow(Weapon):
  def __init__(self, name, att_dmg):
    self.name = name
    self.att_dmg = att_dmg

  def attack(self):
    self.durability -= 1
    print("%s %d %d" %(self.name, self.att_dmg, self.durability))
