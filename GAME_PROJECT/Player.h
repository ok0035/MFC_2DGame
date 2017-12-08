
class Player
{
public:
	Player(int px, int py, int speed);
	~Player();
	void Move(); //ĳ���� �̵�
	void Motion(); // ĳ���� �̵����
	int current_x; // ���� x��ǥ
	int current_y; // ���� y��ǥ
	int des_x; // ������ x��ǥ
	int des_y; // ������ y��ǥ
	int dx; // �̵� �ݰ� x��ǥ
	int dy; // �̵� �ݰ� y��ǥ
	bool isRight; // �������� ���� �ִ���
	bool isMotion; // �ȴ� ����� ���� bool ����
	bool isMove(); // �̵����� �ʾ����� �ȴ� ����� ������ �ʰ��ϱ� ����
	int spd; // �̵��ӵ�( dx, dy ����� �� ���)
	void SetDestination(int destination_x, int destination_y); // ������ ����
	int GetCurrentX(); // ���� ĳ���� x��ǥ ���
	int GetCurrentY(); // ���� ĳ���� y��ǥ ���
	bool isArrive(); // �����ߴ��� ����� bool ����
	void SetRandomDesX(); // ������ ������ x ��ǥ ����
	void SetRandomDesY(); // ������ ������ y ��ǥ ����
	void SetRandomCurrentX(); // ������ ���� ��ġ x ����
	void SetRandomCurrentY(); // ������ ���� ��ġ y ����
	void SeePlayer(); // ���콺�� Ŭ���� ������ �ٶ󺸵��� �ϱ� ���� bool ����
	void SetCurrentPoint(int x, int y); // ���� x, y ��ǥ ����
};
