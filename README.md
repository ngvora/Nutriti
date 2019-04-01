<h1>Nutrition Diary CS 201 Portfolio Project - Nehal Vora</h1>

<h2>What it is</h2>
Nutrition Diary Food Tracker is an application that allows you to create specific user diaries and search a food item to input from the FDA food database into your diary. It allows you to edit and update an existing user diary and gives you to option to add or delete food items from that file. It also keeps track of all the user diaries in the diary_list.txt file.

<h2>Files to download</h2>
FDA Food Database File to be read by the program can be downloaded using this link. Please ensure that you have this file inside the folder of the program for it to work.

https://drive.google.com/file/d/1CU04kfc18ld8KZqVt0BeBIXa0aTGnjQ6/view?usp=sharing

How to use
Video Demo Link:https://youtu.be/ERB5318RNdw

In your terminal, change the directory to the folder the program is in and input the following command: 

<h3>make</h3>

The program will present you with the following options:

1) Open a new diary (open "diary")

 To execute this command, input "open" followed by the name of the diary you are trying to create. For example, to open a diary named Nehal I would enter the command "open Nehal". 

You will now enter into a menu for the diary file:

a) Search Items (query "keyword|id" "key")

b) Insert (insert "keyword|id" "key")

To add a new food into the diary, enter "insert" followed by "keyword|id" where keyword is for general items you want to insert using that keyword and id is for the specific element with that ID. Using the keyword will insert every element that has the keyword inside the diary and using the ID will only insert that specific ID inside the diary.

c) Delete (delete "keyword|id" "key") 

To delete a food from the diary, enter "delete" followed by "keyword|id" where keyword is for general items you want to delete that has those keywords in it and ID is for the specific element with that ID. This will delete the food item that matches your input.
d) Print Current Diary (print) 
To print the user nutrition diary, enter "print". 
e) Quit (quit) 
Enter "quit" to exit the menu.

2) Delete Diary (delete "diaryname") Use this command to delete a diary that has already been created. To execute this command, input "delete" followed by the name of the diary you want to delete. For example, to delete the diary Nehal input "delete Nehal".

3) View all the diaries stored in the system (list) This command will show you all the diaries currently in the system and will help you keep track of them. To execute this command, enter the following input "list".

4)Quit ("quit") This command will quit the program completely. To execute this command, enter "quit".

Additional Notes
This program uses hashtables and dynammic arrays to load the database in. It has an average search time of O(logn).
