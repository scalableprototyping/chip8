0x0200	jmp 0x0225                          // --------------
                                                            |
// SPACE INVADERS 0.91 By David WINTER                      |
    0x0202	DATA = 0x53	GRAPHIC =  # #  ##	ASCII(S)        |
    0x0203	DATA = 0x50	GRAPHIC =  # #    	ASCII(P)        |
    0x0204	DATA = 0x41	GRAPHIC =  #     #	ASCII(A)        |
    0x0205	DATA = 0x43	GRAPHIC =  #    ##	ASCII(C)        |
    0x0206	DATA = 0x45	GRAPHIC =  #   # #	ASCII(E)        |
    0x0207	DATA = 0x20	GRAPHIC =   #                       |
    0x0208	DATA = 0x49	GRAPHIC =  #  #  #	ASCII(I)        |
    0x0209	DATA = 0x4e	GRAPHIC =  #  ### 	ASCII(N)        |
    0x020a	DATA = 0x56	GRAPHIC =  # # ## 	ASCII(V)        |
    0x020b	DATA = 0x41	GRAPHIC =  #     #	ASCII(A)        |
    0x020c	DATA = 0x44	GRAPHIC =  #   #  	ASCII(D)        |
    0x020d	DATA = 0x45	GRAPHIC =  #   # #	ASCII(E)        |
    0x020e	DATA = 0x52	GRAPHIC =  # #  # 	ASCII(R)        |
    0x020f	DATA = 0x53	GRAPHIC =  # #  ##	ASCII(S)        |
    0x0210	DATA = 0x20	GRAPHIC =   #                       |
    0x0211	DATA = 0x30	GRAPHIC =   ##    	ASCII(0)        |
    0x0212	DATA = 0x2e	GRAPHIC =   # ### 	ASCII(.)        |
    0x0213	DATA = 0x39	GRAPHIC =   ###  #	ASCII(9)        |
    0x0214	DATA = 0x31	GRAPHIC =   ##   #	ASCII(1)        |
    0x0215	DATA = 0x20	GRAPHIC =   #                       |
    0x0216	DATA = 0x42	GRAPHIC =  #    # 	ASCII(B)        |
    0x0217	DATA = 0x79	GRAPHIC =  ####  #	ASCII(y)        |
    0x0218	DATA = 0x20	GRAPHIC =   #                       |
    0x0219	DATA = 0x44	GRAPHIC =  #   #  	ASCII(D)        |
    0x021a	DATA = 0x61	GRAPHIC =  ##    #	ASCII(a)        |
    0x021b	DATA = 0x76	GRAPHIC =  ### ## 	ASCII(v)        |
    0x021c	DATA = 0x69	GRAPHIC =  ## #  #	ASCII(i)        |
    0x021d	DATA = 0x64	GRAPHIC =  ##  #  	ASCII(d)        |
    0x021e	DATA = 0x20	GRAPHIC =   #                       |
    0x021f	DATA = 0x57	GRAPHIC =  # # ###	ASCII(W)        |
    0x0220	DATA = 0x49	GRAPHIC =  #  #  #	ASCII(I)        |
    0x0221	DATA = 0x4e	GRAPHIC =  #  ### 	ASCII(N)        |
    0x0222	DATA = 0x54	GRAPHIC =  # # #  	ASCII(T)        |
    0x0223	DATA = 0x45	GRAPHIC =  #   # #	ASCII(E)        |
    0x0224	DATA = 0x52	GRAPHIC =  # #  # 	ASCII(R)        |
                                                            |
// Game Start               <--------------------------------

// for loop initialization 
0x0225	mov v0, 0x00    // initial x possition in the screen 
0x0227	mov v1, 0x00    // initial y position in the screen
0x0229	mov v2, 0x08    // sprite height (8 lines)
0x022b	mov I, 0x03dd   // start sprite

// Print Satic Title Screen:
//   -| Space |-
//     Invaders
//    ----------
// --|         |--
//   ----------

// for (v0 = 0; v1 < 0x40 == 64; v1 += 8) {
    // for (v1 = 0; v1 < 0x20 == 32; v1 += 8) {
        0x022d	draw_spirte xreg=v0, yreg=v1, h=8

        // Update v1 for loop
        0x022f	add v1, 0x08    // Advance to next y possition in the screen
        0x0231	add I, v2       // Load next sprite
        0x0233	skipnext_eq v1, 0x20
        0x0235	jmp 0x022d
    // }
// Update v0 for loop
0x0237	add v0, 0x08 
0x0239	mov v1, 0x00
0x023b	skipnext_eq v0, 0x40
0x023d	jmp 0x022d
// }

0x023f	mov v9, 0x05    // Start game key
0x0241	mov vc, 0x15    // scrolling title y possition

0x0243	mov ve, 0x00    // update title index. With increasing index, new letters will roll in

// while true. It can exit this loop if the start key is pressed during the update_title_screen subrutine {
0x0245	
    call 0x0391_update_title_screen(update_index = ve, scrolling_title_y_pos = vc)  // Update title screen  

    // Wait for 10/60 seconds {
    0x0247	mov v0, 0x0a  = 10 
    0x0249	mov delay_timer, v0
    0x024b	mov v0, delay_timer
    0x024d	skipnext_eq v0, 0x00
    0x024f	jmp 0x024b
    // }
    
    0x0251	call 0x0391_update_title_screen(update_index = ve, scrolling_title_y_pos = vc)  // Update title screen 

    0x0253	add ve, 0x01  // Increment title index. Roll in next letter

0x0255	jmp 0x0245
// }

// ---> Start key pressed during 0x0391_update_title_screen subrutine. 
// Game starts

0x0257_start_game	

// Set initial variables

        mov v6, 0x00    // No bullet in the air flag
0x0259	mov v8, 0x1c    // Player initial position

0x025b	mov v9, 0x00    // Enemies initial level
0x025d	mov va, 0x04 
0x025f	mov vb, 0x0a    // Initial x enemies possition
0x0261	mov vc, 0x04    // Initial y enemies possition

0x0263	mov vd, 0x3c  == 60 // Enemies update frequency (60/60Hz = 1 sec). They become faster when difficulty increases
0x0265	mov ve, 0x0f        // Number of enemies alive 0b1111 in binary

0x0267	clear_screen

0x0269	call 0x0375_move_player_x(pos_x = v8) // Draw player
0x026b	call 0x0353_update_all_enemies(enemies_alive = ve, enemy_type = v9, enemy_x = vb, enemy_y = vc) // Draw enemies

0x026d	mov delay_timer, vd // vd = 60 -> count for 1 second

// Main update loop 

// if left key pressed {
0x026f_game_update_loop	mov v0, 0x04    // left key                          	   
0x0271	skipnext_on_keypress v0         
0x0273	jmp 0x027d                      // goto check if right key pressed

    0x0275	call 0x0375_move_player_x(pos_x = v8)   // Erase player sprite   
    0x0277	skipnext_eq v8, 0x00            // Don't move more to the left if we are at the left margin
    0x0279	add v8, 0xff                    // subtract one
    0x027b	call 0x0375_move_player_x(pos_x = v8)   // Draw new position     

// }

// if right key pressed {
0x027d	mov v0, 0x06                    // right key
0x027f	skipnext_on_keypress v0         
0x0281	jmp 0x028b                      // goto check if shoot key pressed

    0x0283	call 0x0375_move_player_x(pos_x = v8)   // Erase player sprite         
    0x0285	skipnext_eq v8, 0x39 == 57      // 57 + 4 = 61, reached right margin
    0x0287	add v8, 0x01                    // advance one
    0x0289	call 0x0375_move_player_x(pos_x = v8)   // Draw new position         
// }

// if no bullet in the air {
0x028b	skipnext_eq v6, 0x00 // Bullet on the air flag, we can only shoot one bullet at a time
0x028d	jmp 0x029f // Skip bullet key pressed check if there is a bullet already in the air

    // if shoot key pressed {
    // Check if shoot key pressed
    0x028f	mov v0, 0x05            // shoot key                         	
    0x0291	skipnext_on_keypress v0 
    0x0293	jmp 0x02e9_shoot_key_not_pressed

        // Create new  bullet
        0x0295	mov v6, 0x01       // Set bullet in the air flag to true
        // v5 stores the bullet y possition
        0x0297	mov v5, 0x1b == 27 // 27 + 4 = 31   // The bullet starts at the player height
        // v4 stores the bullet x possition
        0x0299	mov v4, v8                          // store in v4 the players position (v8)
        0x029b	mov I, 0x03d9_player_graphics       // Load bullet graphics
        0x029d	draw_spirte xreg=v4, yreg=v5, h=1   // The bullet  graphics is just the first line of the player sprite
    // }

// }

// Bullet in the air
0x029f	mov I, 0x03d9_player_graphics       // Erase bullet
0x02a1	draw_spirte xreg=v4, yreg=v5, h=1

0x02a3	add v5, 0xff == 255                 // Subtract one to bullet_y == move bullet up

// if bullet reached the top
0x02a5	skipnext_eq v5, 0xff
0x02a7	jmp 0x02ad
// {

    0x02a9	mov v6, 0x00                        // Unset bullet in the air flag
    0x02ab	jmp 0x02e9_shoot_key_not_pressed    // Goto no bullet update

