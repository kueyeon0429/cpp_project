#include <clocale>
#include <ncurses.h>
#include <iostream>
#include <ctime>
#include "snake.h"
#include "kbhit.c"
using namespace std;

const HALF_SECOND = 0.5;

SNAKE snake;

// 옵션 초기화
void OptionInit(){
  setlocale(LC_ALL, "");
  initscr();
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_YELLOW);   // 팔레트1
  init_pair(2, COLOR_WHITE, COLOR_GREEN);    // 팔레트2
}

// 터미널 초기화
void TermInit(){
  resize_term(24, 50);
  border('|', '|', '-', '-', '+', '+', '+', '+');   // 테두리
  mvprintw(1, 1, "SnakeGame!");
  refresh();   // 화면 출력
  noecho();   // 입력한 문자 가리기
  getch();   // 문자 입력시 다음 이동
}

// 윈도우 초기화
void WinInit(WINDOW *win){
  win = newwin(21, 21, 2, 1);   // 맵 생성
  wbkgd(win, '0');   // 맵 배경

  keypad(win, TRUE);   // 특수 키 입력 가능
  curs_set(0);   // 커서 가림

  wattron(win, COLOR_PAIR(2));
  wborder(win, '1', '1', '1', '1', '2', '2', '2', '2');
  wattroff(win, COLOR_PAIR(2));
}

// sanke 초기화
void SnakeInit(WINDOW *win){
  snake.y = 10;   // 처음 위치 초기화
  snake.x = 10;
  sanke.length = 3;   // 길이 초기화
  snake.head = KEY_RIGHT;   // 방향 초기화
  wattron(win, COLOR_PAIR(1));
  mvwprintw(win, y, x, "3");
  wattroff(win, COLOR_PAIR(1));

  wrefresh(win);
}

// 방향키 받는 함수
int Head(){
  if(kbhit() == true)
    return getch();
}

// 회전 ---------------완전수정해야댐,,
void Turn(WINDOW *win, int head){
  while(1){
      // 초기화 및 배경 유지
      wclear(win);
      wbkgd(win, '0');
      wattron(win, COLOR_PAIR(2));
      wborder(win, '1', '1', '1', '1', '2', '2', '2', '2');
      wattroff(win, COLOR_PAIR(2));
      // 이동
      wattron(win, COLOR_PAIR(1));
      if(pre == KEY_LEFT){   // head방향: 좌
        switch(input){
            case KEY_UP:
            mvwprintw(win, --y, ++x, "3");
            pre = input;  // head방향(=pre) 갱신
            continue;
            case KEY_DOWN:
            mvwprintw(win, ++y, ++x, "3");
            pre = input;  // head방향(=pre) 갱신
            continue;
            case KEY_LEFT:
            continue;
            case KEY_RIGHT:
            break;
        }
      }
      else if(pre == KEY_RIGHT){
        switch(input){
            case KEY_UP:
            mvwprintw(win, --y, --x, "3");
            pre = input;  // head방향(=pre) 갱신
            continue;
            case KEY_DOWN:
            mvwprintw(win, ++y, --x, "3");
            pre = input;  // head방향(=pre) 갱신
            continue;
            case KEY_LEFT:
            break;
            case KEY_RIGHT:
            continue;
        }
      }
      else if(pre == KEY_UP){
        switch(input){
            case KEY_UP:
            continue;
            case KEY_DOWN:
            break;
            case KEY_LEFT:
            mvwprintw(win1, ++y, --x, "3");
            pre = input;  // head방향(=pre) 갱신
            continue;
            case KEY_RIGHT:
            mvwprintw(win, ++y, ++x, "3");
            pre = input;  // head방향(=pre) 갱신
            continue;
        }
      }
      else if(pre == KEY_DOWN){
        switch(input){
            case KEY_UP:
            break;
            case KEY_DOWN:
            continue;
            case KEY_LEFT:
            mvwprintw(win, --y, --x, "3");
            pre = input;  // head방향(=pre) 갱신
            continue;
            case KEY_RIGHT:
            mvwprintw(win, --y, ++x, "3");
            pre = input;  // head방향(=pre) 갱신
            continue;
        }
      }
      wattroff(win, COLOR_PAIR(1));
  }
}

// 상태 업데이트
void StateUpdate(int head, clock_t curr){

}

// 화면 출력
//void Render(WINDOW *win){
//    wrefresh(win);
//}


int main(){
  OptionInit();
  TermInit();
  WinInit();
  SnakeInit();

  while(1){
    snake.head = Head();
    clock_t cuttTime = clock();
    StateUpdate(snake.head, currTime);
    wrefresh(snake.win)
  }

  getch();
  delwin(snake.win);
  endwin();

  return 0;

}
