class Language:
  default_lang = "English"

  def __init__(self):
    self.show = 'My Lang is ' + self.default_lang

  @classmethod
  def class_my_language(cls):
    return cls()


  @staticmethod
  def static_my_language():
    return Language()


  def print_language(self):
    print(self.show)


# Korean Language class is inherited from Language class
class KoreanLanguage(Language):
  default_lang = "Korean"

