# Botnet Attack Detection using Hashing Table and OOP in C++

## Description

This repository contains a C++ project that implements a hashing table and uses object oriented programming to detect a botnet attack on a web server. The project includes activities that cover different sorting and search methods, linked lists, and binary search trees. To access each of the different activities, please visit the different branches. Consider the main branch as the Activity 1.3

## Reflection

In activity 1.3, I learned about different sorting methods in order to complete the activity. It was a challenge at first to plan the general structure of how we would handle the sorting of dates, and that's when we decided to take advantage of object oriented programming and overload operators to implement the Merge Sort method. I also used pointers and came up with the idea of using a hashing table structure where we could access the data using the date as a key. This would make the search more efficient. Using Binary Search opened the possibility of thinking about BSTs, although I didn't know it at the time. When we implemented BSTs later on, I already had a general understanding of them, which facilitated my learning. Binary Search was the best option for this case due to its O(log n) complexity.

In activity 2.3, I contributed in a similar way to activity 1.3 by using a hashing table structure to store the data, now using the first digit of each IP as the key. In this case, the hashing table method would make the search much more efficient because access to a value is not random, it must be sequential. We used the Bubble Sort search method because it was easier to implement, although the ideal case would have been Merge Sort because it has a lower complexity (O(n log n) < O(n^2)).

I learned about linked lists and their importance in efficient memory usage compared to a vector or array, which require prior knowledge of the number of data to be stored in order to be efficient.

In activity 3.4, we implemented a BST to store the data. In this implementation, we no longer used a hashing table to store the data, making its implementation even simpler. This method allows for efficient search, storage, and sorting of the data due to its O(log n) complexity for insertion and search, and even when inserting the data, it is sorted at the same time, making it highly efficient. We worked in a similar way to linked lists, so the memory usage is also optimal. I implemented the BST by reusing the classes we already had and making minor adjustments, highlighting the importance of using OOP and designing reusable code from the beginning.

In activity 5.2, I contributed again by designing a structure for how to store the data, similar to a linked list, where each element in the list would contain a key and a value. This structure would allow us to efficiently store and access the data using the IP as a key. I also implemented the hash function using the modulo operator to distribute the data evenly across the table.

In activity 6.1, I implemented a function to detect a botnet attack on a web server using the data stored in the hash table. The function receives a threshold value and searches for IPs that have made more requests than the threshold. If any are found, they are considered part of a botnet attack and the function returns a list of the suspicious IPs.

