#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here

        //initialize values
        HASH_INDEX_T w[5] {0,0,0,0};

        int idx = 4;
        HASH_INDEX_T decimal = 0;


        int end = k.length()-1;
        int start = (end-5>0) ? end-5:0;
        int next = start-1;

        //iterate through length of 5 substring
        while(start<=end)
        {
          //conver to corresponding number and update decimal
          decimal = decimal*36 + letterDigitToNumber(k[start]);
          ++start;

          //check if end of substing is reached
          if(start>end)
          {
            //update start and end
            if(next >=5)
            {
              start = next -5;
            }
            else
            {
              start = 0;
            }
            end = next;
            next = start-1;

            w[idx--] = decimal;
            decimal=0;
          }
        }
        //calculate the final hash value
        HASH_INDEX_T r = rValues[0]*w[0] + rValues[1]*w[1] + rValues[2]*w[2] + rValues[3]*w[3] +rValues[4]*w[4];

        return r;

      



    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it

        if(isdigit(letter))
        {
          return letter - '0' + 26;
        }
        else if(isalpha(letter))
        {
          return tolower(letter) - 'a';
        }
        return 0;

    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
