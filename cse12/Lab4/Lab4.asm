###################################################################################################
# Created by 	Jaden Liu
# CruzID; 	zliu259
# 		22 Nay 2020
#
# Assignment: 	Lab4 Sorting Integers
#		CSe12 Computer Systems and Assembly Language
#		UC Santa Cruz, Spring 2020
#
# Description:	This program does a hex to decimal converterion and sorted them by at most 8 numbers in range 0x000-0xFFF.
#		
# Notes:     	This program is 100% seld-did. Please don't send me email of "meeting" with professor.
###################################################################################################

###################################################################################################
# Pseudocode:
#get the argument
#
#save the argument to an array
#
#print the argument
#
#get the length of each argument and save it to another array 
#
#get the amount of all argument and save the number
#
#change the hex value in the array to decimal and save them to another array(iterated the amount of the array)
#    
#print the decimal value
#
#sorted the value in the decimal array save them in the original array
#      
#print the sorted decimal value
#def bubble_sort(list1):
#   n = len(list1)
#    for j in range(n - 1):
#       count = 0
#	for i in range(0, n - 1 - j):
#            if list1[i] > list1[i + 1]:
#                list1[i], list1[i + 1] = list1[i + 1], list1[i]#
#                count += 1
#        if 0 == count:
#            break
###################################################################################################

.data
	hexArray: .space 48
	digitArray: .space 48
	numberArray: .space 48
	amount: .space 4
	printArray: .space 16
	prompt1: .asciiz "Program arguments:\n"
	prompt2: .asciiz "Integer values:\n"
	prompt3: .asciiz "Sorted values:\n"
	empty: .asciiz " "
	newLine: .asciiz "\n"
