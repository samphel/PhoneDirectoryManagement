# DataStructureProject
DTU IT-B sem 3 Data Structure Project - Phone Directory Management using Tries made by Utsav Singh 2k20/IT/156 and Samphel Bodh 2k20/IT/127 

Features

2.1 Add a contact
We have to enter a new unique name and contact number which will be saved into our directory.

2.2 Search for a contact
We have to enter a name or the first few characters of a name and according to what we enter the program will give suggestions.

2.3 Show all contacts
Prints all the contacts in our directory to the screen.

2.4 Delete a contact
We enter the contact we want to delete from our directory and it is removed.


Working/Methodology

Firstly we will be using file handling to save and manage all the contact info to disk. Then every time the program starts we will insert all the names into the Trie.
Also, every time a contact is added it will first be saved to file using file handling and then inserted into the Trie.
Similarly, when a contact is deleted it is removed from the file and also from the Trie.
In the search operation, we use our Trie to search for the prefix/name that is entered by the user. Using the Trie we are able to print the list of all names in our contact list which starts with the prefix entered by the user. This is the main advantage provided by using Trie Data Structure.
