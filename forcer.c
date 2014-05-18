#include <string>
#include <iostream>
#include <cryptopp/sha.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <time.h>       /* time */
#include <boost/thread/thread.hpp>





using namespace std;

boost::thread_group g;


void gen_random(string& s, const int len) {

        const char charset[] =
//                "0123456789"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
//                "abcdefghijklmnopqrstuvwxyz";
        for (int i = 0; i < len; ++i) {
                s[i] = charset[rand() % (sizeof(charset) - 1)];
        }
}


void force(string& prefix, int bf_length) {
  srand (time(NULL));
  string rand;
  rand.resize(bf_length);
  CryptoPP::SHA1 sha1;

  string total;
  while(true) {
    string hash = "";
    gen_random(rand, bf_length);
    string total = prefix + rand;
//    string total = prefix + rand + "\r\n";

    CryptoPP::StringSource(total, true, new CryptoPP::HashFilter(sha1, new CryptoPP::HexEncoder(new CryptoPP::StringSink(hash))));
    if(hash[0] == '0'
        && hash[1] == '0'
       && hash[2] == '0' 
       && hash[3] == '0' 
       && hash[4] == '0'
       && hash[5] == '0' ){

      cout << hash << endl;
      cout << total << endl;
      exit(0);
    }
  }

}



int main(int argc, char *argv[]) {
                        
        string prefix = string(argv[1]);
        int bf_length = 22 - prefix.length();
        unsigned int i;

       // HACK scoping issues with using aloop instad 
        boost::thread w1 = boost::thread(&force, prefix, bf_length);
        g.add_thread(&w1);
        boost::thread x1 = boost::thread(&force, prefix, bf_length);
        g.add_thread(&x1);
        boost::thread y1 = boost::thread(&force, prefix, bf_length);
        g.add_thread(&y1);
        boost::thread z1 = boost::thread(&force, prefix, bf_length);
        g.add_thread(&z1);
        boost::thread w2 = boost::thread(&force, prefix, bf_length);
        g.add_thread(&w2);
        boost::thread x2 = boost::thread(&force, prefix, bf_length);
        g.add_thread(&x2);
        boost::thread y2 = boost::thread(&force, prefix, bf_length);
        g.add_thread(&y2);
        boost::thread z2 = boost::thread(&force, prefix, bf_length);
        g.add_thread(&z2);

        g.join_all();



}
