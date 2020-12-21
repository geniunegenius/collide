#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)

float player_pos_x = -75.f;
float player_pos_y = 0.f;
float enemy_x[13] = {-60.f, -50.f, -40.f, -30.f, -20.f, -10.f, .0f, 10.f, 20.f, 30.f, 40.f, 50.f, 60.f}, enemy_y[13], enemy_dp_x, enemy_dp_y = 45.f;
float enemy_hs = 2;
int ok[13];
int player_deaths, player_points;
int points_x[6] = { -35.f, -31.f, -11.f, 10.f, 50.f }, points_y[6] = { 11.f, 28.f, -4.f, -12.f, 0.f }, current_points, pn, points_hs = 1.f, points_count;
bool points_ok[6];
int leveladiacenta;
bool sb_ok = false;

void set_points() {
	points_ok[0] = 0;
	points_x[0] = -35.f;
	points_y[0] = 11.f;
	points_ok[1] = 0;
	points_x[1] = -31.f;
	points_y[1] = 28.f;
	points_ok[2] = 0;
	points_x[2] = -11.f;
	points_y[2] = -4.f;
	points_ok[3] = 0;
	points_x[3] = 10.f;
	points_y[3] = -12.f;
	points_ok[4] = 0;
	points_x[4] = 50.f;
	points_y[4] = 0.f;
}

const int VMAX = 300;

struct Edge {
	int x, y;
	Edge(int x = 0, int y = 0) {
		this->x = x;
		this->y = y;
	}
	operator bool() {
		return this->x || this->y;
	}
};

int plvl = 1, nlvl = 2; // previous level, next level
Edge ad[VMAX][VMAX];

bool findEdge(Edge edge) {
	if (ad[edge.x][edge.y])
		return 1;
	return 0;
}

void removeEdge(Edge edge) {
	ad[edge.x][edge.y] = ad[edge.y][edge.x] = false;
}

void insertEdge(Edge edge) {
	ad[edge.x][edge.y] = ad[edge.y][edge.x] = true;
}

enum Gamemode {
	GM_MENU,
	GM_GAMEPLAY,	
};
Gamemode current_gamemode;
bool hot_button;
bool gameplay;

