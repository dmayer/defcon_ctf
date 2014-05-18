require 'digest/sha1'

prefix = ARGV[0]
total_length = 22
bf_len = total_length - prefix.length
puts "Creating a bf string of #{bf_len}"


while true do
        bf_string = ('A'..'z').to_a.shuffle[0,bf_len].join
        total_string = prefix + bf_string

        digest = Digest::SHA1.hexdigest total_string
        if digest[0,6] == "0" * 6
                puts total_string
                puts digest
                exit 0
        end
end

