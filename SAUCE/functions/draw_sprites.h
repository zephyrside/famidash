void reset_level(void);

void draw_sprites(void){
    temp_x = high_byte(player.x);
	if(temp_x > 0xfc) temp_x = 1;
	if(temp_x == 0) temp_x = 1;
	switch (gamemode){
		default:
			cube_rotate += CUBE_GRAVITY;
			if (cube_rotate > 0x05FF) cube_rotate -= 0x0600;

			if (!gravity) oam_meta_spr(temp_x, high_byte(player.y)-1, CUBE[high_byte(cube_rotate)]);
			else oam_meta_spr_vflipped(temp_x, high_byte(player.y)-1, CUBE[high_byte(cube_rotate)]);

			break;
    }
}