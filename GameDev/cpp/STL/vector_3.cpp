#include <iostream>
#include <vector>
using namespace std;

int main()
{
    // - 중간 삽입 / 삭제 (bad) 나비 효과를 불러 일으킨다.
    // - 처음 / 끝 삭제
    // - 임의 접근 (Random Access)

    // vector = 동적배열 = 동적으로 커지는 배열 = 배열
    // ** 원소가 하나의 메모리 블록에 연속하게 저장된다 !

    // 중간 삽입 삭제가 되게 비효율 적이다.
    // 왜냐하면 예를 들어 [[0][1][2][3][4][][] ] 가 있다고 하자
    // 그렇다면 [5] 를 넣는 다고 [1] 과  [2] 사이에 넣는다고 가정하면, 
    // [5] [1] 뒤에 넣고 [2][3][4] 를 복사해서 뒤로 넣어줘야 한다. 
     
    // 처음 끝 삽입 / 삭제
    // [5][1][2][3][4][][] 5 라는 값을 앞으로 두고, 나머지 element 를 뒤로 복사해서
    // 보내줘야 하니까 효율적이지 않다.
    // 하지만 끝 삽입 같은경우 조금 쉽다 --> 끝만 지우거나 삽입 하면 되니까
    vector<int> v(20);
    v.push_back(1);
    v.pop_back();

    // 3 번째 데이터는 어디 있습니까?
    v[2] = 3;

    vector<int>::iterator ilt = v.insert(v.begin() + 2, 5); // 비효율적
    vector<int>::iterator ilt = v.erase(v.begin()+2);
    // 마지막 element 는 안지우고, 그 아래의 메모리를 삭제한다.
    vector<int>::iterator ilt = v.erase(v.begin()+2 , v.begin()+4);

    // 쭉 ~ 스캔을 하면서, 3 이라는 데이터가 있으면 일괄 삭제 하고 싶다.
    for(vector<int>::iterator it=v.begin(); it != v.end();)
    {
        int data = *it;
        if (data == 3)
        {
            it = v.erase(it);
            // it 자체가 null 로 바뀌고 it 는 사용할수 없게 되버린다.
            // 삭제를 할수 있는 방법은 break; 를 걸거나 it = v.erase(it) 로 바꿔줘야 한다.
            // 다시 유효한 it 를 저장하게끔 해줘야 한다.  
        }
        else
        {
            ++it;
            // 그런데 그 다음에 3 을 체크한 이후에 다음루프에 ++it 그다음데이터를 체크 하지도 않고 
            // 넘어가는 문제가 있다. 그래서 else 문으로 처리 해줘야한다.
        }
    }
    return 0;
}