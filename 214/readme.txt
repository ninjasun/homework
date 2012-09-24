Project 1
Bilal Quadri & Yvgeniy Demo


Our program takes exactly two inputs as specified in the project description. We then run TKCreate with the input that creates and mallocs a struct with 3 pointers and returns the pointer to the struct. Two to the head of the stream input and one to the delimiters input. 

We then keep running the TKGetNextToken in a while loop until it hits the null terminator. TKGetNextToken first checks if the current token is a delmiter and if it is it moves to the next one. It also checks if it's null at which point it returns null. We then find the first occurence of a deliminator using strpbrk and create a pointer to it. If the endOfToken is null that means the whole string from the current token needs to be returned. Otherwise we strncpy from the stream to the endOfToken and then more the stream forward up to the pointer.

Finally we run TkDestory which frees up all the memory allocated in the struct.

As far as special characters are conserned our program works when they are input literally as special characters, as opposed to a literal backslash character followed by something.