.text
	#print prompt1
	li $v0, 4
	la $a0, prompt1
	syscall

	saveArgument:
		#get the arguments and save it into array
		lw $a0, ($a1)
		
		blt $a0,32,printArgument
		
		#t0 is a index for the array, a1 represent the address for the argument
		sw $a1, hexArray($t0)
		addi $t2, $t2,1
		lw $t7, hexArray($t0)
		
		#the index for the array and address of argument both +4
		addi $t0, $t0, 4
		addi $a1, $a1, 4
				
		j saveArgument
	printArgument:
		#do some preparation for the real print function
		sw $t2,amount($t5)
		addi $t2, $t2,-1
		j printArgument1
	printArgument1:	
		lw $t7, hexArray($t5)
		div $t6, $t5, 4
		addi $t5, $t5, 4
		beq $t6, $t2, printArgument2
		#print the arguments, when it reach the represent the number of arguments, exit
		li $v0, 4
		lw $a0, ($t7)
		syscall
		
		#print an empty char
		li $v0, 4
		la $a0, empty
		syscall
		j printArgument1
	printArgument2:
		#if it is the last one, then no need for an blank.
		li $v0, 4
		lw $a0, ($t7)
		syscall
		j printPrompt2
	printPrompt2:
		
		li $t2, 0
		#print a newline and swich to next line
		li $v0, 4
		la $a0, newLine
		syscall
		syscall
		
		#print prompt2
		li $v0, 4
		la $a0, prompt2
		syscall
	getDigit:
		#save the digit to an array
		li $t0, -4
		getHex1:
			li $t5, 0		
			addi $t0, $t0, 4
			lw $t6, hexArray($t0)
			#jump out when meet the boundary
			blez $t6,clear
			lw $t3, ($t6)
			addi $t3, $t3, 1
			hexCtoD1:

				addi $t3, $t3, 1
				
				lbu $t4,($t3) #load the byte into $t4
				blez $t4, saveword
				addi $t8, $t8, 1
				li $s0, 0x39
				bgt $t4, $s0, hexForChar1 #convert to decimal for character
				ble $t4, $s0, hexForInt1 #convert to decimal for integer
		
			hexForChar1:
				addiu $t4, $t4, -0x37
				j hexCtoD1
			hexForInt1:
				addiu $t4, $t4, -0x30
				j hexCtoD1
	saveword:
		#save all the words into an array
		sw $t8, digitArray($t9)
		lw $t7, digitArray($t9)
		addi $t9, $t9, 4
		li $t8,0
		j getHex1
	
	clear:
		#clear all regiter for later purpose
		li $t0, 0
		li $t1, 0
		li $t2, 0
		li $t3, 0
		li $t4, 0
		li $t5, 0
		li $t6, 0
		li $t7, 0
		li $t8, 0
		li $t9, 0
		li $s1, 0
		li $s2, 0
		li $s3, 0
		li $s4, -4
		li $s5, 0
		li $s6, 0
		li $s7, 0
		j printInteger1	
	printInteger1:
		li $t0, -4
		getHex:
			beq $t5,0,left
			addi $s4, $s4, 4
			sw $t5, numberArray($s4)
			#next three function is for printing using syscall 11
			getDigit4:
				div $t5, $t5, 10
				mfhi $s1
				mflo $t5
				sw $s1, printArray($s2)
				addi $s2, $s2, 4
				beq $t5, 0, printINT3
				j getDigit4
			printINT3:
				beq $s2, 0, exit3
				addi $s2, $s2, -4
				lw $s1, printArray($s2)
				addi $s1, $s1, 0x30
				li $v0, 11
				move $a0, $s1
				syscall
				j printINT3
			exit3:
				#print an empty char
				lw $s7, amount($0)
				addi $s7, $s7, -1
				beq $s7, $s6, left
				addi $s6, $s6, 1
				li $v0, 4
				la $a0, empty
				syscall
			left:
				li $t5, 0
				li $s1, 0		
				addi $t0, $t0, 4
				lw $t6, hexArray($t0)
				blez $t6,printPrompt3
				lw $t3, ($t6)
				addi $t3, $t3, 1
				lw $t7, digitArray($t1)
			hexCtoD:
				
				addi $t3, $t3, 1
			
				lbu $t4,($t3)
				blez $t4, getHex
				li $t9, 0x39
				bgt $t4, $t9, hexForChar
				ble $t4, $t9, hexForInt
				less:
					#tell which digit it is in
					beq $t7, 3, decimal3
					beq $t7, 2, decimal2
					beq $t7, 1, decimal1
					func:
						mul $s0, $t4, $t6
						add $s1, $s1, $s0
						addi $t7, $t7, -1
						beq $t7, 0, func2
				j hexCtoD

			hexForChar:
				addiu $t4, $t4, -0x37
				j less
			hexForInt:
				addiu $t4, $t4, -0x30
				j less
			
	decimal3:
		li $t6, 256
		j func
	decimal2:
		li $t6,16
		j func
	decimal1:
		li $t6,1
		j func
	func2:
		beq $s1,0, print0
		func3:
			add $t5, $t5, $s1
			addi $t1, $t1, 4
			j getHex
	print0:
		#design this function because of some fault of the program structure, it is specifically for 0x00
		addi $s4, $s4, 4
		sw $s1, numberArray($s4)
		sw $s1, numberArray($s4)
		li $v0,1
		move $a0, $s5
		syscall
		lw $s7, amount($0)
		addi $s7, $s7, -1
		beq $s7, $s6, func3
		addi $s6, $s6, 1
		li $v0, 4
		la $a0, empty
		syscall
		j func3

	li $t3, 0
	#next three function is for printing using syscall 11
	getDigit1:
		div $s5, $s5, 10
		mfhi $t1
		mflo $s5
		sw $t1, printArray($t3)
		addi $t3, $t3, 4
		beq $s5, 0, printINT5
		j getDigit1
	printINT5:
		beq $t3, 0, exit1
		addi $t3, $t3, -4
		lw $t1, printArray($t3)
		addi $t1, $t1, 0x30
		li $v0, 11
		move $a0, $t1
		syscall
		j printINT5
	exit1:
		lw $s7, amount($0)
		addi $s7, $s7, -1
		beq $s7, $s6, func3
		addi $s6, $s6, 1
		li $v0, 4
		la $a0, empty
		syscall
		j func3
		
		
	printPrompt3:
		#print a newline and swich to next line
		li $v0, 4
		la $a0, newLine
		syscall
		syscall
		
		#print prompt3
		li $v0, 4
		la $a0, prompt3
		syscall
	clear2:
		#clear all regiter for later purpose
		li $t0,0
		li $t1,0
		li $t2,0
		li $t3,0
		li $t4,0
		li $t5,0
		li $t6,0
		li $t7,0
		li $t8,0
		li $t9,0
		li $s1,0
		li $s2,0
		li $s3,0
		li $s4,0
		li $s5,0
		li $s6,0
		li $s7,0
		lw $s1, amount($0)
		addi $s1, $s1, -1	
		j bubbleSort
	bubbleSort:
		#bubble sort
		beq $t6, $s1, prep
		addi $t6, $t6, 1
		loop:
			lw $t1, numberArray($t0)
			addi $t0, $t0, 4
			lw $t2, numberArray($t0)
			addi $t7, $t7, 1
			bgt $t1, $t2, exchange
			back:
				beq $t7, $s1, cleart7
				
				j loop
		
	exchange:
		#exchange the near value
		li $s0, 0
		add $s0, $s0, $t1
		move $t1, $t2
		move $t2, $s0
		sw $t2, numberArray($t0)
		addi $t0, $t0, -4
		sw $t1, numberArray($t0)
		addi $t0, $t0, 	4	
		j back
	cleart7:
		li $t7, 0
		li $t0, 0
		j bubbleSort
	prep:
		#do some preparation for print integer
		mul $s1, $s1, 4
		li $t0, 0
		j printInt
	printInt:
		#print the integer
		lw $t3, numberArray($t0)
		addi $t0, $t0, 4

	#next three function is for printing using syscall 11
	gD:
		div $t3, $t3, 10
		mfhi $s6
		mflo $t3
		sw $s6, printArray($s5)
		addi $s5, $s5, 4
		beq $t3, 0, printINT1
		j gD
	printINT1:
		beq $s5, 0, exit2
		addi $s5, $s5, -4
		lw $s6, printArray($s5)
		addi $s6, $s6, 0x30
		li $v0, 11
		move $a0, $s6
		syscall
		j printINT1
	exit2:
		lw $t4, amount($0)
		addi $t4, $t4, -1
		beq $t4, $s2, little
		addi $s2, $s2, 1
		li $v0, 4
		la $a0, empty
		syscall
		little:
			bgt $t0, $s1, exit
			j printInt
	exit:
		li $v0, 4
		la $a0, newLine
		syscall
		li $v0, 10
		syscall
