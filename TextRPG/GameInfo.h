#pragma once
// 모두 컴파일된 헤더
#include <iostream>
#include <assert.h>
#include <vector>
#include <string>
#include <Windows.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

// 싱글톤 매크로
#define DECLARE_SINGLETON(classname) private: \
classname();\
~classname();\
public:\
	static CGameManager* GetInst()\
	{\
		static CGameManager Inst;\
		return &Inst;\
	}

#define SYSCLS system("cls");
#define SYSPAUSE system("pause");

#define COUT(TEXT) cout << TEXT;
#define COUTN(TEXT) cout << TEXT << endl;


//글씨색 바꾸기
//ANSI 이스케이프 코드
//https://en.wikipedia.org/wiki/ANSI_escape_code
const std::string FONTCOLOR_REST = "\033[0m";
const std::string FONTCOLOR_RED = "\033[31m";
const std::string FONTCOLOR_GREEN = "\033[32m";
const std::string FONTCOLOR_BLUE = "\033[34m";


#define COUT(TEXT) std::cout << TEXT;
#define COUTN(TEXT) std::cout << TEXT << std::endl;
#define COUTN_RED(TEXT) std::cout << FONTCOLOR_RED << TEXT <<FONTCOLOR_REST << std::endl;
#define COUTN_GREEN(TEXT) std::cout << FONTCOLOR_GREEN << TEXT <<FONTCOLOR_REST << std::endl;
#define COUTN_BLUE(TEXT) std::cout << FONTCOLOR_BLUE << TEXT <<FONTCOLOR_REST << std::endl;


#define DEFAULT_HP 100
#define DEFAULT_ATK 10
#define DEFAULT_DEF 5

// 3초 뜸들이기
#define SLEEP3 Sleep(1000);\
COUTN("...");\
Sleep(1000);\
COUTN("...");\
Sleep(1000);\
COUTN("...");

// 직업
enum class eJobClass
{
	NONE,
	Warrior,
	Wizard,
	Thief,
	Archer,
	MAX
};

// 플레이어의 상태
enum class ePlayerState
{
	// 탐색
	search,
	// 전투
	combat,
	END
};

// 플레이어 공격시 모드
enum class ePlayerCombatMode
{
    None,
    Attack,
    Defense,
    Run,
    Boss,
    MAX
};

// 탐색
enum class eEventType
{
	Tresure,    // 보물찾기
	Enemy,      // 적 만나기
    Mine,       // 함정
	MAX
};

// 몬스터 타입
enum class eMonsterType
{
    Slime,
    Goblin,
    Skeleton,
    End,
    Boss
};

// 지역이름
enum class eAreaName
{
    Forest,
    Rival,
    Mountaion,
    Hell
};






namespace GlobalFunc
{
	// 슬라임 이미지
    static void PrintSlimeImage()
    {
        std::cout << FONTCOLOR_GREEN << R"(
              ██████████              
         ██████        ██████         
      ████                ████       
    ███      ◕      ◕       ███     
   ██                          ██    
  ██          ▄▄▄▄▄▄▄           ██   
  ██         █        █          ██  
   ██         ████████          ██   
    ███                        ███   
      ████                  ████     
         ██████        ██████        
              ██████████              
)" << FONTCOLOR_REST << std::endl;
    }

    // 고블린 이미지
    static void PrintGoblinImage()
    {
        std::cout << FONTCOLOR_RED << R"(
                 ,      ,
                /(.-""-.)\
            |\  \/      \/  /|
            | \ / =.  .= \ / |
            \( \   o\/o   / )/
             \_, '-/  \-' ,_/
               /   \__/   \
               \ \__/\__/ /
             ___\ \|--|/ /___
           /`    \      /    `\
          /       '----'       \
)" << FONTCOLOR_REST << std::endl;
    }

    // 스켈레톤 이미지
    static void PrintSkeletonImage()
    {
        std::cout << FONTCOLOR_BLUE << R"(
             .-"      "-.
            /            \
           |,  .-.  .-.  ,|
           | )(_o/  \o_)( |
           |/     /\     \|
           (_     ^^     _)
            \__|IIIIII|__/
             | \IIIIII/ |
             \          /
              `--------`
)" << FONTCOLOR_REST << std::endl;
    }

    // 보스 드래곤 이미지
    static void PrintDragonBoss()
    {
        std::cout << FONTCOLOR_RED << R"(
                     ___====-_    _-====___
               _--^^^#####//       \\#####^^^--_
            _-^##########//  (    ) \\##########^-_
           -############//   |\^^/|  \\############-
         _/############//    (@::@)   \\############\_
        /#############((      \\//     ))#############\
       -###############\\     (oo)    //###############-
      -#################\\  / UUU   \//#################-
     -###################\\/  (vVv)  \/###################-
    _#/|##########/\######(   /   \   )######/\##########|\#_
    |/ |#/\#/\#/\/  \#/\##\  |(O O)|  /##/\#/  \/\#/\#/\#| \|
    '  |/  V  V  '   V  \\#\|  (_)  |/#//V   '  V  V  \|  '
       '   '  '      '   / |         | \   '      '  '   '
                        (  |         |  )
                       __\ |  .---.  | /__
                      (vvv(V         V)vvv)
)" << FONTCOLOR_REST << std::endl;
    }





    // 다음 층 연출 아트
    static void PrintUpFloor()
    {
        for (int openingWidth = 0; openingWidth < 12; ++openingWidth)
        {
            SYSCLS;
            const int height = 12;
            const int width = 30;
            const int center = width / 2;
            std::string message = "Next Area";

            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    // 문틀 그리기
                    if ((y == 0 || y == height - 1) && (x > 0 && x < width - 1)) {
                        printf("-");
                    }
                    else if (y > 0 && y < height - 1 && (x == 0 || x == width - 1)) {
                        printf("|");
                    }
                    else if (x == 0 || x == width - 1 || y == 0 || y == height - 1) {
                        printf("+");
                    }
                    // 문짝 그리기
                    else {
                        int leftDoorEdge = center - openingWidth;
                        int rightDoorEdge = center + openingWidth;

                        // 왼쪽 문
                        if (x > 0 && x <= leftDoorEdge) {
                            // 문고리
                            if (y == height / 2 && x == leftDoorEdge - 1) {
                                printf("o");
                            }
                            else {
                                printf("#");
                            }
                        }
                        // 오른쪽 문
                        else if (x >= rightDoorEdge && x < width - 1) {
                            // 문고리
                            if (y == height / 2 && x == rightDoorEdge + 1) {
                                printf("o");
                            }
                            else {
                                printf("#");
                            }
                        }
                        // 문이 완전히 열렸을 때 메시지 표시
                        else if (openingWidth >= center - (message.length() / 2) - 2 && y == height / 2) {
                            int msg_start_pos = center - message.length() / 2;
                            if (x >= msg_start_pos && x < msg_start_pos + message.length()) {
                                printf("%c", message[x - msg_start_pos]);
                            }
                            else {
                                printf(" ");
                            }
                        }
                        // 그 외 빈 공간
                        else {
                            printf(" ");
                        }
                    }
                }
                printf("\n");

            }
            Sleep(500);
        }
    }

}