###################################################################################################
# Created by 	Jaden Liu
# CruzID; 	zliu259
# 		12 Nay 2020
#
# Assignment: 	Lab3 ASCII-risks (Asterisks)
#		CSe12 Computer Systems and Assembly Language
#		UC Santa Cruz, Spring 2020
#
# Description:	This program would print a trangular of asterisks and numbers.
#		
# Notes:     	This program cost me so many time.
###################################################################################################

###################################################################################################
# Pseudocode:
#a=0
#b=0
#c=1
#while b<1:
#    b=int(input())
#    if b<1:
#        print("iva")
#
#for i in range(b):
#    for j in range(2*b):
#        if j<i+1:
#            print(c,end='\t')
#            c+=1
#            a=c-1
#        elif j<=(2*b-1-(i+1)):
#            print("*",end='\t')
#        else:
#            if j!=2*b-1:
#                print(a,end='\t')
#                a-=1
#            else:
#                print(a)
###################################################################################################

.data
	prompt:  .asciiz"Enter the height of the pattern (must be greater than 0):\t"
	message: .asciiz "Invalid Entry!\n"
	tab: .asciiz "\t"
	newline: .asciiz "\n"
	star: .asciiz "*\t"
.text
	main:
		li $t0, 0
		li $t6, 1
		while:	
			bge $t0, 1, exit1
			
			#Prompt the user to enter the height
			li $v0 4
			la $a0 prompt
			syscall
	
			#Get user's input
			li $v0 5
			syscall
	
			#Store the result in t0
			move $t0, $v0
			#set t3=2*t2
			add $t3, $t0, $t0 
			
			#Check if it is valid
			blt $t0, 1, printm
			
		exit1:
			addi $t1, $0,0
			li $v0, 4
			la $a0 newline
			syscall
			for1:
				#for1 condition
				beq $t1, $t0, end
				addi $t1, $t1,1
				
				#set t2 to 0 every iteration ending
				li $t2,0
				
				j for2
			for2:
				#set t4,5 to satisfy the condition
				beq $t2, $t3, for1
				addi $t2, $t2, 1
				
				add $t4, $t0, $t0
				sub $t4, $t4, $t1
				
				add $t5, $t0, $t0
				subi $t5, $t5, 1
				
				ble $t2, $t1, printintegertab
				ble $t2, $t4, printstar
				ble $t2, $t5, printinteger1
				bgt $t2, $t5, printinteger2
				j for2
	printm:
		li $v0, 4
		la $a0, message
		syscall
		j while
	end: 
		li $v0, 10
		syscall	
	printinteger1:
		li $v0, 1
		move $a0, $t7
		syscall
		li $v0, 4
		la $a0 tab
		syscall
		subi $t7, $t7, 1
		j for2
		
	printintegertab:
		#print interger first
		li $v0, 1
		move $a0, $t6
		syscall
		#print a tab
		li $v0, 4
		la $a0 tab
		syscall
		#add 1 to t6
		addi $t6, $t6, 1
		subi $t7, $t6, 1
		j for2
		
	printstar:
		li $v0, 4
		la $a0 star
		syscall
		j for2
		
	printinteger2:
		li $v0, 1
		move $a0, $t7
		syscall
		li $v0, 4
		la $a0 newline
		syscall
		j for2
		
		
	
