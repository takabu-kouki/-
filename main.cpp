#include <Novice.h>
#include<Vector2.h>

const char kWindowTitle[] = "GC1D_07_タカブ_コウキ1";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	const int kWindowWidth = 1280; // ウィンドウの横幅
	const int kWindowHeight = 720; // ウィンドウの縦幅
	int playerSpeed = 5;
	//int fiftycoin = 50;//50コイン
	//    int faivcoin = 5;//5コイン

	struct Ball {
		Vector2 position;
		Vector2 velocity;
		Vector2 acceleration;
		float radius;
		unsigned int color;
	};

	Ball ball = {
		{10.0f,50.0f},
		{0.0f,0.0f},
		{0.0f,-0.8f},
		50.0f,
		WHITE
	};

	float positionY = 0;
	positionY += -100;
	positionY *= -1;
	
	float screenPos = 0.0f;
	
	enum Scene {
		TITLE,
		GAME,
		CLEAR,
		OVER,
	};

	int scene = TITLE;

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);


	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	int grapHandle = Novice::LoadTexture("./TD.png");

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		///
		switch (scene) {
		case TITLE:
			if (keys[DIK_RETURN] && preKeys[DIK_RETURN] == 0) {
				scene = GAME;
				
			ball.position.x = ball.position.x + playerSpeed;//右に
			if (keys[DIK_SPACE] != 0 && ball.position.y == ball.radius) {

				ball.velocity.y = 20.0f;//ジャンプ
				//PlayerSpeedY = 10;
			}

			ball.velocity.y += ball.acceleration.y;
			ball.position.y += ball.velocity.y;

			//地面にめり込まないようにする処理
			if (ball.position.y <= ball.radius) {
				ball.position.y = ball.radius;
			}


			screenPos = (ball.position.y + -500) * -1;//2フレーム後にpositionYが変化しないようにする変数

			


			break;
		case OVER:
			if (keys[DIK_RETURN] && preKeys[DIK_RETURN] == 0) {
				scene = TITLE;
			}
			break;

		case CLEAR:
			if (keys[DIK_RETURN] && preKeys[DIK_RETURN] == 0) {
				scene = TITLE;
			}
			break;
		}



		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		//Novice::DrawEllipse(playerPosX, playerPosY, playerRadius, playerRadius, 0.0f, WHITE,kFillModeSolid);
			
		switch (scene) {
		case TITLE:
				if (keys[DIK_RETURN] && preKeys[DIK_RETURN] == 0) {
					
					scene = GAME;
				}
				break;
			case GAME:
		Novice::DrawSprite(0, 0, grapHandle, 1, 1, 0.0f, 0xFFFFFFFF);
		Novice::DrawEllipse((int)ball.position.x, (int)screenPos, (int)ball.radius, (int)ball.radius, 0.0f, WHITE, kFillModeSolid);
		break;
			case OVER:
				if (keys[DIK_RETURN] && preKeys[DIK_RETURN] == 0) {
					scene = TITLE;
				}
				break;

			case CLEAR:
				if (keys[DIK_RETURN] && preKeys[DIK_RETURN] == 0) {
					scene = TITLE;
				}
				break;
	}

		




		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
