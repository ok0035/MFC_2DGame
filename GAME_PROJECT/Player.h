
class Player
{
public:
	Player(int px, int py, int speed);
	~Player();
	void Move();
	void Motion();
	int current_x;
	int current_y;
	int des_x;
	int des_y;
	int dx;
	int dy;
	bool isRight;
	bool isMotion;
	bool isMove();
	int spd;
	void SetDestination(int destination_x, int destination_y);
	int GetCurrentX();
	int GetCurrentY();
	bool isArrive();
	void SetRandomDesX();
	void SetRandomDesY();
	void SetRandomCurrentX();
	void SetRandomCurrentY();
};
