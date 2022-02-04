# LynxFileEncryption
A text file encryption application 

<img src="images/lynxMeganLorenz.jpg" width="600px" height="400px">
Wild Canadian Lynx photographed by Megan Lorenz <br /><br />

<br /><br/>


# To Do
* make a typescript of the output of a shorter quote (and include it in the test file)
* make a secret message binary file in test files
* finish readme explanations

The Lynx file encryption system dgitizes the OTP encryption technqiue to efficiently and reliably encrypt sensitive text data. I created this application while learning about different encryption strategies, their strengths, and their weaknesses. I got curious about encryption after realizing I didn't know how the icloud keychain stored my passwords and other sensitive information. This project is really just a proof of concept and a learning exercise. I did not spend too long on any one feature so there are several weaknesses which I'll discuss later. I've included my design plans, an explanation of my impelmentation, example input/output, and notes on what I learned during the process. I hope you enjoy!

## System Overview
The Lynx file encryption system digitizes the OTP (one time pad) encryption technique. In this technique, newly pseudorandomly generated keys are XOR'd with each character of the plaintext. I implemented the driver and function bodies in C but used inline assembly to perform the XOR operation on both encryption and decrpytion (see section on assembly below).  

#### To create and retrieve key for a given file
1. create binary file during encryption process
2. use seconds of file creation time as seed for key during encryption
3. retrieve seconds of file creation as seed for key during decryption



This diagram shows each method and the abbreviated control flow.

<img src="images/controlFlow.jpeg">

### Perfect Secrecy
The cryptographer's goal is to create a ciphertext that leaks no information about the plaintext message. The One Time Pad encryption technique accomplishes perfect secrecy. The OTP technique requries creates a cipher text by performing an XOR on each character of the plaintext with a new randomly generated number for each character. This method is perfectly secret if the following conditions are met:

