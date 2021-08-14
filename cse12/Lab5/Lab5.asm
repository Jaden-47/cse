#####################################################################################################################################################
# Created by 	CSE 12 Lab 5 Template creator and Jaden Liu
# CruzID; 	zliu259
# Date:		5 June 2020
#
# Assignment: 	Lab5 Functions and Graphics
#		CSE12 Computer Systems and Assembly Language
#		UC Santa Cruz, Spring 2020
#
# Description:	This program save some subroutines that can be used to get, print some color value to the bitmap.
#		
# Notes:     	It is easier than Lab 4 with the given pseudocode, thanks guys for the mercy on the last Lab.
#####################################################################################################################################################

# Macro that stores the value in %reg on the stack 
#  and moves the stack pointer.
#-----------------------------------------------------
# push(a):
#	sp -= 4
#	stack[sp] = a
#-----------------------------------------------------
.macro push(%reg)
	subi $sp, $sp, 4
	sw %reg, 0($sp)
.end_macro 

# Macro takes the value on the top of the stack and 
#  loads it into %reg then moves the stack pointer.
#-----------------------------------------------------
# pop():
#	a = stack[sp]
#	sp += 4
#	return a
#-----------------------------------------------------
.macro pop(%reg)
	lw %reg, 0($sp)
	addi $sp, $sp, 4	
.end_macro

# Macro that takes as input coordinates in the format
# (0x00XX00YY) and returns 0x000000XX in %x and 
# returns 0x000000YY in %y
#-----------------------------------------------------
# getCoordinates(a):
#	x = a // 0x10000
#	y = a - x
#	return (x,y)
#-----------------------------------------------------
.macro getCoordinates(%input, %x, %y)
	div %x, %input, 0x00010000
	mul %x, %x, 0x00010000
	sub %y, %input, %x
	div %x, %input, 0x00010000
.end_macro

# Macro that takes Coordinates in (%x,%y) where
# %x = 0x000000XX and %y= 0x000000YY and
# returns %output = (0x00XX00YY)
#-----------------------------------------------------
# getCoordinates(x,y):
#	a = x * 0x10000
#	a += y
#	return (a)
#-----------------------------------------------------
.macro formatCoordinates(%output, %x, %y)
	push(%x)
	mul %x, %x, 0x00010000
	add %output, %x, %y
	pop(%x)
.end_macro 


.data
originAddress: .word 0xFFFF0000

.text
j done
    
    done: nop
    li $v0 10 
    syscall

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#  Subroutines defined below
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#*****************************************************
#-----------------------------------------------------
# clear_bitmap(a):
#	for i in range(0xFFFF0000, 0xFFFFFFFC)
#		stack[i] = a
#-----------------------------------------------------
#Clear_bitmap: Given a color, will fill the bitmap display with that color.
#   Inputs:
#    $a0 = Color in format (0x00RRGGBB) 
#   Outputs:
#    No register outputs
#    Side-Effects: 
#    Colors the Bitmap display all the same color
#*****************************************************
clear_bitmap: nop
	push($a0)			# push $a0 and $v0 to stack
    	push($v0)
    	
    	li $t9, 0xFFFF0000		#set the loop counter		
    	
    	loop_clear:
    		beq $t9, 0xFFFFFFFC, exit_clear	#clear the map
    		sw $a0, 0($t9)
    		addi $t9, $t9, 4
    		j loop_clear
    	exit_clear:
    		pop($v0)		# pop $a0 and $v0 off stack
    		pop($a0)
		jr $ra
	
#*****************************************************
# draw_pixel:
#  Given a coordinate in $a0, sets corresponding value
#  in memory to the color given by $a1	
#-----------------------------------------------------
# draw_pixel(a, b):
#	(x,y) = getCoordinates(a)
#	z = 4 * x + 128 * y + 0xFFFF0000
#	stack[z] = b
#-----------------------------------------------------
#   Inputs:
#    $a0 = coordinates of pixel in format (0x00XX00YY)
#    $a1 = color of pixel in format (0x00RRGGBB)
#   Outputs:
#    No register outputs
#*****************************************************
draw_pixel: nop
	push($a0)			# push $a0, $a1 and $v0 to stack
	push($a1)                        
    	push($v0)
    	push($t1)
    	push($t2)
    	push($t9)
    	
    	li $t9, 0xFFFF0000		#set the s7 the initial adress			
    	
    	getCoordinates($a0, $t1, $t2)	#get the coordinate and save them into $s1 and $s2
    	
    	mul $t1, $t1, 4			#get the x coordinate
    	add $t9, $t9, $t1
    	addi $t2, $t2, -1		
    	mul $t2, $t2, 0x00000200
    	add $t9, $t9, $t2		#get the y coordinate
    	
    	sw $a1, 0($t9)			#draw the pixel
	
    	pop($t9)
    	pop($t2)
    	pop($t1)
    	pop($v0)			# pop $a0, $a1 and $v0 off stack
    	pop($a1)                        
    	pop($a0)
	jr $ra
	
