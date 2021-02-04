Name  : Alfredo Mejia
NetID : axm180023
Course: SE 3345.004
Assign: Project 3
IDE   : IntelliJ IDEA Community Edition

Terminal/Compiler:
Git Bash

Files: 	README.txt
	MainBinarySearchDriver.java
	LazyBinarySearchTree.java


	
*Used Git bash to compile and pass the files as arguments to the main
class*
**********
Sample 1:

Insert:98
Insert:67
Insert:55
Insert:45
PrintTree
Delete:84
Delete:45
Contains:45
FindMin
FindMax
PrintTree
Height
Size
Insert:84
Insert:32
Insert:132
PrintTree
Insert:980
Insert
hih
Insert:99
Insert:-1
fjfj
Delete:5
Printtree
*************
Output 1:

True
True
True
True
98 67 55 45 
False
True
False
55
98
98 67 55 *45 
3
4
True
True
Error in insert: IllegalArgumentException raised
98 67 55 *45 32 84 
Error in insert: IllegalArgumentException raised
Error in Line: insert
Error in Line: hih
True
Error in insert: IllegalArgumentException raised
Error in Line: fjfj
False
98 67 55 *45 32 84 99
 
*****************
Sample 2:

Insert:50
Insert:40
Insert:30
Insert:20
Insert:10
Insert:1
Insert:60
Insert:70
Insert:80
Insert:90
Insert:99
Insert:0
Insert:100
PrintTree
Delete:1
PrintTree
Delete:60
PrintTree
Insert:60
PrintTree
Delete:55
Insert:68
Delete:99
Delete:1
PrintTree
Delete:10
Delete:90
FindMin
FindMax
Height
Size
PrintTree
Delete:50
PrintTree

***********
Output 2:

True
True
True
True
True
True
True
True
True
True
True
Error in insert: IllegalArgumentException raised
Error in insert: IllegalArgumentException raised
50 40 30 20 10 1 60 70 80 90 99 
True
50 40 30 20 10 *1 60 70 80 90 99 
True
50 40 30 20 10 *1 *60 70 80 90 99 
False
50 40 30 20 10 *1 60 70 80 90 99 
False
True
True
False
50 40 30 20 10 *1 60 70 68 80 90 *99 
True
True
20
80
5
12
50 40 30 20 *10 *1 60 70 68 80 *90 *99 
True
*50 40 30 20 *10 *1 60 70 68 80 *90 *99 

************
Sample 3:

fkjd
sdfjsj
sadfsdkj
dsjfdksl
dskfsdkj
Insert:4
Printtree

***********
Output 3:

Error in Line: fkjd
Error in Line: sdfjsj
Error in Line: sadfsdkj
Error in Line: dsjfdksl
Error in Line: dskfsdkj
True
4 
