class CustomClass:

  # instance method
  def add_instance_method(self, a, b):
    return a + b

  # class method
  @classmethod
  def add_class_method(cls, a, b):
    return a + b

  # static method
  @staticmethod
  def add_static_method(a, b):
    return a + b
