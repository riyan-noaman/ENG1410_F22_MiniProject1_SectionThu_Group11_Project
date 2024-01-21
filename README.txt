This system allows a user to enter a file for it to be encrypted or decrypted 
The user will be asked if they want to encrypt or decrypt at the start of the program 
	To encrypt, the user must type either "-e" or "-E"
	To decrypt, the user must type either "-d" or "-D" 
	If the user does not specify what they wish to do, the program automatically assumes encryption 

The user will then be asked to enter the file they want to modify 	
	The user must ensure that their path is correct or that the file is within the "cmake-build-debug" 
	folder if they wish to type the name of the file without entering the path 

The program will check to make sure that the file exists before attempting modify any of its contents
The program will then open or create a new file with the same name as the input file; however, the extension 
of the file will be modified 
	If the file is being encrypted, a .crp file will be created 
	If the file is being decrypted, a .txt file will be created 

The program will then proceed to read the contents of the file and modify it based on its task, if it is encrypting 
the program will create a new file with hexadecimal values. If the program is decrypting, it will break down a 
a hexadecimal file and create a new file which displays the files contents in words

When the program is done, it will let the user know that encryption/decryption was successful before ending the program 
The user can find their new file at the same location as the file that was originally modified 


The zip package has 2 sources attached to it, one that works directly with the cLion IDE and another HTML extension
which can be used to run the program through another IDE