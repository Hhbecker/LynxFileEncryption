# LynxFileEncryption
A text file encryption application 

<img src="images/lynxMeganLorenz.jpg" width="600px" height="400px">

A block cipher consists of two paired algorithms, one for encryption, E, and the other for decryption, D.[1] Both algorithms accept two inputs: an input block of size n bits and a key of size k bits; and both yield an n-bit output block. The decryption algorithm D is defined to be the inverse function of encryption, i.e., D = E−1. More formally,[2][3] a block cipher is specified by an encryption function

Many modern block ciphers and hashes are ARX algorithms—their round function involves only three operations: (A) modular addition, (R) rotation with fixed rotation amounts, and (X) XOR.

These ARX operations are popular because they are relatively fast and cheap in hardware and software, their implementation can be made extremely simple, and also because they run in constant time, and therefore are immune to timing attacks. The rotational cryptanalysis technique attempts to attack such round functions.


## Add (Caesar Cipher)
Casaer shifted each letter in his military commands to make them appear meaningless to the enemy if they were intercepted. The weakness of the ceasar cipher is that each letter in any language has a given fre   uency of use. This use frequency can be thought of as the language's fngerprint. By comparing frequencies of cipher letters to the known freuency of letters in the language being encrypted with enough data one can determine the shift used to encrypt the original message. This is known as frequency analysis and is the most important weakness of the Caesar cipher.

Each letter in a message is shifted to one of twenty six possible letters. Therefore, there are 26 possible combinations for any message encrypted using the Caesar Cipher.

## Rotate (Bit Shift) 


## XOR (Viginere Cipher) 
Because there is no pseudorandom number function I could implement a pseudorandom number generator in assembly to create a OTP like cipher. Additionally, the Viginere cipher could be used which is a less secure predecessor to the OTP method. The Viginere cipher uses the XOR operation based on an input key to encrypt the message. 

## The OTP (Vernam) Cipher 
The OTP cipher or One Time Pad cipher encrypts a message using a key of random numbers as long as the message itself. Each number in the key is used to shift each character in the message. Because there are 26 letters in the alphabet there are 26 additional combinations for each character in a message resulting in 

The OTP cipher has very little information leak. If the key is generated randomly the shifts of each character in the message will never fall into a repetitive pattern. This means the frequency distribution of characters in the cipher text will be uniform preventing the use of frequency analysis by a code breaker.  

While OTP is impossible to break, if software provides feedback on wether the message has been decrypted correctly the attacker could theoretically brute force each possible key until the system confirms the key is correct. Therefore, some systems limit the number of password entry attempts while other systems require keys large enough that brute force attack would take an impractical amount of time based on the current limits of computing power.


# The calculations change if you're using alphanumeric or all ascii !!!!!

## Perfect Secrecy
A cipher strategy accomplishes perfect secrecy if an attacker can not glean any additional information about the original message when given the ciphertext.

Say you want to encrypt a 10 letter message. Because there are 26 letters in the alphabet and the message is 10 letters long, there are 26^10th possible messages you could encrypt. This is called the message space. If a key to encrypt this 10 letter message is randomly generated, the key space will include 10 random numbers between 1 and 26. This is called the key space and also contains 26^10 possibilites. The key is used to create a ciphertext which is composed of 10 randomly shifted characters each of which has 26 possibilities making the ciphertet space 26^10 as well. This method accomplishes perfect secrecy because it is equally likely that each message in the message space will be paired with any key in the key space resulting in an equal probability of any ciphertext in the ciphertext space. Therefore, if an attacker is given the ciphertext, the best the attacker can do is guess any of the 26^10 possible keys and messages. In other words, the OTP method is perfectly secret because the message space is not narrowed down at all if the ciphertext is revealed. 


