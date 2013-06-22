def setup
  p 'A setup function'
  @x = 0
  @robot = Robot.new
end

def update
  @robot.update
  @x += 1
  # x
end

def draw
  @robot.draw
  puts "x = #{@x}"
end

# --------------------------------

class Robot
  def initialize
    @x = @y = 0
  end
  
  def update
    @x += 1
    @y += 2
  end

  def draw
    p "Robot => x:#{@x}, y:#{@y}"
  end
end