1. The key must be at least as long as the plaintext.
2. The key must be random (uniformly distributed in the set of all possible keys and independent of the plaintext.
3. The key must never be reused in whole or in part.
4. The key must be kept completely secret by the communicating parties. 

Randomly generated keys XOR'd with each character in the plaintext produce a perfectly secret ciphertext because each key in the key space would produce a different output and there is no statistical preference for any one key in the key space being selected over any other key in the key space. This means each character in the ciphertext is equally likely to be the actual plaintext character as it is any other possible character in the encoding. 

Although the OTP method is immune to cryptanalysis its main point of failure is the need to transmit plaintext key information (either a key sheet or seed for a PSRNG) to the intended recipient of the ciphertext.

### Why is XOR used in the One Time Pad encryption? 
1. **XOR is balanced:** For a given plaintext input (0 or 1), the ciphertext result is equally likely to be either 0 or 1 for a truly random key bit.
2. **XOR is reversible:** An XOR of any pair of either the plaintext, key, or ciphertext will produce the third item. 

### Implementing XOR using inline x86 assembly
I think it is so cool that C has support for inline assembly. Because I have an intel based mac I needed to use the so called AT&T assembly syntax. 

```
 __asm__ ( "xorb %%bl, %%al;"
            : "=a" (currentChar)
            : "a" (currentChar), "b" (key) );
```

`xorb` = opcode for xor on a single byte of data <br />
`%%bl` = source register is the lowest 8 bits of the general purpose EBX register <br /> 
`%%al` = destination register (also a source register) is the lowest 8 bits of the general purpose EAX register <br />
`: "=a" (currentChar)` = save results of register a (low byte of EAX) into the currentChar variable <br />
`: "a" (currentChar), "b" (key) )` = save the value of the currentChar variable into register a and the value of the key variable key into register b <br />

I was hoping for a massive speedup using assembly but after testing the time and cycles I found the assembly was 

I used the following resources when implementing this inline assembly:
https://www.codeproject.com/Articles/15971/Using-Inline-Assembly-in-C-C
https://www.eecg.utoronto.ca/~amza/www.mindsec.com/files/x86regs.html

### Pseudorandom Number Generation (PSRNG)
An early computer-based PRNG, suggested by John von Neumann in 1946, 
is known as the middle-square method. The algorithm is as follows: 
take any number, square it, remove the middle digits of the resulting 
number as the "random number", then use that number as the seed for the 
next iteration.


Show your key generation formula (or switch to using von neumanns). 


Perfectly random fluctuations occur constantly in nature. A sequence is random or "nondeterministic" if the next number in the sequence to be generated is impossible to determine in advance. Computers are deterministic because the output can always be determined if the current state and input is known. Therefore, computers cannot generate perfectly random numbers on their own. There are many algorithms that can mechanically simulate randomness (pseudorandomness). These algorithms rely on a seed which is chosen by the operator. The seed is then mutated by some operation to produce a pseudorandom number. The next seed is taken from this number and the same operation is performed to produce the next pseudorandom number. This process is repeated until the adequate number of pseudorandom numbers has been produced. Keep in mind the algorithm will produce the same sequence each time the same initial seed is entered. These algorithms are pseudorandom because the sequence of numbers will eventually repeat once the initial seed is regenerated by the algorithm. The length of the sequence before a pseudorandom sequence repeats is called the period. If a large enough seed is chosen and the algorithm is robust enough, the period will be large enough that the numbers generated will be random enough for all practical intents and purposes. 


### Secret Seed Generation
The seed is the creation time of the binary file (not the text file). It is important to note that some editors (inlcuding vim) will create an entirely new file during the edit process so if a user was to edit the binary file the seed would be lost and the encrypted data is no longer unencryptable (practically speaking of course). 

I used the following bash command via the system() C function to retrieve the seconds of the file creation time for use as the PSRNG seed.


### keyboard to binary explanation
make explanation of keyboard input as ascii which is converted to binary that's stored in a 32 bit space (explain address size, addressability, word size, and byte addressible) (is 8 bits one byte the smallest addressable space in my computer?)

### Cryptanalysis
This is my attempt at crpytanalysis of Lynx ecnryption.

Say you want to encrypt a 10 letter message. Because there are 26 letters in the alphabet and the message is 10 letters long, there are 26^10th possible messages you could encrypt. This is called the message space. If a key to encrypt this 10 letter message is randomly generated, the key space will include 10 random numbers between 1 and 26. This is called the key space and also contains 26^10 possibilites. The key is used to create a ciphertext which is composed of 10 randomly shifted characters each of which has 26 possibilities making the ciphertet space 26^10 as well. This method accomplishes perfect secrecy because it is equally likely that each message in the message space will be paired with any key in the key space resulting in an equal probability of any ciphertext in the ciphertext space. Therefore, if an attacker is given the ciphertext, the best the attacker can do is guess any of the 26^10 possible keys and messages. In other words, the OTP method is perfectly secret because the message space is not narrowed down at all if the ciphertext is revealed. 





### Highlights for me
1. Using inline assembly for the first (but not the last) time
2. Learning more about the system command, sed, grep, and regex in order to use them
3. Learning more about ciphers, pseudorandom number generation, and the points of failure in different encryption strategies
3. making the ascii art lynx 


#### Weaknesses 
* The seed is set by file timestamp which is changed if file is edited by vim because vim creates a new file each time you edit.

* filename generator separates file extension by finding first "." character so if there are more than one "." characters in a filename it will change the filename incorrectly.

* It can take non .txt files which I think is a problem?

* It is not portable at all because it uses c and intel based assembly. 
* it is susceptible to brute force attacks based on the processing power of modern computers.

If you encrypt an already encrypted file you can't unencrypt that file because of the file name issues?

### Testing Instructions
If you are using an intel based mac running OSX Big Sur there is a chance this might also work on your machine (C with inline assembly is from my understanding almost never portable). Download the SRC directory and `cd` into it. run `make` to create the "lynx" executable. Run `./lynx` to run the executable. The testFiles directory contains .txt files that can be used to test encryption and decryption. Make sure to include the directory before the file name (for example: `testDir/200wordTest.txt`). 

### Sources:
https://www.khanacademy.org/computing/computer-science/cryptography/crypt/v/caesar-cipher