// } else {
    0x02ad	draw_spirte xreg=v4, yreg=v5, h=1   // Draw bullet at new possition 

    // if bullet hit enemy 
    0x02af	skipnext_eq vf, 0x01
    0x02b1	jmp 0x02e9_shoot_key_not_pressed    
    // {

        0x02b3	draw_spirte xreg=v4, yreg=v5, h=1       // Redraw bullet so there is no hole

        0x02b5	mov v6, 0x00                            // Unset the 'bullet in the air' flag
        
        0x02b7	mov v3, v4                              // Store bullet x position in v3
        0x02b9	add v3, 0x03                            // The actual bullet possition is 3 pixels offset from the beginning of the sprite
        0x02bb	sub v3, vb                              // vb is enemies_x sprite possition, 
                                                        // so in v2 now we have the position of the bullet with respect the origin of the enemies sprite
        0x02bd	mov v2, 0xf8 == 248 == -8
        0x02bf	and v3, v2

        0x02c1	mov v2, 0x08        // Enemy ID: b1000

        // if v3 == 0  := if (bullet possition < 8), if we hit the first enemy
        0x02c3	skipnext_eq v3, 0x00
        0x02c5	jmp 0x02c9
        // {
            0x02c7	call 0x037d_enemy_hit(enemies_alive = v2)                        
        // }

        0x02c9	right_shift v2      // Enemy ID: b0100

        // if v3 == 0x8 || v3  == 0x10 :=  (bullet possition < 24)
        0x02cb	skipnext_ne v3, 0x08 // if v3 != 0x8                     --
        0x02cd	jmp 0x02d3                                                 |
        0x02cf	skipnext_eq v3, 0x10 // if v3 == 10               --    <--    
        0x02d1	jmp 0x02d5                                          | 
        // {                                                        | 
            0x02d3	call 0x037d_enemy_hit(enemies_alive = v2)     <--          
        // }

        0x02d5	right_shift v2      // Enemy ID: 0b0010 

        // if v3 == (0x18 == 24) := (bullet possition < 32)
        0x02d7	skipnext_eq v3, 0x18
        0x02d9	jmp 0x02dd
        // {
            0x02db	call 0x037d_enemy_hit(enemies_alive = v2)         
        // }

        0x02dd	right_shift v2      // Enemy ID: 0b0001

        // if v3 == (0x20 == 32) || v3 == (0x28 == 40) := (bullet possition < 48)
        0x02df	skipnext_ne v3, 0x20
        0x02e1	jmp 0x02e7
        0x02e3	skipnext_eq v3, 0x28     
        0x02e5	jmp 0x02e9_shoot_key_not_pressed
        // {

            0x02e7	call 0x037d_enemy_hit(enemies_alive = v2) 
        // }

    // }

// }

0x02e9_shoot_key_not_pressed	

// if ve == 0 (we have killed all enemis) load next level
        skipnext_eq ve, 0x00
0x02eb	jmp 0x0307 // if ve != 0 --->
// {
    0x02ed	add v9, 0x06        // Next enemy_type
    // if v9 == (0x18 == 24)    // If we are at the last enemy type, enemy type goes back to start
                                // Nevertheless the game continues and enemies become faster
    0x02ef	skipnext_ne v9, 0x18
    // {
        0x02f1	mov v9, 0x00 // v9 = 0;
    // }

    0x02f3	mov va, 0x04    // Enemies speed, they move 4 pixels to the side

    // Reset enemies position
    0x02f5	mov vb, 0x0a    // Enemy position x = 0x0a == 10
    0x02f7	mov vc, 0x04    // Enemy position y = 0x04

    0x02f9	add vd, 0xf4    // == -12, Update frequency is faster, enemies move faster
    0x02fb	mov ve, 0x0f    // Revive enemies

    0x02fd	clear_screen

    0x02ff	call 0x0353_update_all_enemies(enemies_alive = ve, enemy_type = v9, enemy_x = vb, enemy_y = vc)
    0x0301	call 0x0375_move_player_x(pos_x = v8)
    0x0303	mov delay_timer, vd

    0x0305	jmp 0x026f_game_update_loop
// }

// Update the enemies if the timer runs out else go to the game update loop
0x0307	mov v7, delay_timer     
0x0309	skipnext_eq v7, 0x00
0x030b	jmp 0x026f_game_update_loop
// {
    0x030d	mov delay_timer, vd   // Reset update timer 
    0x030f	call 0x0353_update_all_enemies(enemies_alive = ve, enemy_type = v9, enemy_x = vb, enemy_y = vc) // Erase enemies

    0x0311	add vb, va  // Move enemies

    // if vb == (0x12  == 18) :=  If enemies reached right margin, 18 + (4 enemies * 12 pixesl) = 66 
                                // 12 pixels per enemy := 8 pixels for the enemy + 4 spacing, 
                                // so the most right enemy is 2 pixels away from the margin (64)
    0x0313	skipnext_eq vb, 0x12
    0x0315	jmp 0x031b
    // {
        0x0317	add vc, 0x02 // Enemies lower their altitude, reduce enemies_y by 2 pixels
        0x0319	mov va, 0xfc // == -4, Reverse enemies speed direction
    // }

    // if vb == 0x2 := If enemies reach the left margin
    0x031b	skipnext_eq vb, 0x02
    0x031d	jmp 0x0323
    // {
        0x031f	add vc, 0x02 // Enemies lower their altitude, reduce enemies_y by 2 pixels
        0x0321	mov va, 0x04 // Reverse speed direction
    // }

    0x0323	call 0x0353_update_all_enemies(enemies_alive = ve, enemy_type = v9, enemy_x = vb, enemy_y = vc)

    // If the enemies reach the bottom
    0x0325	skipnext_eq vc, 0x18
    0x0327	jmp 0x026f_game_update_loop
    // {
        // Draw game over screen and reset game
        0x0329	clear_screen        

        // for loop initialization
        0x032b	mov I, 0x04dd
        0x032d	mov v0, 0x14
        0x032f	mov v1, 0x08
        0x0331	mov v2, 0x0f
        // for (v0 = (0x14 == 20); v0 < (0x2c == 44); v0+=8) {
            0x0333	draw_spirte xreg=v0, yreg=v1, h=15 

        // for loop update
        0x0335	add v0, 0x08
        0x0337	add I, v2
        0x0339	skipnext_eq v0, 0x2c
        0x033b	jmp 0x0333
        // }

        // Delay for 256/60 seconds
        0x033d	mov v0, 0xff                      
        0x033f	mov delay_timer, v0
        0x0341	mov v0, delay_timer              
        0x0343	skipnext_eq v0, 0x00
        0x0345	jmp 0x0341
        // end delay

        // Wait until the user presses a key
        0x0347	store_keypress v0               

        0x0349	clear_screen

        // Clear all registers
        0x034b	mov I, 0x0706
        0x034d	mov v0:v14, [I:I+14]
        // end clear all registers

        0x034f	jmp 0x0225 // Restart Game from the very begining
    // } else {

        // goto game update loop

    // }

// Compute enemies {
0x0353_update_all_enemies(enemies_alive = ve, enemy_type = v9, enemy_x = vb, enemy_y = vc) 	
            mov I, 0x03c1_enemy_sprite_lv1                           	
    0x0353	add I, v9  // The enemy type defines the offset from the enemy_lvl_1 sprite

    0x0355	mov v1, 0x08         // -> enemy_id = 0x08
    0x0357	call 0x0369_draw_enemiges(enemis_alive = ve, enemy_id = v1 == 0x8, 
                                      enemy_position_x = vb, enemy_position_y = vc)

    0x0359	right_shift enemy_id // -> enemy_id == 0x04
    0x035b	call 0x0369_draw_enemiges(enemis_alive = ve, enemy_id = v1 == 0x4, 
                                      enemy_position_x = vb, enemy_position_y = vc)

    0x035d	right_shift enemy_id // -> enemy_id == 0x02
    0x035f	call 0x0369_draw_enemiges(enemis_alive = ve, enemy_id = v1 == 0x2, 
                                      enemy_position_x = vb, enemy_position_y = vc)

    0x0361	right_shift enemy_id // -> enemy_id == 0x01
    0x0363	call 0x0369_draw_enemiges(enemis_alive = ve, enemy_id = v1 == 0x1, 
                                      enemy_position_x = vb, enemy_position_y = vc)

    0x0365	add vb, 0xd0 == 208 == -48  // vb points to the last drawn enemy, we need to move the first enemy
                                        // 4 - 12*4 = -44
    0x0367	ret
// }

// Draw enemies subrutine {
0x0369_draw_enemiges(ve, v1, enemy_position_x = vb, enemy_position_y = vc)	
    // if enemies_alive matches the enemy being updated
            mov v0, ve                              
    0x036b	and v0, v1
    0x036d	skipnext_eq v0, 0x00
    0x036f	draw_spirte xreg=vb, yreg=vc, h=6
    0x0371	add vb, 0x0c == 12  // Next enemy will be drawn 12 pixels away from the current enemy
    0x0373	ret
// }

// Move player subrutine {
    0x0375_move_player_x(pos_x = v8)	 
            mov I, 0x03d9_player_graphics       // Load player graphics
    0x0377	mov v0, 0x1c == 28 // 28 + 4 = 32,  // compute player height
    0x0379	draw_spirte xreg=v8, yreg=v0, h=4   // Draw player, v8 contains the x possition
    0x037b	ret
// }


0x037d_enemy_hit(enemies_alive = v2)	
    call 0x0353_update_all_enemies(enemies_alive = ve, enemy_type = v9, enemy_x = vb, enemy_y = vc) // Erase enemy
    0x037f	xor ve, v2 // update if enemy was killed
    0x0381	call 0x0353_update_all_enemies(enemies_alive = ve, enemy_type = v9, enemy_x = vb, enemy_y = vc) // ReDraw enemy

    // Make a sound
    0x0383	mov v0, 0x05
    0x0385	mov sound_timer, v0

    // Delay while sound ringing
    0x0387	mov delay_timer, v0
    0x0389	mov v0, delay_timer                     
    0x038b	skipnext_eq v0, 0x00
    0x038d	jmp 0x0389
    // End delay 

0x038f	ret                                    
// }

// Update title screen subrutine (ve) {
0x0391_update_title_screen(update_index = ve, scrolling_title_y_pos = vc)	
            mov va, 0x00                            	
    0x0393	mov vd, ve
    0x0395	mov vb, 0x04

    // if start key pressed  {
    0x0397	skipnext_on_not_keypress v9       
    0x0399	jmp 0x0257_start_game // goto start game
    // } 

    0x039b	mov I, 0x060c                       
    0x039d	add I, vd
    0x039f	mov v0:v0, [I:I+0]
    0x03a1	skipnext_eq v0, 0xff
    0x03a3	jmp 0x03af
    0x03a5	mov va, 0x00                
    0x03a7	mov vb, 0x04
    0x03a9	mov vd, 0x01
    0x03ab	mov ve, 0x01
    0x03ad	jmp 0x0397
    0x03af	mov I, 0x050a                  
    0x03b1	add I, v0
    0x03b3	draw_spirte xreg=vb, yreg=vc, h=6
    0x03b5	add vb, 0x08
    0x03b7	add vd, 0x01
    0x03b9	add va, 0x01
    0x03bb	skipnext_eq va, 0x07
    0x03bd	jmp 0x0397