## Random vs Pseudorandom 
Perfectly random fluctuations occur constantly in nature. A sequence is random or "nondeterministic" if the next number in the sequence to be generated is impossible to determine in advance. Computers are deterministic because the output can always be determined if the current state and input is known. Therefore, computers cannot generate perfectly random numbers on their own. There are many algorithms that can mechanically simulate randomness which is called pseudorandomness. These algorithms rely on a seed which is chosen by the operator. The seed is then mutated by some operation to produce a pseudorandom number. The next seed is taken from this number and the same operation is performed to produce the next pseudorandom number. This process is repeated until the adequate number of pseudorandom numbers has been produced. Keep in mind the algorithm will produce the same sequence each time the same initial seed is entered. These algorithms are pseudorandom because the sequence of numbers will eventually repeat once the initial seed is regenerated by the algorithm. The length of the sequence before a pseudorandom sequence repeats is called the period. If a large enough seed is chosen and the algorithm is robust enough, the period will be large enough that the numbers generated will be random enough for all practical intents and purposes. 

## Speck Cipher
The OTP method requires a key as long as the message text. This can become very vomputationally intensive as the size of the message grows. ARX (Add Rotate Xor) ciphers are used in substitute of the OTP method because they are less computationally intensive and still provide robust security. 

## The Icloud Keychain
As a mac user I have been saved from password resetting by the icloud keychain many times. This apple password management application automatically saves passwords during login to web accounts. These passwords can then  be retrieved by loggin into the Keychain app using the admin password. I wanted to know how icloud Keychain works so I did a little research: Icloud Keychain uses 256-bit AES encryption and also uses elliptic curve asymmetric cryptography and key wrapping to store and transmit passwords and credit card information.

#### 256-bit AES encryption
AES-256, which has a key length of 256 bits, supports the largest bit size and is practically unbreakable by brute force based on current computing power, making it the strongest encryption standard.

#### elliptical curve asymetric cryptography

#### key wrapping

AES (Advanced Encryption Standard) and DES (Data Encryption Standard)


confusion and diffusion are two properties of the operation of a secure cipher which were identified by Claude Shannon in his paper Communication Theory of Secrecy Systems, published in 1949.

confusion refers to making the relationship between the key and the ciphertext as complex and involved as possible; diffusion refers to the property that the redundancy in the statistics of the plaintext is "dissipated" in the statistics of the ciphertext. In other words, the non-uniformity in the distribution of the individual letters (and pairs of neighbouring letters) in the plaintext should be redistributed into the non-uniformity in the distribution of much larger structures of the ciphertext, which is much harder to detect.

Substitution = a is swapped for z
Permutation = the order of the swapped letters is scrambled 


Confusion 
Achieved using substitution 

Diffusion
Achieved using transposition or permutation


#### Block Cipher 
a block cipher is a deterministic algorithm operating on fixed-length groups of bits, called blocks.

Stream ciphers encrypt messages one bit at a time while block ciphers encrypt blocks of bits
Stream ciphers are faster. they're better when input size is not known.





Thank you to Brit Cruise for the Kahn Academy cryptography course from which much of the below information was gathered. You can find the course here: https://www.khanacademy.org/computing/computer-science/cryptography/crypt/v/caesar-cipher


# To Do
* decide which ciphers you're actually going to implement 
* there is no random number genrator in assembly so maybe a real OTP is a waste of time
* restructure beginning section where user enters key and key is checked 
* explain specs in README 
* tkae notes in OTP encryption and icloud keychain 

* maybe split each cipher into different files 

* echo a * if you can for each letter typed for the key or message 

* make test cases 
* make a diagram of the project flow 
* make a written explanation of the encryption and decryption of a test case 

* instead of combining the three ciphers maybe prompt the user for either a ceasar, OTP, or bit shift or combination

How to write portable assembly code 

How to write portable c code 
https://nullprogram.com/blog/2017/03/30/

https://www.informit.com/articles/article.aspx?p=1620206




C implementation notes
* C opens, encrypts, and closes file 

* block or stream cipher? the msg could be of any length

Options:
* OTP encryption with from scratch pseudorandom number generator 
* ARX block cipher

Input e for encrypt, d for decrypt, and x to exit 

extended asm - writing assembly in c code
https://gcc.gnu.org/onlinedocs/gcc/Extended-Asm.html

How to hide files on a mac 
https://www.howtogeek.com/211496/how-to-hide-files-and-view-hidden-files-on-mac-os-x/#:~:text=Hide%20a%20File%20or%20Folder%20on%20a%20Mac&text=Drag%2Dand%2Ddrop%20a%20folder,file%20or%20folder%20will%20vanish.




