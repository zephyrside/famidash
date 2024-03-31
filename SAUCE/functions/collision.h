char bg_collision_sub(void){
    if(temp_y >= 0xf0) return 0;
        
	coordinates = (temp_x >> 4) + (temp_y & 0xf0);
    // we just need 4 bits each from x and y
	
    tmp3 = temp_room&1; // high byte
    if (tmp3 && coordinates >= 0xc0) return COL_ALL;
    if (tmp3 == 0)
        collision = collisionMap0[coordinates];
    else
        collision = collisionMap1[coordinates];
	

    return is_solid[collision];
}

// replaces tmp5 = add_scroll_y(tmp1, scroll_y); temp_y = low_byte(tmp5); temp_room = high_byte(tmp5);
#define add_scroll_y_base(a, b) asm("lda %v\n jsr pusha \n lda %v \n ldx %v+1 \n jsr _add_scroll_y \n ", a, b, b)
#define add_scroll_y_store_to_temp_y_room(a, b) add_scroll_y_base(a, b); asm("sta %v \n stx %v ", temp_y, temp_room)


char bg_coll_L(void){
    // check 2 points on the left side
    temp_x = Generic.x + low_byte(scroll_x);

    eject_L = temp_x | 0xf0;
	tmp1 = Generic.y + 2;
	add_scroll_y_store_to_temp_y_room(tmp1, scroll_y);
    if(bg_collision_sub() & COL_ALL) return 1;
    
    tmp1 = Generic.y + Generic.height;
    tmp1 -= 2;
	add_scroll_y_store_to_temp_y_room(tmp1, scroll_y);
    if(bg_collision_sub() & COL_ALL) return 1;
    
    return 0;
}

char bg_coll_R(void){
    // check 2 points on the right side
	temp_x = Generic.x + low_byte(scroll_x) + Generic.width - 1;

	tmp1 = Generic.y + (Generic.height >> 1);
	add_scroll_y_store_to_temp_y_room(tmp1, scroll_y);
    if(bg_collision_sub() & COL_ALL) return 1;
    
    return 0;
}

char bg_coll_U(void){
    // check 2 points on the bottom side
	temp_x = Generic.x + low_byte(scroll_x) -1 ;
    
	tmp1 = Generic.y-1;
	add_scroll_y_store_to_temp_y_room(tmp1, scroll_y);
    eject_U = temp_y | 0xf0;
    if(bg_collision_sub() & COL_ALL) return 1;
    
    temp_x = Generic.x + low_byte(scroll_x) + Generic.width + 1;
    
    if(bg_collision_sub() & COL_ALL) return 1;
    
    return 0;
}

char bg_coll_D(void){
	if(bg_collision_sub() & COL_BOTTOM) {
		// check 2 points on the bottom side
		temp_x = Generic.x + low_byte(scroll_x) -1;

		tmp1 = Generic.y + (Generic.height/2);
		add_scroll_y_store_to_temp_y_room(tmp1, scroll_y);
		eject_D = (temp_y + 1) & 0x0f;
		if(bg_collision_sub() & COL_BOTTOM) return 1;

		temp_x = Generic.x + low_byte(scroll_x) + Generic.width +1;

		if(bg_collision_sub() & COL_BOTTOM) return 1;

		return 0;		
		
		
		
		
	}
	
	
	else {
		// check 2 points on the bottom side
		temp_x = Generic.x + low_byte(scroll_x) -1;

		tmp1 = Generic.y + Generic.height;
		add_scroll_y_store_to_temp_y_room(tmp1, scroll_y);
		eject_D = (temp_y + 1) & 0x0f;
		if(bg_collision_sub() & COL_ALL) return 1;
		
        // temp_x = Generic.x + low_byte(scroll_x) + Generic.width + 1;
        temp_x += 2 + Generic.x;

		if(bg_collision_sub() & COL_ALL) return 1;

		return 0;
	}
}



char bg_coll_D2(void){
    // check 2 points on the bottom side
    // a little lower, for jumping
    temp_x = Generic.x + low_byte(scroll_x);

    tmp1 = Generic.y + Generic.height + 2;
	add_scroll_y_store_to_temp_y_room(tmp1, scroll_y);
    if(bg_collision_sub() & COL_ALL) {
        cube_rotate = 0x0080; 
        cube_data = 0x00;
        return 1;
        }

    temp_x = Generic.x + low_byte(scroll_x) + Generic.width;
    
    if(bg_collision_sub() & COL_ALL) {
        cube_rotate = 0x0080; 
        cube_data = 0x00;
        return 1;
        }
    

    return 0;
}

char bg_coll_U2(void){
    // check 2 points on the bottom side
    // a little lower, for jumping
    temp_x = Generic.x + low_byte(scroll_x);

    tmp1 = Generic.y - 2;
	add_scroll_y_store_to_temp_y_room(tmp1, scroll_y);
    --temp_y;
    if(bg_collision_sub() & COL_ALL) {
        cube_rotate = 0x0080; 
        cube_data = 0x00;
        return 1;
    }

    temp_x = Generic.x + low_byte(scroll_x) + Generic.width;
    
    if(bg_collision_sub() & COL_ALL) {
        cube_rotate = 0x0080; 
        cube_data = 0x00;
        return 1;
    }
	
    
    return 0;
}



void bg_coll_death(void) {


	// middle point collision to kill, since hitboxes don't exist
	temp_x = Generic.x + low_byte(scroll_x) + (Generic.width >> 1)-1;

	tmp1 = Generic.y + (Generic.width >> 1);
	add_scroll_y_store_to_temp_y_room(tmp1, scroll_y);

	if(bg_collision_sub() ) cube_data = 0x01;

    
	++temp_x; // low byte

    if(bg_collision_sub() ) cube_data = 0x01;
    

	if(cube_data & 0x01) reset_level();
}