internal void
simulate_game(Input* input, float dt) {
	clear_screen(0x0029f3);


	if (current_gamemode == GM_GAMEPLAY) {
		if (gameplay)
			running = false;
		float speed = 30.f; //units per sec
		float start_pos_x = -75.f;
		float end_pos_x = 100.f;

		// constructia grafului de level
		if (findEdge(Edge(plvl, nlvl)) == 0) { // se deseneaza primul level daca nu l-a terminat
			//draw the levels
			//draw map lv1
			clear_screen(0x0029f3);
			draw_rect(start_pos_x, 0, 10, 35, 0xf3f3f3);
			draw_rect(start_pos_x + 75, 0, 65, 35, 0x00f3f3);
			draw_rect(start_pos_x + 150, 0, 10, 35, 0x07f300);
			draw_rect(start_pos_x + 155, 0, 5, 35, 0x00f3f3);
			draw_text("S", 79.f, 30.f, .7f, 0xfff702);
			draw_text("C", 79.f, 24.f, .7f, 0xfff702);
			draw_text("O", 79.f, 18.f, .7f, 0xfff702);
			draw_text("R", 79.f, 12.f, .7f, 0xfff702);
			draw_text("E", 79.f, 6.f, .7f, 0xfff702);
			draw_text("B", 79.f, 0.f, .7f, 0xfff702);
			draw_text("O", 79.f, -6.f, .7f, 0xfff702);
			draw_text("A", 79.f, -12.f, .7f, 0xfff702);
			draw_text("R", 79.f, -18.f, .7f, 0xfff702);
			draw_text("D", 79.f, -24.f, .7f, 0xfff702);
			//draw points
			pn = 0;
			//collision points test
			if (player_pos_x + 2 * points_hs > points_x[pn] && player_pos_x - 2 * points_hs < points_x[pn]) {
				if (player_pos_y + 2 * points_hs > points_y[pn] && player_pos_y - 2 * points_hs < points_y[pn]) {
					points_x[pn] = -1000.f;
					points_y[pn] = -1000.f;
					player_points++;
					points_count++;
					points_ok[pn] = 1;
				}
			}
			if (points_ok[pn] == 0) {
				draw_rect(points_x[pn], points_y[pn], 1, 1, 0xfff702);
			}
			pn = 1;
			//collision points test
			if (player_pos_x + 2 * points_hs > points_x[pn] && player_pos_x - 2 * points_hs < points_x[pn]) {
				if (player_pos_y + 2 * points_hs > points_y[pn] && player_pos_y - 2 * points_hs < points_y[pn]) {
					points_x[pn] = -1000.f;
					points_y[pn] = -1000.f;
					player_points++;
					points_count++;
					points_ok[pn] = 1;
				}
			}
			if (points_ok[pn] == 0) {
				draw_rect(points_x[pn], points_y[pn], 1, 1, 0xfff702);
			}
			pn = 2;
			//collision points test
			if (player_pos_x + 2 * points_hs > points_x[pn] && player_pos_x - 2 * points_hs < points_x[pn]) {
				if (player_pos_y + 2 * points_hs > points_y[pn] && player_pos_y - 2 * points_hs < points_y[pn]) {
					points_x[pn] = -1000.f;
					points_y[pn] = -1000.f;
					player_points++;
					points_count++;
					points_ok[pn] = 1;
				}
			}
			if (points_ok[pn] == 0) {
				draw_rect(points_x[pn], points_y[pn], 1, 1, 0xfff702);
			}
			pn = 3;
			//collision points test
			if (player_pos_x + 2 * points_hs > points_x[pn] && player_pos_x - 2 * points_hs < points_x[pn]) {
				if (player_pos_y + 2 * points_hs > points_y[pn] && player_pos_y - 2 * points_hs < points_y[pn]) {
					points_x[pn] = -1000.f;
					points_y[pn] = -1000.f;
					player_points++;
					points_count++;
					points_ok[pn] = 1;
				}
			}
			if (points_ok[pn] == 0) {
				draw_rect(points_x[pn], points_y[pn], 1, 1, 0xfff702);
			}
			pn = 4;
			//collision points test
			if (player_pos_x + 2 * points_hs > points_x[pn] && player_pos_x - 2 * points_hs < points_x[pn]) {
				if (player_pos_y + 2 * points_hs > points_y[pn] && player_pos_y - 2 * points_hs < points_y[pn]) {
					points_x[pn] = -1000.f;
					points_y[pn] = -1000.f;
					player_points++;
					points_count++;
					points_ok[pn] = 1;
				}
			}
			if (points_ok[pn] == 0) {
				draw_rect(points_x[pn], points_y[pn], 1, 1, 0xfff702);
			}

			if (is_down(BUTTON_UP))
			{
				if (player_pos_y <= 32.f)
					player_pos_y += speed * dt;
			}
			draw_rect(player_pos_x, player_pos_y, 2, 2, 0xff0000);
			if (is_down(BUTTON_DOWN))
			{
				if (player_pos_y >= -32.f)
					player_pos_y -= speed * dt;
			}
			draw_rect(player_pos_x, player_pos_y, 2, 2, 0xff0000);
			if (is_down(BUTTON_LEFT))
			{
				if (player_pos_x >= -82.f)
					player_pos_x -= speed * dt;
			}
			draw_rect(player_pos_x, player_pos_y, 2, 2, 0xff0000);
			if (is_down(BUTTON_RIGHT))
			{
				if (player_pos_x <= 82.f)
					player_pos_x += speed * dt;
			}
			draw_rect(player_pos_x, player_pos_y, 2, 2, 0xff0000);



			// draw enemies
			int i = 0;
			if (enemy_y[i] > -31.f && ok[i] == 0) {
				enemy_x[i] -= enemy_dp_x * dt;
				enemy_y[i] -= enemy_dp_y * dt;
				if (enemy_y[i] < -31.f)
					ok[i] = 1;
			}
			else
				if (enemy_y[i] < 31.f && ok[i] == 1)
				{
					enemy_x[i] += enemy_dp_x * dt;
					enemy_y[i] += enemy_dp_y * dt;
					if (enemy_y[i] > 31.f)
						ok[i] = 0;
				}
			draw_rect(enemy_x[i], enemy_y[i], enemy_hs, enemy_hs, 0xff0000);

			//collision test
			if (player_pos_x + 2 * enemy_hs > enemy_x[i] && player_pos_x - 2 * enemy_hs < enemy_x[i]) {
				if (player_pos_y + 2 * enemy_hs > enemy_y[i] && player_pos_y - 2 * enemy_hs < enemy_y[i]) {
					player_pos_x = -75.f;
					player_pos_y = 0.f;
					player_deaths++;
					set_points();
					points_count = 0;
					player_points = current_points;
					draw_rect(player_pos_x, player_pos_y, 2, 2, 0xff0000);
				}
			}

			i = 1;
			if (enemy_y[i] < 31.f && ok[i] == 0) {
				enemy_x[i] += enemy_dp_x * dt;
				enemy_y[i] += enemy_dp_y * dt;
				if (enemy_y[i] > 31.f)
					ok[i] = 1;
			}
			else
				if (enemy_y[i] > -31.f && ok[i] == 1)
				{
					enemy_x[i] -= enemy_dp_x * dt;
					enemy_y[i] -= enemy_dp_y * dt;
					if (enemy_y[i] < -31.f)
						ok[i] = 0;
				}
			draw_rect(enemy_x[i], enemy_y[i], 2, 2, 0xff0000);
			//collision test
			if (player_pos_x + 2 * enemy_hs > enemy_x[i] && player_pos_x - 2 * enemy_hs < enemy_x[i]) {
				if (player_pos_y + 2 * enemy_hs > enemy_y[i] && player_pos_y - 2 * enemy_hs < enemy_y[i]) {
					player_pos_x = -75.f;
					player_pos_y = 0.f;
					player_deaths++;
					set_points();
					points_count = 0;
					player_points = current_points;
					draw_rect(player_pos_x, player_pos_y, 2, 2, 0xff0000);
				}
			}

			i = 2;
			if (enemy_y[i] > -31.f && ok[i] == 0) {
				enemy_x[i] -= enemy_dp_x * dt;
				enemy_y[i] -= enemy_dp_y * dt;
				if (enemy_y[i] < -31.f)
					ok[i] = 1;
			}
			else
				if (enemy_y[i] < 31.f && ok[i] == 1)
				{
					enemy_x[i] += enemy_dp_x * dt;
					enemy_y[i] += enemy_dp_y * dt;
					if (enemy_y[i] > 31.f)
						ok[i] = 0;
				}
			draw_rect(enemy_x[i], enemy_y[i], 2, 2, 0xff0000);
			//collision test
			if (player_pos_x + 2 * enemy_hs > enemy_x[i] && player_pos_x - 2 * enemy_hs < enemy_x[i]) {
				if (player_pos_y + 2 * enemy_hs > enemy_y[i] && player_pos_y - 2 * enemy_hs < enemy_y[i]) {
					player_pos_x = -75.f;
					player_pos_y = 0.f;
					player_deaths++;
					set_points();
					points_count = 0;
					player_points = current_points;
					draw_rect(player_pos_x, player_pos_y, 2, 2, 0xff0000);
				}
			}


			i = 3;
			if (enemy_y[i] < 31.f && ok[i] == 0) {
				enemy_x[i] += enemy_dp_x * dt;
				enemy_y[i] += enemy_dp_y * dt;
				if (enemy_y[i] > 31.f)
					ok[i] = 1;
			}
			else
				if (enemy_y[i] > -31.f && ok[i] == 1)
				{
					enemy_x[i] -= enemy_dp_x * dt;
					enemy_y[i] -= enemy_dp_y * dt;
					if (enemy_y[i] < -31.f)
						ok[i] = 0;
				}
			draw_rect(enemy_x[i], enemy_y[i], 2, 2, 0xff0000);
			//collision test
			if (player_pos_x + 2 * enemy_hs > enemy_x[i] && player_pos_x - 2 * enemy_hs < enemy_x[i]) {
				if (player_pos_y + 2 * enemy_hs > enemy_y[i] && player_pos_y - 2 * enemy_hs < enemy_y[i]) {
					player_pos_x = -75.f;
					player_pos_y = 0.f;
					player_deaths++;
					set_points();
					points_count = 0;
					player_points = current_points;
					draw_rect(player_pos_x, player_pos_y, 2, 2, 0xff0000);
				}
			}

			i = 4;
			if (enemy_y[i] > -31.f && ok[i] == 0) {
				enemy_x[i] -= enemy_dp_x * dt;
				enemy_y[i] -= enemy_dp_y * dt;
				if (enemy_y[i] < -31.f)
					ok[i] = 1;
			}
			else
				if (enemy_y[i] < 31.f && ok[i] == 1)
				{
					enemy_x[i] += enemy_dp_x * dt;
					enemy_y[i] += enemy_dp_y * dt;
					if (enemy_y[i] > 31.f)
						ok[i] = 0;
				}
			draw_rect(enemy_x[i], enemy_y[i], 2, 2, 0xff0000);
			//collision test
			if (player_pos_x + 2 * enemy_hs > enemy_x[i] && player_pos_x - 2 * enemy_hs < enemy_x[i]) {
				if (player_pos_y + 2 * enemy_hs > enemy_y[i] && player_pos_y - 2 * enemy_hs < enemy_y[i]) {
					player_pos_x = -75.f;
					player_pos_y = 0.f;
					player_deaths++;
					set_points();
					points_count = 0;
					player_points = current_points;
					draw_rect(player_pos_x, player_pos_y, 2, 2, 0xff0000);
				}
			}

			i = 5;
			if (enemy_y[i] < 31.f && ok[i] == 0) {
				enemy_x[i] += enemy_dp_x * dt;
				enemy_y[i] += enemy_dp_y * dt;
				if (enemy_y[i] > 31.f)
					ok[i] = 1;
			}
			else
				if (enemy_y[i] > -31.f && ok[i] == 1)
				{
					enemy_x[i] -= enemy_dp_x * dt;
					enemy_y[i] -= enemy_dp_y * dt;
					if (enemy_y[i] < -31.f)
						ok[i] = 0;
				}
			draw_rect(enemy_x[i], enemy_y[i], 2, 2, 0xff0000);
			//collision test
			if (player_pos_x + 2 * enemy_hs > enemy_x[i] && player_pos_x - 2 * enemy_hs < enemy_x[i]) {
				if (player_pos_y + 2 * enemy_hs > enemy_y[i] && player_pos_y - 2 * enemy_hs < enemy_y[i]) {
					player_pos_x = -75.f;
					player_pos_y = 0.f;
					player_deaths++;
					set_points();
					points_count = 0;
					player_points = current_points;
					draw_rect(player_pos_x, player_pos_y, 2, 2, 0xff0000);
				}
			}

			i = 6;
			if (enemy_y[i] > -31.f && ok[i] == 0) {
				enemy_x[i] -= enemy_dp_x * dt;
				enemy_y[i] -= enemy_dp_y * dt;
				if (enemy_y[i] < -31.f)
					ok[i] = 1;
			}
			else
				if (enemy_y[i] < 31.f && ok[i] == 1)
				{
					enemy_x[i] += enemy_dp_x * dt;
					enemy_y[i] += enemy_dp_y * dt;
					if (enemy_y[i] > 31.f)
						ok[i] = 0;
				}
			draw_rect(enemy_x[i], enemy_y[i], 2, 2, 0xff0000);
			//collision test
			if (player_pos_x + 2 * enemy_hs > enemy_x[i] && player_pos_x - 2 * enemy_hs < enemy_x[i]) {
				if (player_pos_y + 2 * enemy_hs > enemy_y[i] && player_pos_y - 2 * enemy_hs < enemy_y[i]) {
					player_pos_x = -75.f;
					player_pos_y = 0.f;
					player_deaths++;
					set_points();
					points_count = 0;
					player_points = current_points;
					draw_rect(player_pos_x, player_pos_y, 2, 2, 0xff0000);
				}
			}

			i = 7;
			if (enemy_y[i] < 31.f && ok[i] == 0) {
				enemy_x[i] += enemy_dp_x * dt;
				enemy_y[i] += enemy_dp_y * dt;
				if (enemy_y[i] > 31.f)
					ok[i] = 1;
			}
			else
				if (enemy_y[i] > -31.f && ok[i] == 1)
				{
					enemy_x[i] -= enemy_dp_x * dt;
					enemy_y[i] -= enemy_dp_y * dt;
					if (enemy_y[i] < -31.f)
						ok[i] = 0;
				}
			draw_rect(enemy_x[i], enemy_y[i], 2, 2, 0xff0000);
			//collision test
			if (player_pos_x + 2 * enemy_hs > enemy_x[i] && player_pos_x - 2 * enemy_hs < enemy_x[i]) {
				if (player_pos_y + 2 * enemy_hs > enemy_y[i] && player_pos_y - 2 * enemy_hs < enemy_y[i]) {
					player_pos_x = -75.f;
					player_pos_y = 0.f;
					player_deaths++;
					set_points();
					points_count = 0;
					player_points = current_points;
					draw_rect(player_pos_x, player_pos_y, 2, 2, 0xff0000);
				}
			}

			i = 8;
			if (enemy_y[i] > -31.f && ok[i] == 0) {
				enemy_x[i] -= enemy_dp_x * dt;
				enemy_y[i] -= enemy_dp_y * dt;
				if (enemy_y[i] < -31.f)
					ok[i] = 1;
			}
			else
				if (enemy_y[i] < 31.f && ok[i] == 1)
				{
					enemy_x[i] += enemy_dp_x * dt;
					enemy_y[i] += enemy_dp_y * dt;
					if (enemy_y[i] > 31.f)
						ok[i] = 0;
				}
			draw_rect(enemy_x[i], enemy_y[i], 2, 2, 0xff0000);
			//collision test
			if (player_pos_x + 2 * enemy_hs > enemy_x[i] && player_pos_x - 2 * enemy_hs < enemy_x[i]) {
				if (player_pos_y + 2 * enemy_hs > enemy_y[i] && player_pos_y - 2 * enemy_hs < enemy_y[i]) {
					player_pos_x = -75.f;
					player_pos_y = 0.f;
					player_deaths++;
					set_points();
					points_count = 0;
					player_points = current_points;
					draw_rect(player_pos_x, player_pos_y, 2, 2, 0xff0000);
				}
			}

			i = 9;
			if (enemy_y[i] < 31.f && ok[i] == 0) {
				enemy_x[i] += enemy_dp_x * dt;
				enemy_y[i] += enemy_dp_y * dt;
				if (enemy_y[i] > 31.f)
					ok[i] = 1;
			}
			else
				if (enemy_y[i] > -31.f && ok[i] == 1)
				{
					enemy_x[i] -= enemy_dp_x * dt;
					enemy_y[i] -= enemy_dp_y * dt;
					if (enemy_y[i] < -31.f)
						ok[i] = 0;
				}
			draw_rect(enemy_x[i], enemy_y[i], 2, 2, 0xff0000);
			//collision test
			if (player_pos_x + 2 * enemy_hs > enemy_x[i] && player_pos_x - 2 * enemy_hs < enemy_x[i]) {
				if (player_pos_y + 2 * enemy_hs > enemy_y[i] && player_pos_y - 2 * enemy_hs < enemy_y[i]) {
					player_pos_x = -75.f;
					player_pos_y = 0.f;
					player_deaths++;
					set_points();
					points_count = 0;
					player_points = current_points;
					draw_rect(player_pos_x, player_pos_y, 2, 2, 0xff0000);
				}
			}

			i = 10;
			if (enemy_y[i] > -31.f && ok[i] == 0) {
				enemy_x[i] -= enemy_dp_x * dt;
				enemy_y[i] -= enemy_dp_y * dt;
				if (enemy_y[i] < -31.f)
					ok[i] = 1;
			}
			else
				if (enemy_y[i] < 31.f && ok[i] == 1)
				{
					enemy_x[i] += enemy_dp_x * dt;
					enemy_y[i] += enemy_dp_y * dt;
					if (enemy_y[i] > 31.f)
						ok[i] = 0;
				}
			draw_rect(enemy_x[i], enemy_y[i], 2, 2, 0xff0000);
			//collision test
			if (player_pos_x + 2 * enemy_hs > enemy_x[i] && player_pos_x - 2 * enemy_hs < enemy_x[i]) {
				if (player_pos_y + 2 * enemy_hs > enemy_y[i] && player_pos_y - 2 * enemy_hs < enemy_y[i]) {
					player_pos_x = -75.f;
					player_pos_y = 0.f;
					player_deaths++;
					set_points();
					points_count = 0;
					player_points = current_points;
					draw_rect(player_pos_x, player_pos_y, 2, 2, 0xff0000);
				}
			}

			i = 11;
			if (enemy_y[i] < 31.f && ok[i] == 0) {
				enemy_x[i] += enemy_dp_x * dt;
				enemy_y[i] += enemy_dp_y * dt;
				if (enemy_y[i] > 31.f)
					ok[i] = 1;
			}
			else
				if (enemy_y[i] > -31.f && ok[i] == 1)
				{
					enemy_x[i] -= enemy_dp_x * dt;
					enemy_y[i] -= enemy_dp_y * dt;
					if (enemy_y[i] < -31.f)
						ok[i] = 0;
				}
			draw_rect(enemy_x[i], enemy_y[i], 2, 2, 0xff0000);
			//collision test
			if (player_pos_x + 2 * enemy_hs > enemy_x[i] && player_pos_x - 2 * enemy_hs < enemy_x[i]) {
				if (player_pos_y + 2 * enemy_hs > enemy_y[i] && player_pos_y - 2 * enemy_hs < enemy_y[i]) {
					player_pos_x = -75.f;
					player_pos_y = 0.f;
					player_deaths++;
					set_points();
					points_count = 0;
					player_points = current_points;
					draw_rect(player_pos_x, player_pos_y, 2, 2, 0xff0000);
				}
			}

			i = 12;
			if (enemy_y[i] > -31.f && ok[i] == 0) {
				enemy_x[i] -= enemy_dp_x * dt;
				enemy_y[i] -= enemy_dp_y * dt;
				if (enemy_y[i] < -31.f)
					ok[i] = 1;
			}
			else
				if (enemy_y[i] < 31.f && ok[i] == 1)
				{
					enemy_x[i] += enemy_dp_x * dt;
					enemy_y[i] += enemy_dp_y * dt;
					if (enemy_y[i] > 31.f)
						ok[i] = 0;
				}
			draw_rect(enemy_x[i], enemy_y[i], 2, 2, 0xff0000);
			//collision test
			if (player_pos_x + 2 * enemy_hs > enemy_x[i] && player_pos_x - 2 * enemy_hs < enemy_x[i]) {
				if (player_pos_y + 2 * enemy_hs > enemy_y[i] && player_pos_y - 2 * enemy_hs < enemy_y[i]) {
					player_pos_x = -75.f;
					player_pos_y = 0.f;
					player_deaths++;
					set_points();
					points_count = 0;
					player_points = current_points;
					draw_rect(player_pos_x, player_pos_y, 2, 2, 0xff0000);
				}
			}


			

			//draw text
			//DEATHS
			draw_text("DEATHS ", -65, 41.5f, .5f, 0xbbffbb);
			draw_number(player_deaths, -40, 40, .7f, 0xbbffbb);

			//POINTS
			draw_text("POINTS ", -10, 41.5f, .5f, 0xbbffbb);
			draw_number(player_points, 15, 40, .7f, 0xbbffbb);

			//level
			draw_text("LEVEL ", 40, 41.5f, .5f, 0xbbffbb);
			draw_number(plvl, 60, 40, .7f, 0xbbffbb);

			if (player_pos_x > 70.f && player_pos_x < 85 && points_count == 5) {
				player_pos_x = -75.f;
				player_pos_y = .0f;
				draw_rect(player_pos_x, player_pos_y, 2, 2, 0xff0000);
				set_points();
				points_count = 0;
				current_points = player_points;
				player_points = current_points;
				insertEdge(Edge(plvl, nlvl));
				plvl = nlvl;
				nlvl++;
				enemy_dp_y += 5.f;
			}
			else {
				if (player_pos_x > 65.f && player_pos_x < 85 && points_count < 5) {
					set_points();
					player_points = current_points;
				}
			}
			//scoreboard
			if (player_pos_x > 80) {
				clear_screen(0xfff702);
				draw_text("YOU DIED ", -90, 40, .5f, 0xff0202);
				draw_number(player_deaths, -60, 38.5f, .7f, 0x020aff);
				draw_text(" TIMES", -55, 40, .5f, 0xff0202);
				draw_text("YOUR SCORE WAS ", -90, 35, .5f, 0xff0202);
				draw_number(current_points, -45, 33.5f, .7f, 0x020aff);
				draw_text("YOUR LEVEL WAS ", -90, 30, .5f, 0xff0202);
				i = 0;
				while (i < nlvl && sb_ok == false)
				{
					if(findEdge(Edge(i , i+1)))
						leveladiacenta++;
					i++;
					if (i == nlvl)
						sb_ok = true;
				}
				draw_number(leveladiacenta + 1, -45, 28.5f, .7f, 0x020aff);
			}

		}
	}
	else {
		if (pressed(BUTTON_LEFT) || pressed(BUTTON_RIGHT))
		{
			hot_button = !hot_button;
		}

		if (pressed(BUTTON_ENTER))
		{
			current_gamemode = GM_GAMEPLAY;
			gameplay = hot_button ? 1 : 0;
		}

		if (hot_button == 0) {
			draw_text("PLAY", -40, -10, 1, 0xff0000); 
			draw_text("EXIT", 20, -10, 1, 0xaaaaaa);
		}
		else {
			draw_text("PLAY", -40, -10, 1, 0xaaaaaa);
			draw_text("EXIT", 20, -10, 1, 0xff0000);
		}
	}
}

