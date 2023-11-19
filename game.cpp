#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)

float player_1_pos_y,player_1_dp,player_2_pos_y, player_2_dp;
float arena_half_size_x = 100, arena_half_size_y = 50;
float player_half_size_x = 1, player_half_size_y = 10;
float ball_p_x, ball_p_y, ball_dp_x = 100, ball_dp_y = 0, ball_half_size = 1;
/*
internal void simulate_player(float *p, float *dp, float ddp, float dt) {
	ddp -= *dp * 30.f;

	*dp = *dp + ddp * dt;
	*p = *p + *dp * dt + .5f * ddp * dt * dt;

	if (*p + player_half_size_y > arena_half_size_y) {
		*p = arena_half_size_y - player_half_size_y;
		*dp *= -3;
	}
	else if (*p - player_half_size_y < -arena_half_size_y) {
		*p = -arena_half_size_y + player_half_size_y;
		*dp *= -3;
	}
}
*/
internal_variable void
simulate_game(Input* input, float dt) {
	clear_screen(0x000000);

	float player_1_ddp = 0.f;
	if (is_down(BUTTON_UP)) player_1_ddp += 2500;
	if (is_down(BUTTON_DOWN)) player_1_ddp -= 2500;

	float player_2_ddp = 0.f;
	if (is_down(BUTTON_W)) player_2_ddp += 3000;
	if (is_down(BUTTON_S)) player_2_ddp -= 3000;

	//simulate_player(&player_1_pos_y, &player_1_dp, player_1_ddp, dt);
	//simulate_player(&player_2_pos_y, &player_2_dp, player_2_ddp, dt);
	
	player_1_ddp -= player_1_dp * 30.f;

	player_1_dp = player_1_dp + player_1_ddp * dt;
	player_1_pos_y = player_1_pos_y + player_1_dp * dt + .5f * player_1_ddp * dt * dt;

	if (player_1_pos_y + player_half_size_y > arena_half_size_y) {
		player_1_pos_y = arena_half_size_y - player_half_size_y;
		player_1_dp *= -3;
	}
	else if (player_1_pos_y - player_half_size_y < -arena_half_size_y) {
		player_1_pos_y = -arena_half_size_y + player_half_size_y;
		player_1_dp *= -3;
	}

	player_2_ddp -= player_2_dp * 30.f;

	player_2_dp = player_2_dp + player_2_ddp * dt;
	player_2_pos_y = player_2_pos_y + player_2_dp * dt + .5f * player_2_ddp * dt * dt;

	if (player_2_pos_y + player_half_size_y > arena_half_size_y) {
		player_2_pos_y = arena_half_size_y - player_half_size_y;
		player_2_ddp *= -3;
	}
	else if (player_2_pos_y - player_half_size_y < -arena_half_size_y) {
		player_2_pos_y = -arena_half_size_y + player_half_size_y;
		player_2_ddp *= -3;
	}
	
	ball_p_x += ball_dp_x * dt;
	ball_p_y += ball_dp_y * dt;

	if (ball_p_x + ball_half_size > 85 - player_half_size_x &&
		ball_p_x - ball_half_size < 85 + player_half_size_x &&
		ball_p_y + ball_half_size > player_1_pos_y - player_half_size_y &&
		ball_p_y + ball_half_size < player_1_pos_y + player_half_size_y) {
		ball_p_x = 85 - player_half_size_x - ball_half_size;
		ball_dp_x *= -1;
		ball_dp_y = (ball_p_y - player_1_pos_y) * 5 + player_1_dp * 1.5f;
	}else if (ball_p_x + ball_half_size > -85 - player_half_size_x &&
		ball_p_x - ball_half_size < -85 + player_half_size_x &&
		ball_p_y + ball_half_size > player_2_pos_y - player_half_size_y &&
		ball_p_y + ball_half_size < player_2_pos_y + player_half_size_y) {
		ball_p_x = -85 + player_half_size_x + ball_half_size;
		ball_dp_x *= -1;
		ball_dp_y = (ball_p_y - player_2_pos_y) * 5 + player_2_dp * 1.5f;
	}


	if (ball_p_y + ball_half_size > arena_half_size_y) {
		ball_p_y = arena_half_size_y - ball_half_size;
		ball_dp_y *= -1;
	} else if (ball_p_y + ball_half_size < -arena_half_size_y) {
		ball_p_y = -arena_half_size_y + ball_half_size;
		ball_dp_y *= -1;
	}
	

	if (ball_p_x + ball_half_size > arena_half_size_x) {
		ball_p_x = 0;
		ball_p_y = 0;
		ball_dp_x *= -1;
		ball_dp_y = 0;
	}
	else if (ball_p_x - ball_half_size < -arena_half_size_x) {
		ball_p_x = 0;
		ball_p_y = 0;
		ball_dp_x *= -1;
		ball_dp_y = 0;
	}

	
	draw_rect(ball_p_x, ball_p_y, ball_half_size, ball_half_size, 0xffffff);
	draw_rect(-85, player_2_pos_y, player_half_size_x, player_half_size_y, 0xffffff);
	draw_rect(85, player_1_pos_y, player_half_size_x, player_half_size_y, 0xffffff);
}