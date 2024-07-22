#include <iostream>
#include <vector>
#include <openssl/md5.h>

class BloomFilter
{
    int nHashes;
    std::vector<bool> bits;

    static constexpr int hashSize = 128 / 8; // 128 Bit / 16 Bytes 
    unsigned char hashValue[hashSize];

public:
    BloomFilter(int size, int hashes) : bits(size), nHashes(hashes)
    {
        if (nHashes > hashSize)
            throw("Too much hash function");
        if (size > 255)
            throw("Bloom Filter Can have more than 255 bits");
    }

    void hash(const std::string key)
    {
        MD5(reinterpret_cast<const unsigned char*>(key.data()), key.length(), hashValue);
    }

    void add(const std::string& key)
    {
        hash(key);
        for (auto it = &hashValue[0]; it < &hashValue[nHashes]; it++)
        {
            bits[*it % bits.size()] = true;
        }
    }

    bool mayContain(const std::string& key)
    {
        hash(key);
        for (auto it = &hashValue[0]; it < &hashValue[nHashes]; it++)
        {
            if (!bits[*it % bits.size()])
            {
                return false;
            }
        }

        // Taken
        return true;
    }
};

int main()
{
    BloomFilter bloom(128, 5);

    bloom.add("abc@gilbut.com");
    bloom.add("xyz@gilbut.com");

    bloom.mayContain("abc");
    bloom.mayContain("xyz@gilbut.com");
    bloom.mayContain("xyz");

    bloom.add("abcd@gilbut.com");
    bloom.add("ab@gilbut.com");

    bloom.mayContain("abcd");
    bloom.mayContain("ab@gilbut.com");
}