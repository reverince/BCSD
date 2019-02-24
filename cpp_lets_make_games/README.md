# C++ Let's Make Games

- 참고: 인프런 [C++ Let's Make Games](https://www.inflearn.com/course/c_game-making/) by 노근식

## 배울 내용
- 타입 시스템
- 반복문 및 배열 활용
- 구조체 및 포인터 활용
- 연결 리스트와 동적 할당

### 참고 자료
- https://www.inflearn.com/course/c_game-making/ 처음부터 `더블 링크드리스트 정렬 2`까지.

### 자료 정리
- github 등에 저장소를 만들고 직접 따라 만든 코드들을 push.
- 공부하는 과정에서 중요하다고 생각되거나, 의문이 있는 부분을 문서로 만들어 구글드라이브에 게시.

## 타입 시스템

| 종류 | 용량 | 데이터 | 표현 범위 | unsigned 표현 범위 |
|: - :|: - :|: - :|: - :|: - :|
| char | 1 byte | 문자 | -128 ~ 127 | 0 ~ 255 |
| bool | 1 byte | 참/거짓 | 0 ~ 1 | 0 ~ 1 |
| short | 2 bytes | 정수 | -32768 ~ 32767 | 0 ~ 65535 |
| int | 4 bytes | 정수 | -2147483648 ~ 2147483647 | 0 ~ 4,294,967,295 |
| float | 4 bytes | 실수 |
| double | 8 bytes | 실수 |

- 문자 표현은 ASCII 코드를 이용한다. 한글은 2바이트를 차지하기 때문에 `char`에 저장할 수 없다.

## 연산자

- 산술 연산자: `+`, `-`, `*`, `/`, `%`
- 관계 연산자: `==`, `!=`, `>=`, `>`
- 논리 연산자: `&&`(AND), `||`(OR), `!`(NOT)
- 비트 논리 연산자: `&`(AND), `|`(OR), `~`(NOT), `^`(XOR)
- 비트 이동 연산자: `<<`(LEFT SHIFT), `>>`(RIGHT SHIFT)
- 증감 연산자: `++`, `--`

## 진수 변환

2진수로 변환한 후에 다시 변환하는 것이 쉽다.

### 10진수에서 2진수로

`87 = (1010111)₂`

| 값 | / | 몫 | 나머지 |
|: - :|: - :|: - :|: - :|
| 87 | 2 | 43 | **1** |
| 43 | 2 | 21 | **1** |
| 21 | 2 | 10 | **1** |
| 10 | 2 | 5 | **0** |
| 5 | 2 | 2 | **1** |
| 2 | 2 | **1** | **0** |

마지막 몫부터 나머지 값들을 역순으로 읽는다.

### 2진수에서 16진수로

1. `16 = 2⁴`이므로 네 자리씩 끊어 계산한다. `87 = (0101 0111)₂`.
1. 2진수 네 자리는 16진수 한 자리로 표현된다. `(0101)₂ = 5`, `(0111)₂ = 7`.
1. 따라서 `87`을 16진수로 표현하면 `57`.

## 내장 메소드

- `sizeof(타입 혹은 변수)`: 해당 타입 혹은 변수의 메모리 크기를 반환한다.
- `typeid(타입 혹은 변수).name()`: 해당 타입 혹은 변수의 타입 이름을 반환한다.

## 열거체

```cpp
enum DIRECTION {
  // 0, 1, 2, ... 순으로 값이 부여된다.
  UP, DOWN, LEFT, RIGHT
}
```

## 가위바위보 게임

`rock_scissors_paper.cpp`

## `for`문 별 찍기

## 로또

`lotto.cpp`

## 야구 게임

`baseball.cpp`

## 숫자 퍼즐 게임

`number_puzzle.cpp`

- TODO: 리눅스에서 `getch()` 사용하기

## 숫자 빙고 게임

`number_bingo.cpp`

## 구조체

```cpp
struct Student {
  int id;
  char name[32];
};
```

- 관련 있는 변수들을 모아 만들어진 하나의 새로운 타입.
- 배열처럼 연속된 공간에 데이터가 저장된다.

## 문자열 함수

```cpp
// 문자열 길이
strlen(name);

// 오른쪽 문자열을 왼쪽으로 복사
strcpy_s(name, "YJ");

// 문자열 뒤에 새로운 문자열 추가
strcat_s(name, "Cho");

// 두 문자열이 같을 경우 0,
// 왼쪽 문자열이 클 경우 양수,
// 오른쪽 문자열이 클 경우 음수 반환
strcmp_s(name, name2);
```

## 학생 관리 프로그램 (구조체)

`student_manager.cpp`


## TextRPG

`textRPG.cpp`

## 포인터

```cpp
// x86에서는 4, x64에서는 8 출력
cout << sizeof(int*) << '\n';
cout << sizeof(char*) << '\n';
cout << sizeof(double*) << '\n';

int num = 100;
int* pNum = &num;
cout << *pNum << '\n';  //=> 100 (역참조)
cout << &num << '\n';     //=> 0012FF56
cout << pNum << '\n';   //=> 0012FF56
cout << &pNum << '\n';  //=> 0034DD78

// 이중 포인터
int** ppNum = &pNum;
cout << **ppNum << '\n';  //=> 100
cout << *pNum << '\n';    //=> 0034DD78

// 포인터 연산
int arr[5] = { 2, 3, 5, 7, 11 };
int* pArr;
cout << *pArr << '\n';        //=> 2
cout << *(pArr + 2) << '\n';  //=> 5

// 구조체 포인터
Student student = { };
student.kor = 100;
Student* pStudent = &student;
(*pStudent).kor = 50;  // 연산자 우선순위: . > *
pStudent->kor = 80;  // 대상의 멤버에 접근

// void 포인터
// 어떤 타입의 메모리 주소든 저장할 수 있다
// 역참조 불가능
void* pVoid = &num;
```

- 일반 변수는 값을 저장하지만 포인터 변수는 메모리 주소를 저장한다.
- 모든 변수 타입은 포인터로 선언할 수 있다.
- 32비트 환경에서는 4바이트, 64비트 환경에서는 8바이트를 차지한다.
- 다른 변수의 메모리 주소를 바탕으로 값을 제어한다.

## 미로 게임

`maze.cpp`

## 동적 할당

```cpp
int* pNum = new int;
*pNum = 100;
delete pNum;

// 동적 배열 할당
int* pNums = new int[10];
pNums[0] = 100;
delete[] pNums;
```

- 원하는 시점에 메모리를 할당할 수 있는 기능.
- 메모리 힙 영역에 할당되며 힙 특성상 해제하기 전까지는 메모리를 계속 차지한다.
- 사용하지 않는 메모리를 해제하지 않으면 메모리 누수가 발생할 수 있다.

## 학생 관리 프로그램 (단일 연결 리스트)

`student_manager_with_single_linked_list.cpp`