0x03bf	ret                         
// }

0x03c1_enemy_sprite_lv1	
        DATA = 0x3c	GRAPHIC =   ####  	ASCII(<)
0x03c2	DATA = 0x7e	GRAPHIC =  ###### 	ASCII(~)
0x03c3	DATA = 0xff	GRAPHIC = ########
0x03c4	DATA = 0xff	GRAPHIC = ########
0x03c5	DATA = 0x99	GRAPHIC = #  ##  #
0x03c6	DATA = 0x99	GRAPHIC = #  ##  #

0x03c7_enemy_sprite_lv2	
        DATA = 0x7e	GRAPHIC =  ###### 	ASCII(~)
0x03c8	DATA = 0xff	GRAPHIC = ########
0x03c9	DATA = 0xff	GRAPHIC = ########
0x03ca	DATA = 0x24	GRAPHIC =   #  #  	ASCII($)
0x03cb	DATA = 0x24	GRAPHIC =   #  #  	ASCII($)
0x03cc	DATA = 0xe7	GRAPHIC = ###  ###

0x03cd_enemy_sprite_lv3	
        DATA = 0x7e	GRAPHIC =  ###### 	ASCII(~)
0x03ce	DATA = 0xff	GRAPHIC = ########
0x03cf	DATA = 0x3c	GRAPHIC =   ####  	ASCII(<)
0x03d0	DATA = 0x3c	GRAPHIC =   ####  	ASCII(<)
0x03d1	DATA = 0x7e	GRAPHIC =  ###### 	ASCII(~)
0x03d2	DATA = 0xdb	GRAPHIC = ## ## ##

0x03d3	DATA = 0x81	GRAPHIC = #      #
0x03d4	DATA = 0x42	GRAPHIC =  #    # 	ASCII(B)
0x03d5	DATA = 0x3c	GRAPHIC =   ####  	ASCII(<)
0x03d6	DATA = 0x7e	GRAPHIC =  ###### 	ASCII(~)
0x03d7	DATA = 0xff	GRAPHIC = ########
0x03d8	DATA = 0xdb	GRAPHIC = ## ## ##

0x03d9_player_sprite	
        DATA = 0x10	GRAPHIC =    #                
0x03da	DATA = 0x38	GRAPHIC =   ###   	ASCII(8)
0x03db	DATA = 0x7c	GRAPHIC =  #####  	ASCII(|)
0x03dc	DATA = 0xfe	GRAPHIC = ####### 

