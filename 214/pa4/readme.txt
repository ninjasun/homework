Our design for this assignment was to store the words in a linked list and each
node has it's own linked list. We choose this data structure because it makes
inserting and removing nodes easier. Once the main data structure is built our
SA and SO duplicate the nodes it needs first and store it in a temp data
structure. This way we don't risk inserting or removing something from the main
data structure.

For this assignment we used the Indexer that was provided. Our indexer had a few
bugs that we hope to fix soon.

Valgrind does report invalid reads at times, with some blocks not being freed.
