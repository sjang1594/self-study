// Game Manager
// is-a
// has-a

// 전방 선언
class Player;
class Field;

class Game
{
public:
	Game();
	~Game();
	void Init();
	void Update();
	void CreatePlayer();
private:
	// Player _player --> 의존성이 생김

	// [4 - 8] ----> []
	Player* _player;
	Field* _field;
};