0x03dd	DATA = 0x00	GRAPHIC =         
0x03de	DATA = 0x00	GRAPHIC =         
0x03df	DATA = 0x7f	GRAPHIC =  #######
0x03e0	DATA = 0x00	GRAPHIC =         
0x03e1	DATA = 0x3f	GRAPHIC =   ######	ASCII(?)
0x03e2	DATA = 0x00	GRAPHIC =         
0x03e3	DATA = 0x7f	GRAPHIC =  #######
0x03e4	DATA = 0x00	GRAPHIC =         
0x03e5	DATA = 0x00	GRAPHIC =         
0x03e6	DATA = 0x00	GRAPHIC =         
0x03e7	DATA = 0x01	GRAPHIC =        #
0x03e8	DATA = 0x01	GRAPHIC =        #
0x03e9	DATA = 0x01	GRAPHIC =        #
0x03ea	DATA = 0x03	GRAPHIC =       ##
0x03eb	DATA = 0x03	GRAPHIC =       ##
0x03ec	DATA = 0x03	GRAPHIC =       ##
0x03ed	DATA = 0x03	GRAPHIC =       ##
0x03ee	DATA = 0x00	GRAPHIC =         
0x03ef	DATA = 0x00	GRAPHIC =         
0x03f0	DATA = 0x3f	GRAPHIC =   ######	ASCII(?)
0x03f1	DATA = 0x20	GRAPHIC =   #     
0x03f2	DATA = 0x20	GRAPHIC =   #     
0x03f3	DATA = 0x20	GRAPHIC =   #     
0x03f4	DATA = 0x20	GRAPHIC =   #     
0x03f5	DATA = 0x20	GRAPHIC =   #     
0x03f6	DATA = 0x20	GRAPHIC =   #     
0x03f7	DATA = 0x20	GRAPHIC =   #     
0x03f8	DATA = 0x20	GRAPHIC =   #     
0x03f9	DATA = 0x3f	GRAPHIC =   ######	ASCII(?)
0x03fa	DATA = 0x08	GRAPHIC =     #   
0x03fb	DATA = 0x08	GRAPHIC =     #   
0x03fc	DATA = 0xff	GRAPHIC = ########
0x03fd	DATA = 0x00	GRAPHIC =         
0x03fe	DATA = 0x00	GRAPHIC =         
0x03ff	DATA = 0xfe	GRAPHIC = ####### 
0x0400	DATA = 0x00	GRAPHIC =         
0x0401	DATA = 0xfc	GRAPHIC = ######  
0x0402	DATA = 0x00	GRAPHIC =         
0x0403	DATA = 0xfe	GRAPHIC = ####### 
0x0404	DATA = 0x00	GRAPHIC =         
0x0405	DATA = 0x00	GRAPHIC =         
0x0406	DATA = 0x00	GRAPHIC =         
0x0407	DATA = 0x7e	GRAPHIC =  ###### 	ASCII(~)
0x0408	DATA = 0x42	GRAPHIC =  #    # 	ASCII(B)
0x0409	DATA = 0x42	GRAPHIC =  #    # 	ASCII(B)
0x040a	DATA = 0x62	GRAPHIC =  ##   # 	ASCII(b)
0x040b	DATA = 0x62	GRAPHIC =  ##   # 	ASCII(b)
0x040c	DATA = 0x62	GRAPHIC =  ##   # 	ASCII(b)
0x040d	DATA = 0x62	GRAPHIC =  ##   # 	ASCII(b)
0x040e	DATA = 0x00	GRAPHIC =         
0x040f	DATA = 0x00	GRAPHIC =         
0x0410	DATA = 0xff	GRAPHIC = ########
0x0411	DATA = 0x00	GRAPHIC =         
0x0412	DATA = 0x00	GRAPHIC =         
0x0413	DATA = 0x00	GRAPHIC =         
0x0414	DATA = 0x00	GRAPHIC =         
0x0415	DATA = 0x00	GRAPHIC =         
0x0416	DATA = 0x00	GRAPHIC =         
0x0417	DATA = 0x00	GRAPHIC =         
0x0418	DATA = 0x00	GRAPHIC =         
0x0419	DATA = 0xff	GRAPHIC = ########
0x041a	DATA = 0x00	GRAPHIC =         
0x041b	DATA = 0x00	GRAPHIC =         
0x041c	DATA = 0xff	GRAPHIC = ########
0x041d	DATA = 0x00	GRAPHIC =         
0x041e	DATA = 0x7d	GRAPHIC =  ##### #	ASCII(})
0x041f	DATA = 0x00	GRAPHIC =         
0x0420	DATA = 0x41	GRAPHIC =  #     #	ASCII(A)
0x0421	DATA = 0x7d	GRAPHIC =  ##### #	ASCII(})
0x0422	DATA = 0x05	GRAPHIC =      # #
0x0423	DATA = 0x7d	GRAPHIC =  ##### #	ASCII(})
0x0424	DATA = 0x7d	GRAPHIC =  ##### #	ASCII(})
0x0425	DATA = 0x00	GRAPHIC =         
0x0426	DATA = 0x00	GRAPHIC =         
0x0427	DATA = 0xc2	GRAPHIC = ##    # 
0x0428	DATA = 0xc2	GRAPHIC = ##    # 
0x0429	DATA = 0xc6	GRAPHIC = ##   ## 
0x042a	DATA = 0x44	GRAPHIC =  #   #  	ASCII(D)
0x042b	DATA = 0x6c	GRAPHIC =  ## ##  	ASCII(l)
0x042c	DATA = 0x28	GRAPHIC =   # #   	ASCII(()
0x042d	DATA = 0x38	GRAPHIC =   ###   	ASCII(8)
0x042e	DATA = 0x00	GRAPHIC =         
0x042f	DATA = 0x00	GRAPHIC =         
0x0430	DATA = 0xff	GRAPHIC = ########
0x0431	DATA = 0x00	GRAPHIC =         
0x0432	DATA = 0x00	GRAPHIC =         
0x0433	DATA = 0x00	GRAPHIC =         
0x0434	DATA = 0x00	GRAPHIC =         
0x0435	DATA = 0x00	GRAPHIC =         
0x0436	DATA = 0x00	GRAPHIC =         
0x0437	DATA = 0x00	GRAPHIC =         
0x0438	DATA = 0x00	GRAPHIC =         
0x0439	DATA = 0xff	GRAPHIC = ########
0x043a	DATA = 0x00	GRAPHIC =         
0x043b	DATA = 0x00	GRAPHIC =         
0x043c	DATA = 0xff	GRAPHIC = ########
0x043d	DATA = 0x00	GRAPHIC =         
0x043e	DATA = 0xf7	GRAPHIC = #### ###
0x043f	DATA = 0x10	GRAPHIC =    #    
0x0440	DATA = 0x14	GRAPHIC =    # #  
0x0441	DATA = 0xf7	GRAPHIC = #### ###
0x0442	DATA = 0xf7	GRAPHIC = #### ###
0x0443	DATA = 0x04	GRAPHIC =      #  
0x0444	DATA = 0x04	GRAPHIC =      #  
0x0445	DATA = 0x00	GRAPHIC =         
0x0446	DATA = 0x00	GRAPHIC =         
0x0447	DATA = 0x7c	GRAPHIC =  #####  	ASCII(|)
0x0448	DATA = 0x44	GRAPHIC =  #   #  	ASCII(D)
0x0449	DATA = 0xfe	GRAPHIC = ####### 
0x044a	DATA = 0xc2	GRAPHIC = ##    # 
0x044b	DATA = 0xc2	GRAPHIC = ##    # 
0x044c	DATA = 0xc2	GRAPHIC = ##    # 
0x044d	DATA = 0xc2	GRAPHIC = ##    # 
0x044e	DATA = 0x00	GRAPHIC =         
0x044f	DATA = 0x00	GRAPHIC =         
0x0450	DATA = 0xff	GRAPHIC = ########
0x0451	DATA = 0x00	GRAPHIC =         
0x0452	DATA = 0x00	GRAPHIC =         
0x0453	DATA = 0x00	GRAPHIC =         
0x0454	DATA = 0x00	GRAPHIC =         
0x0455	DATA = 0x00	GRAPHIC =         
0x0456	DATA = 0x00	GRAPHIC =         
0x0457	DATA = 0x00	GRAPHIC =         
0x0458	DATA = 0x00	GRAPHIC =         
0x0459	DATA = 0xff	GRAPHIC = ########
0x045a	DATA = 0x00	GRAPHIC =         
0x045b	DATA = 0x00	GRAPHIC =         
0x045c	DATA = 0xff	GRAPHIC = ########
0x045d	DATA = 0x00	GRAPHIC =         
0x045e	DATA = 0xef	GRAPHIC = ### ####
0x045f	DATA = 0x20	GRAPHIC =   #     
0x0460	DATA = 0x28	GRAPHIC =   # #   	ASCII(()
0x0461	DATA = 0xe8	GRAPHIC = ### #   
0x0462	DATA = 0xe8	GRAPHIC = ### #   
0x0463	DATA = 0x2f	GRAPHIC =   # ####	ASCII(/)
0x0464	DATA = 0x2f	GRAPHIC =   # ####	ASCII(/)
0x0465	DATA = 0x00	GRAPHIC =         
0x0466	DATA = 0x00	GRAPHIC =         
0x0467	DATA = 0xf9	GRAPHIC = #####  #
0x0468	DATA = 0x85	GRAPHIC = #    # #
0x0469	DATA = 0xc5	GRAPHIC = ##   # #
0x046a	DATA = 0xc5	GRAPHIC = ##   # #
0x046b	DATA = 0xc5	GRAPHIC = ##   # #
0x046c	DATA = 0xc5	GRAPHIC = ##   # #
0x046d	DATA = 0xf9	GRAPHIC = #####  #
0x046e	DATA = 0x00	GRAPHIC =         
0x046f	DATA = 0x00	GRAPHIC =         
0x0470	DATA = 0xff	GRAPHIC = ########
0x0471	DATA = 0x00	GRAPHIC =         
0x0472	DATA = 0x00	GRAPHIC =         
0x0473	DATA = 0x00	GRAPHIC =         
0x0474	DATA = 0x00	GRAPHIC =         
0x0475	DATA = 0x00	GRAPHIC =         
0x0476	DATA = 0x00	GRAPHIC =         
0x0477	DATA = 0x00	GRAPHIC =         
0x0478	DATA = 0x00	GRAPHIC =         
0x0479	DATA = 0xff	GRAPHIC = ########
0x047a	DATA = 0x00	GRAPHIC =         
0x047b	DATA = 0x00	GRAPHIC =         
0x047c	DATA = 0xff	GRAPHIC = ########
0x047d	DATA = 0x00	GRAPHIC =         
0x047e	DATA = 0xbe	GRAPHIC = # ##### 
0x047f	DATA = 0x00	GRAPHIC =         
0x0480	DATA = 0x20	GRAPHIC =   #     
0x0481	DATA = 0x30	GRAPHIC =   ##    	ASCII(0)
0x0482	DATA = 0x20	GRAPHIC =   #     
0x0483	DATA = 0xbe	GRAPHIC = # ##### 
0x0484	DATA = 0xbe	GRAPHIC = # ##### 
0x0485	DATA = 0x00	GRAPHIC =         
0x0486	DATA = 0x00	GRAPHIC =         
0x0487	DATA = 0xf7	GRAPHIC = #### ###
0x0488	DATA = 0x04	GRAPHIC =      #  
0x0489	DATA = 0xe7	GRAPHIC = ###  ###
0x048a	DATA = 0x85	GRAPHIC = #    # #
0x048b	DATA = 0x85	GRAPHIC = #    # #
0x048c	DATA = 0x84	GRAPHIC = #    #  
0x048d	DATA = 0xf4	GRAPHIC = #### #  
0x048e	DATA = 0x00	GRAPHIC =         
0x048f	DATA = 0x00	GRAPHIC =         
0x0490	DATA = 0xff	GRAPHIC = ########
0x0491	DATA = 0x00	GRAPHIC =         
0x0492	DATA = 0x00	GRAPHIC =         
0x0493	DATA = 0x00	GRAPHIC =         
0x0494	DATA = 0x00	GRAPHIC =         
0x0495	DATA = 0x00	GRAPHIC =         
0x0496	DATA = 0x00	GRAPHIC =         
0x0497	DATA = 0x00	GRAPHIC =         
0x0498	DATA = 0x00	GRAPHIC =         
0x0499	DATA = 0xff	GRAPHIC = ########
0x049a	DATA = 0x00	GRAPHIC =         
0x049b	DATA = 0x00	GRAPHIC =         
0x049c	DATA = 0xff	GRAPHIC = ########
0x049d	DATA = 0x00	GRAPHIC =         
0x049e	DATA = 0x00	GRAPHIC =         
0x049f	DATA = 0x7f	GRAPHIC =  #######
0x04a0	DATA = 0x00	GRAPHIC =         
0x04a1	DATA = 0x3f	GRAPHIC =   ######	ASCII(?)
0x04a2	DATA = 0x00	GRAPHIC =         
0x04a3	DATA = 0x7f	GRAPHIC =  #######
0x04a4	DATA = 0x00	GRAPHIC =         
0x04a5	DATA = 0x00	GRAPHIC =         
0x04a6	DATA = 0x00	GRAPHIC =         
0x04a7	DATA = 0xef	GRAPHIC = ### ####
0x04a8	DATA = 0x28	GRAPHIC =   # #   	ASCII(()
0x04a9	DATA = 0xef	GRAPHIC = ### ####
0x04aa	DATA = 0x00	GRAPHIC =         
0x04ab	DATA = 0xe0	GRAPHIC = ###     
0x04ac	DATA = 0x60	GRAPHIC =  ##     	ASCII(`)
0x04ad	DATA = 0x6f	GRAPHIC =  ## ####	ASCII(o)
0x04ae	DATA = 0x00	GRAPHIC =         
0x04af	DATA = 0x00	GRAPHIC =         
0x04b0	DATA = 0xff	GRAPHIC = ########
0x04b1	DATA = 0x00	GRAPHIC =         
0x04b2	DATA = 0x00	GRAPHIC =         
0x04b3	DATA = 0x00	GRAPHIC =         
0x04b4	DATA = 0x00	GRAPHIC =         
0x04b5	DATA = 0x00	GRAPHIC =         
0x04b6	DATA = 0x00	GRAPHIC =         
0x04b7	DATA = 0x00	GRAPHIC =         
0x04b8	DATA = 0x00	GRAPHIC =         
0x04b9	DATA = 0xff	GRAPHIC = ########
0x04ba	DATA = 0x00	GRAPHIC =         
0x04bb	DATA = 0x00	GRAPHIC =         
0x04bc	DATA = 0xff	GRAPHIC = ########
0x04bd	DATA = 0x00	GRAPHIC =         
0x04be	DATA = 0x00	GRAPHIC =         
0x04bf	DATA = 0xfe	GRAPHIC = ####### 
0x04c0	DATA = 0x00	GRAPHIC =         
0x04c1	DATA = 0xfc	GRAPHIC = ######  
0x04c2	DATA = 0x00	GRAPHIC =         
0x04c3	DATA = 0xfe	GRAPHIC = ####### 
0x04c4	DATA = 0x00	GRAPHIC =         
0x04c5	DATA = 0x00	GRAPHIC =         
0x04c6	DATA = 0x00	GRAPHIC =         
0x04c7	DATA = 0xc0	GRAPHIC = ##      
0x04c8	DATA = 0x00	GRAPHIC =         
0x04c9	DATA = 0xc0	GRAPHIC = ##      
0x04ca	DATA = 0xc0	GRAPHIC = ##      
0x04cb	DATA = 0xc0	GRAPHIC = ##      
0x04cc	DATA = 0xc0	GRAPHIC = ##      
0x04cd	DATA = 0xc0	GRAPHIC = ##      
0x04ce	DATA = 0x00	GRAPHIC =         
0x04cf	DATA = 0x00	GRAPHIC =         
0x04d0	DATA = 0xfc	GRAPHIC = ######  
0x04d1	DATA = 0x04	GRAPHIC =      #  
0x04d2	DATA = 0x04	GRAPHIC =      #  
0x04d3	DATA = 0x04	GRAPHIC =      #  
0x04d4	DATA = 0x04	GRAPHIC =      #  
0x04d5	DATA = 0x04	GRAPHIC =      #  
0x04d6	DATA = 0x04	GRAPHIC =      #  
0x04d7	DATA = 0x04	GRAPHIC =      #  
0x04d8	DATA = 0x04	GRAPHIC =      #  
0x04d9	DATA = 0xfc	GRAPHIC = ######  
0x04da	DATA = 0x10	GRAPHIC =    #    
0x04db	DATA = 0x10	GRAPHIC =    #    
0x04dc	DATA = 0xff	GRAPHIC = ########
0x04dd	DATA = 0xf9	GRAPHIC = #####  #
0x04de	DATA = 0x81	GRAPHIC = #      #
0x04df	DATA = 0xb9	GRAPHIC = # ###  #
0x04e0	DATA = 0x8b	GRAPHIC = #   # ##
0x04e1	DATA = 0x9a	GRAPHIC = #  ## # 
0x04e2	DATA = 0x9a	GRAPHIC = #  ## # 
0x04e3	DATA = 0xfa	GRAPHIC = ##### # 
0x04e4	DATA = 0x00	GRAPHIC =         
0x04e5	DATA = 0xfa	GRAPHIC = ##### # 
0x04e6	DATA = 0x8a	GRAPHIC = #   # # 
0x04e7	DATA = 0x9a	GRAPHIC = #  ## # 
0x04e8	DATA = 0x9a	GRAPHIC = #  ## # 
0x04e9	DATA = 0x9b	GRAPHIC = #  ## ##
0x04ea	DATA = 0x99	GRAPHIC = #  ##  #
0x04eb	DATA = 0xf8	GRAPHIC = #####   
0x04ec	DATA = 0xe6	GRAPHIC = ###  ## 
0x04ed	DATA = 0x25	GRAPHIC =   #  # #	ASCII(%)
0x04ee	DATA = 0x25	GRAPHIC =   #  # #	ASCII(%)
0x04ef	DATA = 0xf4	GRAPHIC = #### #  
0x04f0	DATA = 0x34	GRAPHIC =   ## #  	ASCII(4)
0x04f1	DATA = 0x34	GRAPHIC =   ## #  	ASCII(4)
0x04f2	DATA = 0x34	GRAPHIC =   ## #  	ASCII(4)
0x04f3	DATA = 0x00	GRAPHIC =         
0x04f4	DATA = 0x17	GRAPHIC =    # ###
0x04f5	DATA = 0x14	GRAPHIC =    # #  
0x04f6	DATA = 0x34	GRAPHIC =   ## #  	ASCII(4)
0x04f7	DATA = 0x37	GRAPHIC =   ## ###	ASCII(7)
0x04f8	DATA = 0x36	GRAPHIC =   ## ## 	ASCII(6)
0x04f9	DATA = 0x26	GRAPHIC =   #  ## 	ASCII(&)
0x04fa	DATA = 0xc7	GRAPHIC = ##   ###
0x04fb	DATA = 0xdf	GRAPHIC = ## #####
0x04fc	DATA = 0x50	GRAPHIC =  # #    	ASCII(P)
0x04fd	DATA = 0x50	GRAPHIC =  # #    	ASCII(P)
0x04fe	DATA = 0x5c	GRAPHIC =  # ###  	ASCII(\)
0x04ff	DATA = 0xd8	GRAPHIC = ## ##   
0x0500	DATA = 0xd8	GRAPHIC = ## ##   
0x0501	DATA = 0xdf	GRAPHIC = ## #####
0x0502	DATA = 0x00	GRAPHIC =         
0x0503	DATA = 0xdf	GRAPHIC = ## #####
0x0504	DATA = 0x11	GRAPHIC =    #   #
0x0505	DATA = 0x1f	GRAPHIC =    #####
0x0506	DATA = 0x12	GRAPHIC =    #  # 
0x0507	DATA = 0x1b	GRAPHIC =    ## ##
0x0508	DATA = 0x19	GRAPHIC =    ##  #
0x0509	DATA = 0xd9	GRAPHIC = ## ##  #

