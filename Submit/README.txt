/* * * * * * * * * * * * * * * * * * * * *\
 *                                       *
 * Compile Instruction & file organize   *
 *                                       *
 * File:    README.TXT                   *
 * Author:  Tasos Anastasas              *
 * A.M:     3166                         *
 * Course:  CS486                        *
 * Project: 2017                         *
 * Phase:   1                            *
\* * * * * * * * * * * * * * * * * * * * */

Perigrafei Ulopoihsh:
	-Uparxoun 6 fakeloi
		- 4 einai gia kathe diaforetikh ulopoihsh pou eixame na kanoume,
			-StackCGWithElim: coarse grained stack with elimination array
			-StackCG: coarse grained stack without elimination array
			-ListLazySync: list with lazy synchronization
			-ListFGSync: list with fine grained synchronization
		- 2 fakeloi genikoi skopou:
			- source: ola ta source pou einai genika kai gia tis 4 ulopoihshs
			- headers: ola ta .h ton source
			
H basikh idea einai oti sto source file exoume ulopoihsei tous client,updater,util
kai to stack kai list .c arxeia. Ta stack,list perilambanoun tis genikes sunartiseis
pou xreiazetai h ekastote ulopoihsh ton stack,list pou mas zitithike.
Se kathe ena apo tous 4 fakelous me tis diaforetikes ulopoihseis exoume ena .c kai 
ena .h se kapoies apo aftes. Sta .c ulopoioume tis sunartiseis apo to stack.h/list.h
oi opoios den uparxoun sta stack.h kai list.h. Diladi tis pushStack,popStack 
kai tis insertList,deleteList,lookupList,modifyList kai opoia extra voithitikh 
sunartisi xreiazetai kathe ulopoihsh

Tropos ekteleseis:
	-Exoume ena makefile to opoio me make paragei 4 ektelesima
		- make
			OUTPUT:
			-stackCG_listFG : coarse grained stack without elimination array & list with fine grained synchronization
			-stackCG_listLazy: coarse grained stack without elimination array & list with lazy synchronization
			-stackEl_listFG: coarse grained stack with elimination array & list with fine grained synchronization
			-stackEl_listLazy: coarse grained stack with elimination array & list with lazy synchronization
		
	-Mporoume na paragoume opoiadipote apo tis 4 ekteleseis theloume me ton eksis tropo:
		- make stackCG_listFG    
		- make stackCG_listLazy  
		- make stackEl_listFG    
		- make stackEl_listLazy
		
	-Mporoume na kanoume clean oti exoume ftiaksei me
		- make clean
		
		
	-To makefile sundiazei ola ta .c pou exoume sto source kai meta analoga poia ektelesh theloume na ftiaksoume kathe fora
	 epilegei ta antistoixa arxeia tis ekastote ulopoihshs.
		
		
		
		
		
		