#*****************************************************
# get_pixel:
#  Given a coordinate, returns the color of that pixel	
#-----------------------------------------------------
# get_pixel(a):
#	(x,y) = getCoordinates(a)
#	z = 4 * x + 128 * y + 0xFFFF0000
#	z = loadword(z)
#	return z
#-----------------------------------------------------
#   Inputs:
#    $a0 = coordinates of pixel in format (0x00XX00YY)
#   Outputs:
#    Returns pixel color in $v0 in format (0x00RRGGBB)
#*****************************************************
get_pixel: nop
	push($a0)                        # push $a0 to stack
	push($t3)
	push($t4)
	push($t5)
	
	getCoordinates($a0, $t3, $t4)	#get the coordinate and save them into $t3 and $t4
	
	li $t5, 0xFFFF0000		#change the coordinate to the location of the stack
	mul $t3, $t3, 4
	add $t5, $t5, $t3
	addi $t4, $t4, -1
	mul $t4, $t4, 0x00000200
	add $t5, $t5, $t4
	
	lw $v0, 0($t5)			#load the RGB value
	
	pop($t5)
	pop($t4)
	pop($t3)
	pop($a0)			# pop $a0 off stack
	jr $ra

#***********************************************
# draw_solid_circle:
#  Considering a square arround the circle to be drawn  
#  iterate through the square points and if the point 
#  lies inside the circle (x - xc)^2 + (y - yc)^2 = r^2
#  then plot it.
#-----------------------------------------------------
# draw_solid_circle(int xc, int yc, int r) 
#    xmin = xc-r
#    xmax = xc+r
#    ymin = yc-r
#    ymax = yc+r
#    for (i = xmin; i <= xmax; i++) 
#        for (j = ymin; j <= ymax; j++)
#            a = (i - xc)*(i - xc) + (j - yc)*(j - yc)	 
#            if (a < r*r ) 
#                draw_pixel(x,y) 	
#-----------------------------------------------------
#   Inputs:
#    $a0 = coordinates of circle center in format (0x00XX00YY)
#    $a1 = radius of the circle
#    $a2 = color in format (0x00RRGGBB)
#   Outputs:
#    No register outputs
#***************************************************
draw_solid_circle: nop
	push($a0)			# push $a0 - $a2, $s1 - $s7, $ra to stack
	push($a1)                        
    	push($a2)
    	push($s1)
    	push($s2)
	push($s3)
	push($s4)
	push($s5)
	push($s6)
	push($s7)
	push($ra)
	
	
	getCoordinates($a0, $t5, $t6)	# get the coordinate and save them into $t5 and $t6
					# $t5 = xc 	$t6 =yc
	
	add $t7, $t5, $a1		# $t7 = xmax
	sub $t8, $t5, $a1		# $t8 = xmin 
	
	addi $t0, $t8, -1		# $t0 = loop counter i
	
	add $s1, $t6, $a1		# $s1 = ymax 
	sub $s2, $t6, $a1		# $s2 = ymin					
	
	mul $s6, $a1, $a1		# $s6 = r*r
	move $a1, $a2
	loop1_sc:
		beq $t0, $t7, exit_loop1_sc	
		addi $t0, $t0, 1		# i++
		
		addi $s7, $s2, -1		# reset $s7 = loop counter j
		
		loop2_sc:
			beq $s7, $s1,loop1_sc
			addi $s7, $s7, 1	# j++
			
			sub $s3, $t0, $t5	# (i - xc)*(i - xc)
			mul $s3, $s3, $s3
			
			sub $s4, $s7, $t6	# (j - yc)*(j - yc)	 
			mul $s4, $s4, $s4
			
			add $s5, $s3, $s4
			
			bge $s5, $s6, loop2_sc	# if (a < r*r ) 
			formatCoordinates($a0, $t0, $s7) 	
			jal draw_pixel
			j loop2_sc
	exit_loop1_sc:
	
	pop($ra)			# pop $a0 - $a2, $s1 - $s7, $ra off stack
	pop($s7)
	pop($s6)	
	pop($s5)
	pop($s4)	
	pop($s3)	
	pop($s2)
	pop($s1)
	pop($a2)			
    	pop($a1)                        
    	pop($a0)
	jr $ra
		