0x050a	DATA = 0x7c	GRAPHIC =  #####  	ASCII(|)
0x050b	DATA = 0x44	GRAPHIC =  #   #  	ASCII(D)
0x050c	DATA = 0xfe	GRAPHIC = ####### 
0x050d	DATA = 0x86	GRAPHIC = #    ## 
0x050e	DATA = 0x86	GRAPHIC = #    ## 
0x050f	DATA = 0x86	GRAPHIC = #    ## 
0x0510	DATA = 0xfc	GRAPHIC = ######  
0x0511	DATA = 0x84	GRAPHIC = #    #  
0x0512	DATA = 0xfe	GRAPHIC = ####### 
0x0513	DATA = 0x82	GRAPHIC = #     # 
0x0514	DATA = 0x82	GRAPHIC = #     # 
0x0515	DATA = 0xfe	GRAPHIC = ####### 
0x0516	DATA = 0xfe	GRAPHIC = ####### 
0x0517	DATA = 0x80	GRAPHIC = #       
0x0518	DATA = 0xc0	GRAPHIC = ##      
0x0519	DATA = 0xc0	GRAPHIC = ##      
0x051a	DATA = 0xc0	GRAPHIC = ##      
0x051b	DATA = 0xfe	GRAPHIC = ####### 
0x051c	DATA = 0xfc	GRAPHIC = ######  
0x051d	DATA = 0x82	GRAPHIC = #     # 
0x051e	DATA = 0xc2	GRAPHIC = ##    # 
0x051f	DATA = 0xc2	GRAPHIC = ##    # 
0x0520	DATA = 0xc2	GRAPHIC = ##    # 
0x0521	DATA = 0xfc	GRAPHIC = ######  
0x0522	DATA = 0xfe	GRAPHIC = ####### 
0x0523	DATA = 0x80	GRAPHIC = #       
0x0524	DATA = 0xf8	GRAPHIC = #####   
0x0525	DATA = 0xc0	GRAPHIC = ##      
0x0526	DATA = 0xc0	GRAPHIC = ##      
0x0527	DATA = 0xfe	GRAPHIC = ####### 
0x0528	DATA = 0xfe	GRAPHIC = ####### 
0x0529	DATA = 0x80	GRAPHIC = #       
0x052a	DATA = 0xf0	GRAPHIC = ####    
0x052b	DATA = 0xc0	GRAPHIC = ##      
0x052c	DATA = 0xc0	GRAPHIC = ##      
0x052d	DATA = 0xc0	GRAPHIC = ##      
0x052e	DATA = 0xfe	GRAPHIC = ####### 
0x052f	DATA = 0x80	GRAPHIC = #       
0x0530	DATA = 0xbe	GRAPHIC = # ##### 
0x0531	DATA = 0x86	GRAPHIC = #    ## 
0x0532	DATA = 0x86	GRAPHIC = #    ## 
0x0533	DATA = 0xfe	GRAPHIC = ####### 
0x0534	DATA = 0x86	GRAPHIC = #    ## 
0x0535	DATA = 0x86	GRAPHIC = #    ## 
0x0536	DATA = 0xfe	GRAPHIC = ####### 
0x0537	DATA = 0x86	GRAPHIC = #    ## 
0x0538	DATA = 0x86	GRAPHIC = #    ## 
0x0539	DATA = 0x86	GRAPHIC = #    ## 
0x053a	DATA = 0x10	GRAPHIC =    #    
0x053b	DATA = 0x10	GRAPHIC =    #    
0x053c	DATA = 0x10	GRAPHIC =    #    
0x053d	DATA = 0x10	GRAPHIC =    #    
0x053e	DATA = 0x10	GRAPHIC =    #    
0x053f	DATA = 0x10	GRAPHIC =    #    
0x0540	DATA = 0x18	GRAPHIC =    ##   
0x0541	DATA = 0x18	GRAPHIC =    ##   
0x0542	DATA = 0x18	GRAPHIC =    ##   
0x0543	DATA = 0x48	GRAPHIC =  #  #   	ASCII(H)
0x0544	DATA = 0x48	GRAPHIC =  #  #   	ASCII(H)
0x0545	DATA = 0x78	GRAPHIC =  ####   	ASCII(x)
0x0546	DATA = 0x9c	GRAPHIC = #  ###  
0x0547	DATA = 0x90	GRAPHIC = #  #    
0x0548	DATA = 0xb0	GRAPHIC = # ##    
0x0549	DATA = 0xc0	GRAPHIC = ##      
0x054a	DATA = 0xb0	GRAPHIC = # ##    
0x054b	DATA = 0x9c	GRAPHIC = #  ###  
0x054c	DATA = 0x80	GRAPHIC = #       
0x054d	DATA = 0x80	GRAPHIC = #       
0x054e	DATA = 0xc0	GRAPHIC = ##      
0x054f	DATA = 0xc0	GRAPHIC = ##      
0x0550	DATA = 0xc0	GRAPHIC = ##      
0x0551	DATA = 0xfe	GRAPHIC = ####### 
0x0552	DATA = 0xee	GRAPHIC = ### ### 
0x0553	DATA = 0x92	GRAPHIC = #  #  # 
0x0554	DATA = 0x92	GRAPHIC = #  #  # 
0x0555	DATA = 0x86	GRAPHIC = #    ## 
0x0556	DATA = 0x86	GRAPHIC = #    ## 
0x0557	DATA = 0x86	GRAPHIC = #    ## 
0x0558	DATA = 0xfe	GRAPHIC = ####### 
0x0559	DATA = 0x82	GRAPHIC = #     # 
0x055a	DATA = 0x86	GRAPHIC = #    ## 
0x055b	DATA = 0x86	GRAPHIC = #    ## 
0x055c	DATA = 0x86	GRAPHIC = #    ## 
0x055d	DATA = 0x86	GRAPHIC = #    ## 
0x055e	DATA = 0x7c	GRAPHIC =  #####  	ASCII(|)
0x055f	DATA = 0x82	GRAPHIC = #     # 
0x0560	DATA = 0x86	GRAPHIC = #    ## 
0x0561	DATA = 0x86	GRAPHIC = #    ## 
0x0562	DATA = 0x86	GRAPHIC = #    ## 
0x0563	DATA = 0x7c	GRAPHIC =  #####  	ASCII(|)
0x0564	DATA = 0xfe	GRAPHIC = ####### 
0x0565	DATA = 0x82	GRAPHIC = #     # 
0x0566	DATA = 0xfe	GRAPHIC = ####### 
0x0567	DATA = 0xc0	GRAPHIC = ##      
0x0568	DATA = 0xc0	GRAPHIC = ##      
0x0569	DATA = 0xc0	GRAPHIC = ##      
0x056a	DATA = 0x7c	GRAPHIC =  #####  	ASCII(|)
0x056b	DATA = 0x82	GRAPHIC = #     # 
0x056c	DATA = 0xc2	GRAPHIC = ##    # 
0x056d	DATA = 0xca	GRAPHIC = ##  # # 
0x056e	DATA = 0xc4	GRAPHIC = ##   #  
0x056f	DATA = 0x7a	GRAPHIC =  #### # 	ASCII(z)
0x0570	DATA = 0xfe	GRAPHIC = ####### 
0x0571	DATA = 0x86	GRAPHIC = #    ## 
0x0572	DATA = 0xfe	GRAPHIC = ####### 
0x0573	DATA = 0x90	GRAPHIC = #  #    
0x0574	DATA = 0x9c	GRAPHIC = #  ###  
0x0575	DATA = 0x84	GRAPHIC = #    #  
0x0576	DATA = 0xfe	GRAPHIC = ####### 
0x0577	DATA = 0xc0	GRAPHIC = ##      
0x0578	DATA = 0xfe	GRAPHIC = ####### 
0x0579	DATA = 0x02	GRAPHIC =       # 
0x057a	DATA = 0x02	GRAPHIC =       # 
0x057b	DATA = 0xfe	GRAPHIC = ####### 
0x057c	DATA = 0xfe	GRAPHIC = ####### 
0x057d	DATA = 0x10	GRAPHIC =    #    
0x057e	DATA = 0x30	GRAPHIC =   ##    	ASCII(0)
0x057f	DATA = 0x30	GRAPHIC =   ##    	ASCII(0)
0x0580	DATA = 0x30	GRAPHIC =   ##    	ASCII(0)
0x0581	DATA = 0x30	GRAPHIC =   ##    	ASCII(0)
0x0582	DATA = 0x82	GRAPHIC = #     # 
0x0583	DATA = 0x82	GRAPHIC = #     # 
0x0584	DATA = 0xc2	GRAPHIC = ##    # 
0x0585	DATA = 0xc2	GRAPHIC = ##    # 
0x0586	DATA = 0xc2	GRAPHIC = ##    # 
0x0587	DATA = 0xfe	GRAPHIC = ####### 
0x0588	DATA = 0x82	GRAPHIC = #     # 
0x0589	DATA = 0x82	GRAPHIC = #     # 
0x058a	DATA = 0x82	GRAPHIC = #     # 
0x058b	DATA = 0xee	GRAPHIC = ### ### 
0x058c	DATA = 0x38	GRAPHIC =   ###   	ASCII(8)
0x058d	DATA = 0x10	GRAPHIC =    #    
0x058e	DATA = 0x86	GRAPHIC = #    ## 
0x058f	DATA = 0x86	GRAPHIC = #    ## 
0x0590	DATA = 0x96	GRAPHIC = #  # ## 
0x0591	DATA = 0x92	GRAPHIC = #  #  # 
0x0592	DATA = 0x92	GRAPHIC = #  #  # 
0x0593	DATA = 0xee	GRAPHIC = ### ### 
0x0594	DATA = 0x82	GRAPHIC = #     # 
0x0595	DATA = 0x44	GRAPHIC =  #   #  	ASCII(D)
0x0596	DATA = 0x38	GRAPHIC =   ###   	ASCII(8)
0x0597	DATA = 0x38	GRAPHIC =   ###   	ASCII(8)
0x0598	DATA = 0x44	GRAPHIC =  #   #  	ASCII(D)
0x0599	DATA = 0x82	GRAPHIC = #     # 
0x059a	DATA = 0x82	GRAPHIC = #     # 
0x059b	DATA = 0x82	GRAPHIC = #     # 
0x059c	DATA = 0xfe	GRAPHIC = ####### 
0x059d	DATA = 0x30	GRAPHIC =   ##    	ASCII(0)
0x059e	DATA = 0x30	GRAPHIC =   ##    	ASCII(0)
0x059f	DATA = 0x30	GRAPHIC =   ##    	ASCII(0)
0x05a0	DATA = 0xfe	GRAPHIC = ####### 
0x05a1	DATA = 0x02	GRAPHIC =       # 
0x05a2	DATA = 0x1e	GRAPHIC =    #### 
0x05a3	DATA = 0xf0	GRAPHIC = ####    
0x05a4	DATA = 0x80	GRAPHIC = #       
0x05a5	DATA = 0xfe	GRAPHIC = ####### 
0x05a6	DATA = 0x00	GRAPHIC =         
0x05a7	DATA = 0x00	GRAPHIC =         
0x05a8	DATA = 0x00	GRAPHIC =         
0x05a9	DATA = 0x00	GRAPHIC =         
0x05aa	DATA = 0x06	GRAPHIC =      ## 
0x05ab	DATA = 0x06	GRAPHIC =      ## 
0x05ac	DATA = 0x00	GRAPHIC =         
0x05ad	DATA = 0x00	GRAPHIC =         
0x05ae	DATA = 0x00	GRAPHIC =         
0x05af	DATA = 0x60	GRAPHIC =  ##     	ASCII(`)
0x05b0	DATA = 0x60	GRAPHIC =  ##     	ASCII(`)
0x05b1	DATA = 0xc0	GRAPHIC = ##      
0x05b2	DATA = 0x00	GRAPHIC =         
0x05b3	DATA = 0x00	GRAPHIC =         
0x05b4	DATA = 0x00	GRAPHIC =         
0x05b5	DATA = 0x00	GRAPHIC =         
0x05b6	DATA = 0x00	GRAPHIC =         
0x05b7	DATA = 0x00	GRAPHIC =         
0x05b8	DATA = 0x18	GRAPHIC =    ##   
0x05b9	DATA = 0x18	GRAPHIC =    ##   
0x05ba	DATA = 0x18	GRAPHIC =    ##   
0x05bb	DATA = 0x18	GRAPHIC =    ##   
0x05bc	DATA = 0x00	GRAPHIC =         
0x05bd	DATA = 0x18	GRAPHIC =    ##   
0x05be	DATA = 0x7c	GRAPHIC =  #####  	ASCII(|)
0x05bf	DATA = 0xc6	GRAPHIC = ##   ## 
0x05c0	DATA = 0x0c	GRAPHIC =     ##  
0x05c1	DATA = 0x18	GRAPHIC =    ##   
0x05c2	DATA = 0x00	GRAPHIC =         
0x05c3	DATA = 0x18	GRAPHIC =    ##   
0x05c4	DATA = 0x00	GRAPHIC =         
0x05c5	DATA = 0x00	GRAPHIC =         
0x05c6	DATA = 0xfe	GRAPHIC = ####### 
0x05c7	DATA = 0xfe	GRAPHIC = ####### 
0x05c8	DATA = 0x00	GRAPHIC =         
0x05c9	DATA = 0x00	GRAPHIC =         
0x05ca	DATA = 0xfe	GRAPHIC = ####### 
0x05cb	DATA = 0x82	GRAPHIC = #     # 
0x05cc	DATA = 0x86	GRAPHIC = #    ## 
0x05cd	DATA = 0x86	GRAPHIC = #    ## 
0x05ce	DATA = 0x86	GRAPHIC = #    ## 
0x05cf	DATA = 0xfe	GRAPHIC = ####### 
0x05d0	DATA = 0x08	GRAPHIC =     #   
0x05d1	DATA = 0x08	GRAPHIC =     #   
0x05d2	DATA = 0x08	GRAPHIC =     #   
0x05d3	DATA = 0x18	GRAPHIC =    ##   
0x05d4	DATA = 0x18	GRAPHIC =    ##   
0x05d5	DATA = 0x18	GRAPHIC =    ##   
0x05d6	DATA = 0xfe	GRAPHIC = ####### 
0x05d7	DATA = 0x02	GRAPHIC =       # 
0x05d8	DATA = 0xfe	GRAPHIC = ####### 
0x05d9	DATA = 0xc0	GRAPHIC = ##      
0x05da	DATA = 0xc0	GRAPHIC = ##      
0x05db	DATA = 0xfe	GRAPHIC = ####### 
0x05dc	DATA = 0xfe	GRAPHIC = ####### 
0x05dd	DATA = 0x02	GRAPHIC =       # 
0x05de	DATA = 0x1e	GRAPHIC =    #### 
0x05df	DATA = 0x06	GRAPHIC =      ## 
0x05e0	DATA = 0x06	GRAPHIC =      ## 
0x05e1	DATA = 0xfe	GRAPHIC = ####### 
0x05e2	DATA = 0x84	GRAPHIC = #    #  
0x05e3	DATA = 0xc4	GRAPHIC = ##   #  
0x05e4	DATA = 0xc4	GRAPHIC = ##   #  
0x05e5	DATA = 0xfe	GRAPHIC = ####### 
0x05e6	DATA = 0x04	GRAPHIC =      #  
0x05e7	DATA = 0x04	GRAPHIC =      #  
0x05e8	DATA = 0xfe	GRAPHIC = ####### 
0x05e9	DATA = 0x80	GRAPHIC = #       
0x05ea	DATA = 0xfe	GRAPHIC = ####### 
0x05eb	DATA = 0x06	GRAPHIC =      ## 
0x05ec	DATA = 0x06	GRAPHIC =      ## 
0x05ed	DATA = 0xfe	GRAPHIC = ####### 
0x05ee	DATA = 0xc0	GRAPHIC = ##      
0x05ef	DATA = 0xc0	GRAPHIC = ##      
0x05f0	DATA = 0xc0	GRAPHIC = ##      
0x05f1	DATA = 0xfe	GRAPHIC = ####### 
0x05f2	DATA = 0x82	GRAPHIC = #     # 
0x05f3	DATA = 0xfe	GRAPHIC = ####### 
0x05f4	DATA = 0xfe	GRAPHIC = ####### 
0x05f5	DATA = 0x02	GRAPHIC =       # 
0x05f6	DATA = 0x02	GRAPHIC =       # 
0x05f7	DATA = 0x06	GRAPHIC =      ## 
0x05f8	DATA = 0x06	GRAPHIC =      ## 
0x05f9	DATA = 0x06	GRAPHIC =      ## 
0x05fa	DATA = 0x7c	GRAPHIC =  #####  	ASCII(|)
0x05fb	DATA = 0x44	GRAPHIC =  #   #  	ASCII(D)
0x05fc	DATA = 0xfe	GRAPHIC = ####### 
0x05fd	DATA = 0x86	GRAPHIC = #    ## 
0x05fe	DATA = 0x86	GRAPHIC = #    ## 
0x05ff	DATA = 0xfe	GRAPHIC = ####### 
0x0600	DATA = 0xfe	GRAPHIC = ####### 
0x0601	DATA = 0x82	GRAPHIC = #     # 
0x0602	DATA = 0xfe	GRAPHIC = ####### 
0x0603	DATA = 0x06	GRAPHIC =      ## 
0x0604	DATA = 0x06	GRAPHIC =      ## 
0x0605	DATA = 0x06	GRAPHIC =      ## 
0x0606	DATA = 0x44	GRAPHIC =  #   #  	ASCII(D)
0x0607	DATA = 0xfe	GRAPHIC = ####### 
0x0608	DATA = 0x44	GRAPHIC =  #   #  	ASCII(D)
0x0609	DATA = 0x44	GRAPHIC =  #   #  	ASCII(D)
0x060a	DATA = 0xfe	GRAPHIC = ####### 
0x060b	DATA = 0x44	GRAPHIC =  #   #  	ASCII(D)

