<h1>Nutrition Diary CS 201 Portfolio Project - Nehal Vora</h1>
<h2><a id="user-content-what-it-is" class="anchor" href="https://github.com/ngvora/Nutrition-CRUD-Database-Log-CS-201-#what-it-is" aria-hidden="true"></a>What it is</h2>
<p>Nutrition Diary Food Tracker is an application that allows you to create specific user diaries and search a food item to input from the FDA food database into your diary. It allows you to edit and update an existing user diary and gives you to option to add or delete food items from that file. It also keeps track of all the user diaries in the diary_list.txt file.</p>
<h2><a id="user-content-files-to-download" class="anchor" href="https://github.com/ngvora/Nutrition-CRUD-Database-Log-CS-201-#files-to-download" aria-hidden="true"></a>Files to download</h2>
<p>FDA Food Database File to be read by the program can be downloaded using this link. Please ensure that you have this file inside the folder of the program for it to work.</p>
<p><a href="https://drive.google.com/file/d/1CU04kfc18ld8KZqVt0BeBIXa0aTGnjQ6/view?usp=sharing" rel="nofollow">https://drive.google.com/file/d/1CU04kfc18ld8KZqVt0BeBIXa0aTGnjQ6/view?usp=sharing</a></p>
<h2><strong>How to use</strong></h2>
<p>Video Demo Link:<a href="https://youtu.be/ERB5318RNdw" rel="nofollow">https://youtu.be/ERB5318RNdw</a></p>
<p>In your terminal, change the directory to the folder the program is in and input the following command:</p>
<h3><a id="user-content-make" class="anchor" href="https://github.com/ngvora/Nutrition-CRUD-Database-Log-CS-201-#make" aria-hidden="true"></a>make</h3>
<p>The program will present you with the following options:</p>
<ol>
<li><strong>Open a new diary (open "diary")</strong></li>
</ol>
<p>To execute this command, input "open" followed by the name of the diary you are trying to create. For example, to open a diary named Nehal I would enter the command "open Nehal".</p>
<p>You will now enter into a menu for the diary file:</p>
<p>a) Search Items (query "keyword|id" "key")</p>
<p>To search a new food item, enter "query" followed by "keyword|id" where keyword is for general items you want to search using that keyword and id is for the specific element with that ID you want to see. Using the keyword will search every element that has the keyword in the database and display it and using the ID will only display the food item inside the database.</p>
<p>b) Insert (insert "keyword|id" "key")</p>
<p>To add a new food into the diary, enter "insert" followed by "keyword|id" where keyword is for general items you want to insert using that keyword and id is for the specific element with that ID. Using the keyword will insert every element that has the keyword inside the diary and using the ID will only insert that specific ID inside the diary.</p>
<p>c) Delete (delete "keyword|id" "key")</p>
<p>To delete a food from the diary, enter "delete" followed by "keyword|id" where keyword is for general items you want to delete that has those keywords in it and ID is for the specific element with that ID. This will delete the food item that matches your input. 
 <p> d) Print Current Diary (print)</p><p> To print the user nutrition diary, enter "print". </p>
 <p> e) Quit (quit)</p> <p>Enter "quit" to exit the menu.</p>
<ol start="2">
<li>
<p>Delete Diary (delete "diaryname") <br />Use this command to delete a diary that has already been created. To execute this command, input "delete" followed by the name of the diary you want to delete. For example, to delete the diary Nehal input "delete Nehal".</p>
</li>
<li>
<p>View all the diaries stored in the system (list) <br />This command will show you all the diaries currently in the system and will help you keep track of them. To execute this command, enter the following input "list".</p>
</li>
</ol>
<p>&nbsp; &nbsp;4.Quit ("quit") <br />&nbsp; &nbsp; &nbsp; This command will quit the program completely. To execute this command,&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; enter "quit".</p>
<h2>Additional Notes</h2>
<p>This program uses hashtables and dynamic arrays to load the database in. It has an average search time of O(logn).</p>