#***********************************************
# draw_circle:
#  Given the coordinates of the center of the circle
#  plot the circle using the Bresenham's circle 
#  drawing algorithm 	
#-----------------------------------------------------
# draw_circle(xc, yc, r) 
#    x = 0 
#    y = r 
#    d = 3 - 2 * r 
#    draw_circle_pixels(xc, yc, x, y) 
#    while (y >= x) 
#        x=x+1 
#        if (d > 0) 
#            y=y-1  
#            d = d + 4 * (x - y) + 10 
#        else
#            d = d + 4 * x + 6 
#        draw_circle_pixels(xc, yc, x, y) 	
#-----------------------------------------------------
#   Inputs:
#    $a0 = coordinates of the circle center in format (0x00XX00YY)
#    $a1 = radius of the circle
#    $a2 = color of line in format (0x00RRGGBB)
#   Outputs:
#    No register outputs
#***************************************************
draw_circle: nop
	push($a0)			# push $a0 - $a2, $s0 - $s6 and $ra to stack
	push($a1)                        
    	push($a2)
    	push($s0)
    	push($s1)
    	push($s2)
	push($s3)
	push($s4)
	push($s5)
	push($s6)
	push($ra)
	
	getCoordinates($a0, $s0, $s1)	# get the coordinate and save them into $t5 and $t6
					# $s0 = xc 	$s1 =yc
					
	li $s2, 0			# $s2 = x = 0
	
	add $s3, $0, $a1		# $s3 = y = r
	
	mul $s4, $a1, 2			# $s4 = d = 3 - 2 * r
	neg $s4, $s4
	addi $s4, $s4, 3
	
	move $a1, $a2
	move $a2, $s2			#prepare arguments $a0, $a1, $a2, $a3
	move $a3, $s3
	
	jal draw_circle_pixels	
	
	while_loop:
		blt $s3, $s2, exit_while # exit if y < x
		addi $s2, $s2, 1	# x = x + 1
		
		ble $s4, $0, else	# if d > 0
		addi $s3, $s3, -1	#  y = y-1
		
		sub $s5, $s2, $s3	# d = d + 4 * (x - y) + 10 
		mul $s5, $s5, 4
		addi $s5, $s5, 10
		add $s4, $s4, $s5
		j remain_part
		else:
			mul $s6, $s2, 4	# d = d + 4 * x + 6 
			addi $s6, $s6, 6
			add $s4, $s4, $s6
		remain_part:
			move $a2, $s2		#prepare arguments $a0, $a1, $a2, $a3
			move $a3, $s3
		jal draw_circle_pixels
		j while_loop
	exit_while:
		
	pop($ra)			# pop $a0 - $a2, $s0 - $s6 and $ra to stack
	pop($s6)	
	pop($s5)
	pop($s4)	
	pop($s3)	
	pop($s2)
	pop($s1)
	pop($s0)
	pop($a2)			
    	pop($a1)                        
    	pop($a0)
	jr $ra
	
#*****************************************************
# draw_circle_pixels:
#  Function to draw the circle pixels 
#  using the octans' symmetry
#-----------------------------------------------------
# draw_circle_pixels(xc, yc, x, y)  
#    draw_pixel(xc+x, yc+y) 
#    draw_pixel(xc-x, yc+y)
#    draw_pixel(xc+x, yc-y)
#    draw_pixel(xc-x, yc-y)
#    draw_pixel(xc+y, yc+x)
#    draw_pixel(xc-y, yc+x)
#    draw_pixel(xc+y, yc-x)
#    draw_pixel(xc-y, yc-x)
#-----------------------------------------------------
#   Inputs:
#    $a0 = coordinates of circle center in format (0x00XX00YY)
#    $a1 = color of pixel in format (0x00RRGGBB)
#    $a2 = current x value from the Bresenham's circle algorithm
#    $a3 = current y value from the Bresenham's circle algorithm
#   Outputs:
#    No register outputs	
#*****************************************************
draw_circle_pixels: nop
	push($a0)			# push $a0 - $a3, $t3 - $t6 and $ra to stack
	push($a1)                        
    	push($a2)
    	push($a3)
    	push($t3)
    	push($t4)
    	push($t5)
    	push($t6)
    	push($ra)
    	
    	getCoordinates($a0, $t3, $t4)	# get the coordinate and save them into $t3 and $t4
					# $t3 = xc 	$t4 =yc
					
	add $t5, $t3, $a2		# xc+x, yc+y
	add $t6, $t4, $a3
	formatCoordinates($a0, $t5, $t6)
	jal draw_pixel
	
	sub $t5, $t3, $a2		# xc-x, yc+y
	add $t6, $t4, $a3
	formatCoordinates($a0, $t5, $t6)
	jal draw_pixel
	
	add $t5, $t3, $a2		# xc+x, yc-y
	sub $t6, $t4, $a3
	formatCoordinates($a0, $t5, $t6)
	jal draw_pixel
	
	sub $t5, $t3, $a2		# xc-x, yc-y
	sub $t6, $t4, $a3
	formatCoordinates($a0, $t5, $t6)
	jal draw_pixel
	
	add $t5, $t3, $a3		# xc+y, yc+x
	add $t6, $t4, $a2
	formatCoordinates($a0, $t5, $t6)
	jal draw_pixel
	
	add $t5, $t3, $a3		# xc+y, yc-x
	sub $t6, $t4, $a2
	formatCoordinates($a0, $t5, $t6)
	jal draw_pixel
	
	sub $t5, $t3, $a3		# xc-y, yc+x
	add $t6, $t4, $a2
	formatCoordinates($a0, $t5, $t6)
	jal draw_pixel
	
	sub $t5, $t3, $a3		# xc-y, yc-x
	sub $t6, $t4, $a2
	formatCoordinates($a0, $t5, $t6)
	jal draw_pixel
	
	pop($ra)
	pop($t6)
	pop($t5)
	pop($t4)
	pop($t3)
	pop($a3)
	pop($a2)
	pop($a1)
	pop($a0)
	jr $ra
