<p># Nutrition Diary CS 201 Portfolio Project - Nehal Vora # What it is</p>
<p>Nutrition Diary Food Tracker is an application that allows you to create specific user diaries and search a food item to input from the FDA food database into your diary. It allows you to edit and update an existing user diary and gives you to option to add or delete food items from that file. It also keeps track of all the user diaries in the <em>diary_list.txt</em> file.</p>
<p># Files to Download</p>
<p>FDA Food Database File to be read by the program can be downloaded using this link. Please ensure that you have this file inside the folder of the program for it to work.</p>
<p>https://drive.google.com/file/d/1CU04kfc18ld8KZqVt0BeBIXa0aTGnjQ6/view?usp=sharing # How to use</p>
<p><strong>Video Demo Link: </strong></p>
<p>In your terminal, change the directory to the folder the program is in and input the following command:&nbsp;</p>
<p><strong>gcc -Wall string.c dynamic.c UNORDEREDSET.c UNORDEREDMAP.c main2.c ROW.c -g3 </strong></p>
<p>The program will present you with the following options:</p>
<p><strong> 1) Open a new diary (open )</strong></p>
<p><strong>&nbsp;</strong>To execute this command, input "open" followed by the name of the diary you are trying to create. For example, to open a diary named Nehal I would enter the command "open Nehal".&nbsp;</p>
<p>You will now enter into a menu for the diary file: </p>
<ul>
<li><strong>Insert (insert "name|vendor|keyword" "key")<br /></strong>To add a new food into the diary, enter "insert" followed by "&lt;name|vendor|keyword&gt; " where name stands for the exact food name, vendor stands for the manufacturer name and keyword is for a general item you want to search for using a key. Once you have the search results displayed, select the item you want to be inserted into your food diary.</li>
<li><strong>&nbsp;Delete (delete)</strong> <br />To delete a food from the diary, enter "delete" followed by "&lt;name|vendor|keyword&gt; " where name stands for the exact food name, vendor stands for the manufacturer name and keyword is for a general item you want to delete for using a key. This will delete the food item that matches your query.</li>
<li><strong>Print (print)&nbsp;<br /></strong>To print the user nutrition diary, enter "print".&nbsp;</li>
<li><strong>Quit (quit)</strong> <br />Enter "quit" to exit the menu.</li>
</ul>
<p><strong> 2) Update an existing diary (update "diaryname") </strong></p>
<p>Use this command to open and update a diary that has already been created. To execute this command, input "update" followed by the name of the diary you want to update. For example, to update the diary Nehal input "update Nehal". You will now enter into a menu for the diary file:&nbsp;</p>
<ul>
<li><strong>Insert (insert "name|vendor|keyword" "key")</strong></li>
<li>To add a new food into the diary, enter "insert" followed by "&lt;name|vendor|keyword&gt; " where name stands for the exact food name, vendor stands for the manufacturer name and keyword is for a general item you want to search for using a key. Once you have the search results displayed, select the item you want to be inserted into your food diary.&nbsp;</li>
<li><strong>Delete (delete) </strong> To delete a food from the diary, enter "delete" followed by "&lt;name|vendor|keyword&gt; " where name stands for the exact food name, vendor stands for the manufacturer name and keyword is for a general item you want to delete for using a key. This will delete the food item that matches your query.&nbsp;</li>
<li><strong>Print (print)</strong><br />&nbsp;To print the user nutrition diary, enter "print".&nbsp;</li>
<li><strong>Quit (quit)</strong><br />&nbsp;Enter "quit" to exit the menu.</li>
</ul>
<p><strong> 3) Delete Diary (delete "diaryname")</strong> Use this command to delete a diary that has already been created. To execute this command, input "delete" followed by the name of the diary you want to delete. For example, to delete the diary Nehal input "delete Nehal".</p>
<p><strong> 4) View all the diaries stored in the system (view list) </strong> This command will show you all the diaries currently in the system and will help you keep track of them. To execute this command, enter the following input "view list".</p>
<p># Additional Notes</p>
<p>This program uses hashtables and dynammic arrays to load the database in. It has an average search time of O(logn).</p>
