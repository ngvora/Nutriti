# Nutrition Diary CS 201 Portfolio Project - Nehal Vora

# What it is

Nutrition Diary Food Tracker is an application that allows you to create specific user diaries and search a food item to input from the FDA food database into your diary. It allows you to edit and update an existing user diary and gives you to option to add or delete food items from that file. It also keeps track of all the user diaries in the diary_list.txt file.

# Files to Download 

FDA Food Database File to be read by the program can be downloaded using this link. Please ensure that you have this file inside the folder of the program for it to work.
https://drive.google.com/file/d/1CU04kfc18ld8KZqVt0BeBIXa0aTGnjQ6/view?usp=sharing

# How to use
<b>Video Demo Link: </b></n>
In your terminal, change the directory to the folder the program is in and input the following command:</n>
<b> gcc -Wall string.c dynamic.c UNORDEREDSET.c UNORDEREDMAP.c main2.c ROW.c -g3 </b> </n>

The program will present you with the following options:</n>
<b> 1) Open a new diary (open <diaryname>) </b> </n>
 To execute this command, input "open" followed by the name of the diary you are trying to create.
 For example, to open a diary named Nehal I would enter the command "open Nehal".</n>
 
 You will now enter into a menu for the diary file:</n>
 <b>a)Insert (insert <name|vendor|keyword> <key>) </b></n>
 To add a new food into the diary, enter "insert" followed by "<name|vendor|keyword> <key>" where name stands for the exact food name, vendor stands for the manufacturer name and keyword is for a general item you want to search for using a key.</n>
 Once you have the search results displayed, select the item you want to be inserted into your food diary.</n>
 <b>b) Delete (delete)</b></n>
 To delete a food from the diary, enter "delete" followed by "<name|vendor|keyword> <key>" where name stands for the exact food name, vendor stands for the manufacturer name and keyword is for a general item you want to delete for using a key.
 This will delete the food item that matches your query.</n>
 <b>c)Print (print) </b></n>
 To print the user nutrition diary, enter "print".</n>
<b>d)Quit (quit)</b> </n>
 Enter "quit" to exit the menu.</n>
 
<b> 2) Update an existing diary (update <diaryname>) </b></n>
 Use this command to open and update a diary that has already been created. To execute this command, input "update" followed by the name    of the diary you want to update.
 For example, to update the diary Nehal input "update Nehal".
  
  You will now enter into a menu for the diary file:
 <b>a)Insert (insert <name|vendor|keyword> <key>)</b></n>
 To add a new food into the diary, enter "insert" followed by "<name|vendor|keyword> <key>" where name stands for the exact food name, vendor stands for the manufacturer name and keyword is for a general item you want to search for using a key.
 Once you have the search results displayed, select the item you want to be inserted into your food diary. </n>
 <b> b) Delete (delete) </b> </n>
 To delete a food from the diary, enter "delete" followed by "<name|vendor|keyword> <key>" where name stands for the exact food name, vendor stands for the manufacturer name and keyword is for a general item you want to delete for using a key.
 This will delete the food item that matches your query. </n>
 c) Print (print) </n>
 To print the user nutrition diary, enter "print".
 d) Quit (quit) </n>
 Enter "quit" to exit the menu.
  
<b> 3) Delete Diary (delete <diaryname>)</b> </n>
 Use this command to delete a diary that has already been created. To execute this command, input "delete" followed by the name of the diary you want to delete.
 For example, to delete the diary Nehal input "delete Nehal".
<b> 4) View all the diaries stored in the system (view list) </b> </n>
This command will show you all the diaries currently in the system and will help you keep track of them.
To execute this command, enter the following input "view list".
 </n>
# Additional Notes
This program uses hashtables and dynammic arrays to load the database in. It has an average search time of O(logn).
