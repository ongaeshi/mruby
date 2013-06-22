# person.rb

class Person
  attr_accessor :name, :age

  def initialize(name, age)
    @name = name
    @age = age
  end

  def greeting
    "Hello, my name is #{name}, #{age} years old."
  end
end