0x060c	DATA = 0xa8	GRAPHIC = # # #   
0x060d	DATA = 0xa8	GRAPHIC = # # #   
0x060e	DATA = 0xa8	GRAPHIC = # # #   
0x060f	DATA = 0xa8	GRAPHIC = # # #   
0x0610	DATA = 0xa8	GRAPHIC = # # #   
0x0611	DATA = 0xa8	GRAPHIC = # # #   
0x0612	DATA = 0xa8	GRAPHIC = # # #   
0x0613	DATA = 0x6c	GRAPHIC =  ## ##  	ASCII(l)
0x0614	DATA = 0x5a	GRAPHIC =  # ## # 	ASCII(Z)
0x0615	DATA = 0x00	GRAPHIC =         
0x0616	DATA = 0x0c	GRAPHIC =     ##  
0x0617	DATA = 0x18	GRAPHIC =    ##   
0x0618	DATA = 0xa8	GRAPHIC = # # #   
0x0619	DATA = 0x30	GRAPHIC =   ##    	ASCII(0)
0x061a	DATA = 0x4e	GRAPHIC =  #  ### 	ASCII(N)
0x061b	DATA = 0x7e	GRAPHIC =  ###### 	ASCII(~)
0x061c	DATA = 0x00	GRAPHIC =         
0x061d	DATA = 0x12	GRAPHIC =    #  # 
0x061e	DATA = 0x18	GRAPHIC =    ##   
0x061f	DATA = 0x66	GRAPHIC =  ##  ## 	ASCII(f)
0x0620	DATA = 0x6c	GRAPHIC =  ## ##  	ASCII(l)
0x0621	DATA = 0xa8	GRAPHIC = # # #   
0x0622	DATA = 0x5a	GRAPHIC =  # ## # 	ASCII(Z)
0x0623	DATA = 0x66	GRAPHIC =  ##  ## 	ASCII(f)
0x0624	DATA = 0x54	GRAPHIC =  # # #  	ASCII(T)
0x0625	DATA = 0x24	GRAPHIC =   #  #  	ASCII($)
0x0626	DATA = 0x66	GRAPHIC =  ##  ## 	ASCII(f)
0x0627	DATA = 0x00	GRAPHIC =         
0x0628	DATA = 0x48	GRAPHIC =  #  #   	ASCII(H)
0x0629	DATA = 0x48	GRAPHIC =  #  #   	ASCII(H)
0x062a	DATA = 0x18	GRAPHIC =    ##   
0x062b	DATA = 0x12	GRAPHIC =    #  # 
0x062c	DATA = 0xa8	GRAPHIC = # # #   
0x062d	DATA = 0x06	GRAPHIC =      ## 
0x062e	DATA = 0x90	GRAPHIC = #  #    
0x062f	DATA = 0xa8	GRAPHIC = # # #   
0x0630	DATA = 0x12	GRAPHIC =    #  # 
0x0631	DATA = 0x00	GRAPHIC =         
0x0632	DATA = 0x7e	GRAPHIC =  ###### 	ASCII(~)
0x0633	DATA = 0x30	GRAPHIC =   ##    	ASCII(0)
0x0634	DATA = 0x12	GRAPHIC =    #  # 
0x0635	DATA = 0xa8	GRAPHIC = # # #   
0x0636	DATA = 0x84	GRAPHIC = #    #  
0x0637	DATA = 0x30	GRAPHIC =   ##    	ASCII(0)
0x0638	DATA = 0x4e	GRAPHIC =  #  ### 	ASCII(N)
0x0639	DATA = 0x72	GRAPHIC =  ###  # 	ASCII(r)
0x063a	DATA = 0x18	GRAPHIC =    ##   
0x063b	DATA = 0x66	GRAPHIC =  ##  ## 	ASCII(f)
0x063c	DATA = 0xa8	GRAPHIC = # # #   
0x063d	DATA = 0xa8	GRAPHIC = # # #   
0x063e	DATA = 0xa8	GRAPHIC = # # #   
0x063f	DATA = 0xa8	GRAPHIC = # # #   
0x0640	DATA = 0xa8	GRAPHIC = # # #   
0x0641	DATA = 0xa8	GRAPHIC = # # #   
0x0642	DATA = 0x90	GRAPHIC = #  #    
0x0643	DATA = 0x54	GRAPHIC =  # # #  	ASCII(T)
0x0644	DATA = 0x78	GRAPHIC =  ####   	ASCII(x)
0x0645	DATA = 0xa8	GRAPHIC = # # #   
0x0646	DATA = 0x48	GRAPHIC =  #  #   	ASCII(H)
0x0647	DATA = 0x78	GRAPHIC =  ####   	ASCII(x)
0x0648	DATA = 0x6c	GRAPHIC =  ## ##  	ASCII(l)
0x0649	DATA = 0x72	GRAPHIC =  ###  # 	ASCII(r)
0x064a	DATA = 0xa8	GRAPHIC = # # #   
0x064b	DATA = 0x12	GRAPHIC =    #  # 
0x064c	DATA = 0x18	GRAPHIC =    ##   
0x064d	DATA = 0x6c	GRAPHIC =  ## ##  	ASCII(l)
0x064e	DATA = 0x72	GRAPHIC =  ###  # 	ASCII(r)
0x064f	DATA = 0x66	GRAPHIC =  ##  ## 	ASCII(f)
0x0650	DATA = 0x54	GRAPHIC =  # # #  	ASCII(T)
0x0651	DATA = 0x90	GRAPHIC = #  #    
0x0652	DATA = 0xa8	GRAPHIC = # # #   
0x0653	DATA = 0x72	GRAPHIC =  ###  # 	ASCII(r)
0x0654	DATA = 0x2a	GRAPHIC =   # # # 	ASCII(*)
0x0655	DATA = 0x18	GRAPHIC =    ##   
0x0656	DATA = 0xa8	GRAPHIC = # # #   
0x0657	DATA = 0x30	GRAPHIC =   ##    	ASCII(0)
0x0658	DATA = 0x4e	GRAPHIC =  #  ### 	ASCII(N)
0x0659	DATA = 0x7e	GRAPHIC =  ###### 	ASCII(~)
0x065a	DATA = 0x00	GRAPHIC =         
0x065b	DATA = 0x12	GRAPHIC =    #  # 
0x065c	DATA = 0x18	GRAPHIC =    ##   
0x065d	DATA = 0x66	GRAPHIC =  ##  ## 	ASCII(f)
0x065e	DATA = 0x6c	GRAPHIC =  ## ##  	ASCII(l)
0x065f	DATA = 0xa8	GRAPHIC = # # #   
0x0660	DATA = 0x72	GRAPHIC =  ###  # 	ASCII(r)
0x0661	DATA = 0x54	GRAPHIC =  # # #  	ASCII(T)
0x0662	DATA = 0xa8	GRAPHIC = # # #   
0x0663	DATA = 0x5a	GRAPHIC =  # ## # 	ASCII(Z)
0x0664	DATA = 0x66	GRAPHIC =  ##  ## 	ASCII(f)
0x0665	DATA = 0x18	GRAPHIC =    ##   
0x0666	DATA = 0x7e	GRAPHIC =  ###### 	ASCII(~)
0x0667	DATA = 0x18	GRAPHIC =    ##   
0x0668	DATA = 0x4e	GRAPHIC =  #  ### 	ASCII(N)
0x0669	DATA = 0x72	GRAPHIC =  ###  # 	ASCII(r)
0x066a	DATA = 0xa8	GRAPHIC = # # #   
0x066b	DATA = 0x72	GRAPHIC =  ###  # 	ASCII(r)
0x066c	DATA = 0x2a	GRAPHIC =   # # # 	ASCII(*)
0x066d	DATA = 0x18	GRAPHIC =    ##   
0x066e	DATA = 0x30	GRAPHIC =   ##    	ASCII(0)
0x066f	DATA = 0x66	GRAPHIC =  ##  ## 	ASCII(f)
0x0670	DATA = 0xa8	GRAPHIC = # # #   
0x0671	DATA = 0x30	GRAPHIC =   ##    	ASCII(0)
0x0672	DATA = 0x4e	GRAPHIC =  #  ### 	ASCII(N)
0x0673	DATA = 0x7e	GRAPHIC =  ###### 	ASCII(~)
0x0674	DATA = 0x00	GRAPHIC =         
0x0675	DATA = 0x6c	GRAPHIC =  ## ##  	ASCII(l)
0x0676	DATA = 0x30	GRAPHIC =   ##    	ASCII(0)
0x0677	DATA = 0x54	GRAPHIC =  # # #  	ASCII(T)
0x0678	DATA = 0x4e	GRAPHIC =  #  ### 	ASCII(N)
0x0679	DATA = 0x9c	GRAPHIC = #  ###  
0x067a	DATA = 0xa8	GRAPHIC = # # #   
0x067b	DATA = 0xa8	GRAPHIC = # # #   
0x067c	DATA = 0xa8	GRAPHIC = # # #   
0x067d	DATA = 0xa8	GRAPHIC = # # #   
0x067e	DATA = 0xa8	GRAPHIC = # # #   
0x067f	DATA = 0xa8	GRAPHIC = # # #   
0x0680	DATA = 0xa8	GRAPHIC = # # #   
0x0681	DATA = 0x48	GRAPHIC =  #  #   	ASCII(H)
0x0682	DATA = 0x54	GRAPHIC =  # # #  	ASCII(T)
0x0683	DATA = 0x7e	GRAPHIC =  ###### 	ASCII(~)
0x0684	DATA = 0x18	GRAPHIC =    ##   
0x0685	DATA = 0xa8	GRAPHIC = # # #   
0x0686	DATA = 0x90	GRAPHIC = #  #    
0x0687	DATA = 0x54	GRAPHIC =  # # #  	ASCII(T)
0x0688	DATA = 0x78	GRAPHIC =  ####   	ASCII(x)
0x0689	DATA = 0x66	GRAPHIC =  ##  ## 	ASCII(f)
0x068a	DATA = 0xa8	GRAPHIC = # # #   
0x068b	DATA = 0x6c	GRAPHIC =  ## ##  	ASCII(l)
0x068c	DATA = 0x2a	GRAPHIC =   # # # 	ASCII(*)
0x068d	DATA = 0x30	GRAPHIC =   ##    	ASCII(0)
0x068e	DATA = 0x5a	GRAPHIC =  # ## # 	ASCII(Z)
0x068f	DATA = 0xa8	GRAPHIC = # # #   
0x0690	DATA = 0x84	GRAPHIC = #    #  
0x0691	DATA = 0x30	GRAPHIC =   ##    	ASCII(0)
0x0692	DATA = 0x72	GRAPHIC =  ###  # 	ASCII(r)
0x0693	DATA = 0x2a	GRAPHIC =   # # # 	ASCII(*)
0x0694	DATA = 0xa8	GRAPHIC = # # #   
0x0695	DATA = 0xd8	GRAPHIC = ## ##   
0x0696	DATA = 0xa8	GRAPHIC = # # #   
0x0697	DATA = 0x00	GRAPHIC =         
0x0698	DATA = 0x4e	GRAPHIC =  #  ### 	ASCII(N)
0x0699	DATA = 0x12	GRAPHIC =    #  # 
0x069a	DATA = 0xa8	GRAPHIC = # # #   
0x069b	DATA = 0xe4	GRAPHIC = ###  #  
0x069c	DATA = 0xa2	GRAPHIC = # #   # 
0x069d	DATA = 0xa8	GRAPHIC = # # #   
0x069e	DATA = 0x00	GRAPHIC =         
0x069f	DATA = 0x4e	GRAPHIC =  #  ### 	ASCII(N)
0x06a0	DATA = 0x12	GRAPHIC =    #  # 
0x06a1	DATA = 0xa8	GRAPHIC = # # #   
0x06a2	DATA = 0x6c	GRAPHIC =  ## ##  	ASCII(l)
0x06a3	DATA = 0x2a	GRAPHIC =   # # # 	ASCII(*)
0x06a4	DATA = 0x54	GRAPHIC =  # # #  	ASCII(T)
0x06a5	DATA = 0x54	GRAPHIC =  # # #  	ASCII(T)
0x06a6	DATA = 0x72	GRAPHIC =  ###  # 	ASCII(r)
0x06a7	DATA = 0xa8	GRAPHIC = # # #   
0x06a8	DATA = 0x84	GRAPHIC = #    #  
0x06a9	DATA = 0x30	GRAPHIC =   ##    	ASCII(0)
0x06aa	DATA = 0x72	GRAPHIC =  ###  # 	ASCII(r)
0x06ab	DATA = 0x2a	GRAPHIC =   # # # 	ASCII(*)
0x06ac	DATA = 0xa8	GRAPHIC = # # #   
0x06ad	DATA = 0xde	GRAPHIC = ## #### 
0x06ae	DATA = 0x9c	GRAPHIC = #  ###  
0x06af	DATA = 0xa8	GRAPHIC = # # #   
0x06b0	DATA = 0x72	GRAPHIC =  ###  # 	ASCII(r)
0x06b1	DATA = 0x2a	GRAPHIC =   # # # 	ASCII(*)
0x06b2	DATA = 0x18	GRAPHIC =    ##   
0x06b3	DATA = 0xa8	GRAPHIC = # # #   
0x06b4	DATA = 0x0c	GRAPHIC =     ##  
0x06b5	DATA = 0x54	GRAPHIC =  # # #  	ASCII(T)
0x06b6	DATA = 0x48	GRAPHIC =  #  #   	ASCII(H)
0x06b7	DATA = 0x5a	GRAPHIC =  # ## # 	ASCII(Z)
0x06b8	DATA = 0x78	GRAPHIC =  ####   	ASCII(x)
0x06b9	DATA = 0x72	GRAPHIC =  ###  # 	ASCII(r)
0x06ba	DATA = 0x18	GRAPHIC =    ##   
0x06bb	DATA = 0x66	GRAPHIC =  ##  ## 	ASCII(f)
0x06bc	DATA = 0xa8	GRAPHIC = # # #   
0x06bd	DATA = 0x66	GRAPHIC =  ##  ## 	ASCII(f)
0x06be	DATA = 0x18	GRAPHIC =    ##   
0x06bf	DATA = 0x5a	GRAPHIC =  # ## # 	ASCII(Z)
0x06c0	DATA = 0x54	GRAPHIC =  # # #  	ASCII(T)
0x06c1	DATA = 0x66	GRAPHIC =  ##  ## 	ASCII(f)
0x06c2	DATA = 0x72	GRAPHIC =  ###  # 	ASCII(r)
0x06c3	DATA = 0x6c	GRAPHIC =  ## ##  	ASCII(l)
0x06c4	DATA = 0xa8	GRAPHIC = # # #   
0x06c5	DATA = 0x72	GRAPHIC =  ###  # 	ASCII(r)
0x06c6	DATA = 0x2a	GRAPHIC =   # # # 	ASCII(*)
0x06c7	DATA = 0x00	GRAPHIC =         
0x06c8	DATA = 0x72	GRAPHIC =  ###  # 	ASCII(r)
0x06c9	DATA = 0xa8	GRAPHIC = # # #   
0x06ca	DATA = 0x72	GRAPHIC =  ###  # 	ASCII(r)
0x06cb	DATA = 0x2a	GRAPHIC =   # # # 	ASCII(*)
0x06cc	DATA = 0x18	GRAPHIC =    ##   
0x06cd	DATA = 0xa8	GRAPHIC = # # #   
0x06ce	DATA = 0x30	GRAPHIC =   ##    	ASCII(0)
0x06cf	DATA = 0x4e	GRAPHIC =  #  ### 	ASCII(N)
0x06d0	DATA = 0x7e	GRAPHIC =  ###### 	ASCII(~)
0x06d1	DATA = 0x00	GRAPHIC =         
0x06d2	DATA = 0x12	GRAPHIC =    #  # 
0x06d3	DATA = 0x18	GRAPHIC =    ##   
0x06d4	DATA = 0x66	GRAPHIC =  ##  ## 	ASCII(f)
0x06d5	DATA = 0x6c	GRAPHIC =  ## ##  	ASCII(l)
0x06d6	DATA = 0xa8	GRAPHIC = # # #   
0x06d7	DATA = 0x00	GRAPHIC =         
0x06d8	DATA = 0x66	GRAPHIC =  ##  ## 	ASCII(f)
0x06d9	DATA = 0x18	GRAPHIC =    ##   
0x06da	DATA = 0xa8	GRAPHIC = # # #   
0x06db	DATA = 0x30	GRAPHIC =   ##    	ASCII(0)
0x06dc	DATA = 0x4e	GRAPHIC =  #  ### 	ASCII(N)
0x06dd	DATA = 0x0c	GRAPHIC =     ##  
0x06de	DATA = 0x66	GRAPHIC =  ##  ## 	ASCII(f)
0x06df	DATA = 0x18	GRAPHIC =    ##   
0x06e0	DATA = 0x00	GRAPHIC =         
0x06e1	DATA = 0x6c	GRAPHIC =  ## ##  	ASCII(l)
0x06e2	DATA = 0x30	GRAPHIC =   ##    	ASCII(0)
0x06e3	DATA = 0x4e	GRAPHIC =  #  ### 	ASCII(N)
0x06e4	DATA = 0x24	GRAPHIC =   #  #  	ASCII($)
0x06e5	DATA = 0xa8	GRAPHIC = # # #   
0x06e6	DATA = 0x72	GRAPHIC =  ###  # 	ASCII(r)
0x06e7	DATA = 0x2a	GRAPHIC =   # # # 	ASCII(*)
0x06e8	DATA = 0x18	GRAPHIC =    ##   
0x06e9	DATA = 0x30	GRAPHIC =   ##    	ASCII(0)
0x06ea	DATA = 0x66	GRAPHIC =  ##  ## 	ASCII(f)
0x06eb	DATA = 0xa8	GRAPHIC = # # #   
0x06ec	DATA = 0x1e	GRAPHIC =    #### 
0x06ed	DATA = 0x54	GRAPHIC =  # # #  	ASCII(T)
0x06ee	DATA = 0x66	GRAPHIC =  ##  ## 	ASCII(f)
0x06ef	DATA = 0x0c	GRAPHIC =     ##  
0x06f0	DATA = 0x18	GRAPHIC =    ##   
0x06f1	DATA = 0x9c	GRAPHIC = #  ###  
0x06f2	DATA = 0xa8	GRAPHIC = # # #   
0x06f3	DATA = 0x24	GRAPHIC =   #  #  	ASCII($)
0x06f4	DATA = 0x54	GRAPHIC =  # # #  	ASCII(T)
0x06f5	DATA = 0x54	GRAPHIC =  # # #  	ASCII(T)
0x06f6	DATA = 0x12	GRAPHIC =    #  # 
0x06f7	DATA = 0xa8	GRAPHIC = # # #   
0x06f8	DATA = 0x42	GRAPHIC =  #    # 	ASCII(B)
0x06f9	DATA = 0x78	GRAPHIC =  ####   	ASCII(x)
0x06fa	DATA = 0x0c	GRAPHIC =     ##  
0x06fb	DATA = 0x3c	GRAPHIC =   ####  	ASCII(<)
0x06fc	DATA = 0xa8	GRAPHIC = # # #   
0x06fd	DATA = 0xae	GRAPHIC = # # ### 
0x06fe	DATA = 0xa8	GRAPHIC = # # #   
0x06ff	DATA = 0xa8	GRAPHIC = # # #   
0x0700	DATA = 0xa8	GRAPHIC = # # #   
0x0701	DATA = 0xa8	GRAPHIC = # # #   
0x0702	DATA = 0xa8	GRAPHIC = # # #   
0x0703	DATA = 0xa8	GRAPHIC = # # #   
0x0704	DATA = 0xa8	GRAPHIC = # # #   
0x0705	DATA = 0xff	GRAPHIC = ########
0x0706	DATA = 0x00	GRAPHIC =         
0x0707	DATA = 0x00	GRAPHIC =         
0x0708	DATA = 0x00	GRAPHIC =         
0x0709	DATA = 0x00	GRAPHIC =         
0x070a	DATA = 0x00	GRAPHIC =         
0x070b	DATA = 0x00	GRAPHIC =         
0x070c	DATA = 0x00	GRAPHIC =         
0x070d	DATA = 0x00	GRAPHIC =         
0x070e	DATA = 0x00	GRAPHIC =         
0x070f	DATA = 0x00	GRAPHIC =         
0x0710	DATA = 0x00	GRAPHIC =         
0x0711	DATA = 0x00	GRAPHIC =         
0x0712	DATA = 0x00	GRAPHIC =         
0x0713	DATA = 0x00	GRAPHIC =         
0x0714	DATA = 0x00	GRAPHIC =         
