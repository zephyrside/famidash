void x_movement(){
    // handle x

	old_x = player.x;
	player.x += CUBE_SPEED_X1;
	
	if(player.x > 0xf000) { // too far, don't wrap around
        if(old_x >= 0xf000){
            player.x = 0xf000; // max right
        }else{
            player.x = 0x0000; // max left
        }
		player.vel_x = 0;
	} 
	
	Generic.x = high_byte(player.x); // this is much faster than passing a pointer to player
	Generic.y = high_byte(player.y);
	Generic.width = CUBE_WIDTH;
	Generic.height = CUBE_HEIGHT;

	if (player.y < 0x0600){
		cube_data |= 0x01;	//DIE if player goes too high
	};
	
	// no L/R collision required, since that is accounted for with the death script
	
	if (bg_coll_R()) cube_data |= 0x01; // turns out, this is needed to temporarily fix zipping
	if (pad_new & PAD_A) cube_data |= 0x02;
}