
class Player
{
public:
	Player(int px, int py, int speed);
	~Player();
	void Move(); //캐릭터 이동
	void Motion(); // 캐릭터 이동모션
	int current_x; // 현재 x좌표
	int current_y; // 현재 y좌표
	int des_x; // 목적지 x좌표
	int des_y; // 목적지 y좌표
	int dx; // 이동 반경 x좌표
	int dy; // 이동 반경 y좌표
	bool isRight; // 오른쪽을 보고 있는지
	bool isMotion; // 걷는 모션을 위한 bool 변수
	bool isMove(); // 이동하지 않았으면 걷는 모션을 취하지 않게하기 위함
	int spd; // 이동속도( dx, dy 계산할 때 사용)
	void SetDestination(int destination_x, int destination_y); // 목적지 설정
	int GetCurrentX(); // 현재 캐릭터 x좌표 얻기
	int GetCurrentY(); // 현재 캐릭터 y좌표 얻기
	bool isArrive(); // 도착했는지 물어보는 bool 변수
	void SetRandomDesX(); // 랜덤한 목적지 x 좌표 설정
	void SetRandomDesY(); // 랜덤한 목적지 y 좌표 설정
	void SetRandomCurrentX(); // 랜덤한 현재 위치 x 설정
	void SetRandomCurrentY(); // 랜덤한 현재 위치 y 설정
	void SeePlayer(); // 마우스를 클릭한 방향을 바라보도록 하기 위한 bool 변수
	void SetCurrentPoint(int x, int y); // 현재 x, y 좌표 설정
};
