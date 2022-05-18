// djb2
// k=33
// The starting number 5381 was picked by djb simply 
// because testing showed that it results in fewer 
// collisions and better avalanching.
// xor: hash(i) = hash(i - 1) * 33 ^ str[i]


unsigned long hashFunction(char *str)
{
    unsigned long hash = 5381;
    int c;

    while(c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}






// sdbm
// the actual function is hash(i) = hash(i - 1) * 65599 + str[i]; 
// what is included below is the faster version used in gawk. [there is even a faster, 
// duff-device version] the magic constant 65599 was picked out of thin air while 
// experimenting with different constants, and turns out to be a prime


// unsigned long hashFunction(char *str)    
// {
//     unsigned long hash = 0;
//     int c;

//     while (c = *str++)
//         hash = c + (hash << 6) + (hash << 16) - hash;

//     return hash;
// }






// A good second Hash function is: 
// It must never evaluate to zero
// Must make sure that all cells can be probed


unsigned long auxHashFunction(char *str)
{
    unsigned long hash = 0x55555555;

    while (*str) { 
        hash ^= *str++;
        hash = (hash << 5) | (hash >> (32 - 5));
    }

    return hash;
}