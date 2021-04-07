hello and welcome to battle ship the game this is a c++ language that has 
been used for this(i know not the language that would make sense to use but alas we were told to)

the assigment we were given was 
Use an object-oriented design approach for the creation, development and testing of AdaShip (a REPL.IT C++
computer console version/adaptation of the classic paper-based Battleships game).
You are expected to adopt an agile and iterated approach to decomposing, designing and developing your
game; ideally with a test early and fail fast approach.

so how did i approcach this 
i started of by breaking it down uml diagram see below:


how do i get a image into a read me because i cant seem to 
mike please email me for uml if needed beacuse repl wont let me get hte image into the read me?








due to a significant lack of knowladge in c++ i started of by just jumping into it as i had no idea what c++ could do or what was the best way to approach the situation i started of by trying to get a working structure board to use this took a while due to the fact i was taught javascript activaly in collage and work upuntil now so i had created the board but was then not able to use it in the structure i had created as there was missing key functions i was used to in javascript so had to create a new board design pretty quickly into the project but arfter this i had a bit of better knowladge so i moved the board of into a class to use it easier and removed it from the main file to save space for the main code i then looked into creating the ships and how to store thier information on the board i decided to use a rray of classes as this would allow me to be able to store multiple information within on array and make it a easy place to target for the c++.

to maintain a high quality i tired to seperate as much as i could in to object orientaded programing but again due to lack of knowladge i spent multiple days having to fix problems with this approach but manged to get the ones i had created so far to work but this now meant i was arfully low on time so you can see hwere the qulaity started to drop due to pressure constraints and i had to move to more nested logic as i could not sacrifice debugging time for this coursework as i had actual work from work that had to be prioratized.

in the end i broke down the key work into a few key epic 
the boats 
these needed to be able to be placed on the board manually or automatic 
and the life of the boat i needed to make sure was recorded 

the board its self:
the board i broke down into:
the array of information
the dynamic sizing which i had nearly inplementead but ran out of time for the alphabtical doubiling 
and the outputing of the board information in a user freindly way 

and finally the game logic was the last epic that i made sure worked to a playable extent for the user


see commented code for break down of functions and variables 