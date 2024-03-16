C99-Template-Containers
=======================

This was just a silly idea of mine when I was interested in trying to do generics in C99.

I didn't like how macros didn't expand in GDB, making them very difficult to debug.

This lead me to try experimenting with using python as a pre-processor as follows:
- A set of .template.h/.template.c files define generic datastructures with replaceable tokens in the name.
- A JSON config may then be created containing the desired resolution of the generic datastructures, ex.
  - A list of doubles.
  - A list of strings.
  - A hashmap using strings as the key, and a user-defined struct 'person' as the value.
- A python script then is used to:
  - Read this config.
  - Perform the replacement of the tokens in the corresponding templates.

    For the above examples this would result in the types:
      - list_of_double
      - list_of_string
      - dict_of_string_and_person
   
    (Some other types may be created, ex. the hash-table/dict uses a linked list internally).

  - Output the resolved templates in to .h/.c files.
- The .h/.c files output by the python script can then be compiled with the rest of your source as usual.

This approach works, and there are unit tests verifying the code.

I do prefer it to macros, but it still feels awkward (it has a funny smell to it).

I think the main take away is that C++ (and other higher level languages) contains a number of features out of the box that require some appreciation :)
