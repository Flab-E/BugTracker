# BugTracker

## Overview

This is a basic Bug reporting and resolving software between the user and the admin/manager.
The program has 2 modes:
1.	User mode
2.	Admin mode



### User Mode:

In user mode a user can either login or sign up. 
all user credentials stored in `Users.csv`.
A User once logged in with his password can do the following:
1.	report a bug
2.	view all the bugs eported by the user ONLY
3.	Logout
4.	Exit

The report-bug section asks for the following:
|	Sl	|	Sl		|
|---------------|-----------------------|
|	1	|	bugid		|	
|	2	|	username	|	
|	3	|	description	|	
|	4	|	type		|	
|	5	|	status		|	
|	6	|	priority	|	
|	7	|	time		|	

in View section the user can see all the bugs reported by him.
A user cannot change the status of the bug.
A user cannot se other user's bug reports.



### Admin Mode:

the PASSWORD TO ADMIN IS: `admin123`
the admin can resolve the status of a bug.
The admin can view all bugs.
The admin can view bugs based on queries too.

## There is only one admin.
## there are multiple Users
