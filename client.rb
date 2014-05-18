require 'eventmachine'




class Echo < EventMachine::Connection
  def post_init
  end

  def unbind
    puts "Lost connection :("
  end

  def receive_data(data)
    p data
    if data.include?("of length")
      prefix = data.split(" ")[0]
      puts "Need to find input for prefix: #{prefix}"
        data = `./a.out #{prefix}`
        response = data.split("\n")[1]
        response = response.strip + "\n"
        puts "Sending: #{response}"
        send_data response
        send_data "Harmon\n"
    end


  end
end


EM.run do
  EM.connect('dosfun4u_5d712652e1d06a362f7fc6d12d66755b.2014.shallweplayaga.me', 8888, Echo)
end
